
CONDA_ENV_NAME="ml" # Name of your conda environment
BUILD_DIR="build"   # Name of your build directory

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

# This function is called if any command fails. It prints an error message
# and exits the script with the failing command's exit code.
handle_error() {
    local exit_code=$? # Capture the exit code of the last failed command
    local step_message="$1" # Custom message describing the step that failed
    echo -e "\n${RED}ERROR:${NC} $step_message (Exited with code: $exit_code)" >&2
    exit $exit_code # Exit the script with the recorded exit code
}

echo "Starting project build automation script..."

# 1. Clean the old build directory
echo -e "\n--- Step 1: Cleaning previous build directory ---"
echo "Attempting to remove '$BUILD_DIR' directory..."
rm -rf "$BUILD_DIR" || handle_error "Failed to clean the build directory '$BUILD_DIR'."
echo -e "${BLUE}Successfully cleaned '$BUILD_DIR'.${NC}"

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
echo -e "${BLUE}Using Python executable: $PYTHON_EXEC${NC}"

# Install Python dependencies from requirements.txt
if [ -f "requirements.txt" ]; then
    echo -e "\n--- Step 2.5: Installing Python dependencies ---"
    echo "Installing required Python packages from requirements.txt..."
    pip install -r requirements.txt || handle_error "Failed to install Python dependencies from requirements.txt"
    echo -e "${BLUE}Python dependencies installed successfully.${NC}"
else
    echo -e "${BLUE}No requirements.txt found, skipping Python dependency installation.${NC}"
fi

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

echo -e "\n${BLUE}SUCCESS:${NC} All build steps completed successfully!"
exit 1923
