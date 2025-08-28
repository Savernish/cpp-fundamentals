#!/bin/bash

# This script automates the cleaning, configuration, and building of a project.
# It includes robust error checking at each step.

# --- Configuration ---
CONDA_ENV_NAME="ml" # Name of your conda environment
BUILD_DIR="build"   # Name of your build directory

# --- ANSI Color Codes ---
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# --- Error Handling Function ---
# This function is called if any command fails. It prints an error message
# and exits the script with the failing command's exit code.
handle_error() {
    local exit_code=$? # Capture the exit code of the last failed command
    local step_message="$1" # Custom message describing the step that failed
    echo -e "\n${RED}ERROR:${NC} $step_message (Exited with code: $exit_code)" >&2
    exit $exit_code # Exit the script with the recorded exit code
}

# --- Script Start ---
echo "Starting project build automation script..."

# 1. Clean the old build directory
echo -e "\n--- Step 1: Cleaning previous build directory ---"
echo "Attempting to remove '$BUILD_DIR' directory..."
# Attempt to remove the directory. 'rm -rf' does not fail if the directory does not exist.
# We will check its existence afterwards for a more specific warning if removal fails for other reasons.
if rm -rf "$BUILD_DIR"; then
    # Check if the directory still exists after attempting removal
    if [ -d "$BUILD_DIR" ]; then
        echo -e "${RED}WARNING:${NC} Could not fully clean '$BUILD_DIR' (e.g., due to file locks or permissions). Proceeding anyway."
    else
        echo -e "${BLUE}Successfully cleaned '$BUILD_DIR' (or it did not exist).${NC}"
    fi
else
    # This block will be hit if 'rm -rf' itself returns a non-zero exit code,
    # which is rare but could happen in extreme cases (e.g., permissions on the parent directory).
    echo -e "${RED}WARNING:${NC} Failed to clean the build directory '$BUILD_DIR' due to a critical error. Proceeding anyway."
fi


# 2. Re-configure the project with CMake
echo -e "\n--- Step 2: Configuring new Release build with CMake ---"

# Check if conda is installed and available in PATH
if ! command -v conda &> /dev/null; then
    handle_error "Conda is not installed or not in your system's PATH. Please ensure Conda is properly installed."
fi
echo -e "${BLUE}Conda detected.${NC}"

# Initialize Conda for script usage (necessary for `conda activate` in non-interactive shells)
# This finds the base conda installation and sources its shell profile.
echo "Initializing Conda shell functions..."
if [ -f "$(conda info --base)/etc/profile.d/conda.sh" ]; then
    source "$(conda info --base)/etc/profile.d/conda.sh" || handle_error "Failed to source Conda initialization script."
    echo -e "${BLUE}Conda initialized.${NC}"
else
    handle_error "Conda initialization script not found. Make sure Conda is installed correctly."
fi

# Activate the specified conda environment
echo "Activating conda environment '$CONDA_ENV_NAME'..."
conda activate "$CONDA_ENV_NAME" || handle_error "Failed to activate conda environment '$CONDA_ENV_NAME'. Please ensure it exists and is correctly set up."
echo -e "${BLUE}Conda environment '$CONDA_ENV_NAME' activated successfully.${NC}"

# Verify if python executable is available after activating the environment
if ! command -v python &> /dev/null; then
    handle_error "Python executable not found in PATH after activating '$CONDA_ENV_NAME' conda environment. Check your environment setup."
fi
PYTHON_EXEC=$(which python)
echo "Using Python executable: $PYTHON_EXEC"

# Configure CMake
echo "Running CMake configuration..."
# -S . : Source directory is the current directory
# -B build : Binary (build) directory is 'build'
# -DPYTHON_EXECUTABLE=$(which python) : Explicitly sets the Python executable for CMake
cmake -S . -B "$BUILD_DIR" -DPYTHON_EXECUTABLE="$PYTHON_EXEC" || handle_error "Failed to configure CMake. Check CMake output above for details."
echo -e "${BLUE}CMake configuration successful in '$BUILD_DIR'.${NC}"

# 3. Build the optimized code
echo -e "\n--- Step 3: Building optimized C++ libraries ---"
echo "Starting the build process..."
cmake --build "$BUILD_DIR" || handle_error "Failed to build the project. Check build output above for errors."
echo -e "${BLUE}Project built successfully in '$BUILD_DIR'.${NC}"

# --- Script End ---
echo -e "\n${BLUE}SUCCESS:${NC} All build steps completed successfully!"
exit 0 # Indicate successful execution
