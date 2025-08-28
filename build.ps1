# This script automates the cleaning, configuration, and building of a project on Windows.
# It includes robust error checking at each step using PowerShell.
# This version does NOT use Conda and relies on a system-wide Python installation.

# --- Configuration ---
$BuildDir = "build"   # Name of your build directory

# --- ANSI Color Codes for PowerShell ---
# Note: These colors require a modern PowerShell terminal (e.g., Windows Terminal)
# or PowerShell 5.1+ with support for ANSI escape sequences.
$Red = "`e[0;31m]"
$Green = "`e[0;32m]"
$Blue = "`e[0;34m]"
$NC = "`e[0m]" # No Color

# --- Error Handling Function ---
# This function is called if any command fails. It prints an error message
# and exits the script.
function Handle-Error {
    param(
        [string]$StepMessage,
        [int]$ExitCode = 1 # Default exit code for general errors
    )
    # Check if the last command (external executable) failed
    if ($LASTEXITCODE -ne 0 -and $ExitCode -eq 1) { # Only use LASTEXITCODE if no specific ExitCode was provided
        $ExitCode = $LASTEXITCODE
    }
    Write-Host ""
    Write-Host "${Red}ERROR:${NC} $StepMessage (Exited with code: $ExitCode)" -ForegroundColor Red -ErrorVariable +ErrorMessage
    exit $ExitCode
}

# --- Script Start ---
Write-Host "Starting project build automation script for Windows..."

# 1. Clean the old build directory
Write-Host "`n--- Step 1: Cleaning previous build directory ---"
Write-Host "Attempting to remove '$BuildDir' directory..."
try {
    # Remove-Item with -Force does not throw an error if the path does not exist.
    # We set -ErrorAction SilentlyContinue to gracefully handle other non-terminating errors (though -Force often prevents them).
    # If a terminating error occurs (e.g., access denied), the catch block will handle it.
    Remove-Item -Path $BuildDir -Recurse -Force -ErrorAction Stop

    # After attempting removal, check if the directory still exists.
    # If it does, and it's not due to it simply not existing initially, then there was a problem.
    if (Test-Path $BuildDir -PathType Container) {
        Write-Host "${Red}WARNING:${NC} Could not fully clean '$BuildDir' (e.g., due to file locks or permissions). Proceeding anyway."
    } else {
        Write-Host "${Blue}Successfully cleaned '$BuildDir' (or it did not exist).${NC}"
    }
}
catch {
    # This catch block will only be hit if a *terminating* error occurred during Remove-Item,
    # which is often more severe (like critical permissions issues that -Force can't overcome).
    Write-Host "${Red}WARNING:${NC} Failed to clean the build directory '$BuildDir' due to a critical error: $($_.Exception.Message). Proceeding anyway."
}


# 2. Re-configure the project with CMake
Write-Host "`n--- Step 2: Configuring new Release build with CMake ---"

# --- Python Path Determination (System-wide Python) ---
Write-Host "Attempting to use system-wide Python."
try {
    $PythonExec = (Get-Command python -ErrorAction SilentlyContinue).Path
    if (-not $PythonExec) {
        Handle-Error "Python executable not found in system PATH. Please ensure Python is installed and in your PATH."
    }
    Write-Host "${Blue}Using system-wide Python executable: $PythonExec${NC}"
}
catch {
    Handle-Error "Failed to find system-wide Python executable. Error: $($_.Exception.Message)"
}


# Configure CMake
Write-Host "Running CMake configuration..."
try {
    # -S . : Source directory is the current directory
    # -B build : Binary (build) directory is 'build'
    # -DPYTHON_EXECUTABLE=<path> : Explicitly sets the Python executable for CMake
    cmake -S . -B $BuildDir "-DPYTHON_EXECUTABLE=$PythonExec"
    # Check CMake's exit code
    if ($LASTEXITCODE -ne 0) {
        Handle-Error "CMake configuration failed. Check CMake output above for details."
    }
    Write-Host "${Blue}CMake configuration successful in '$BuildDir'.${NC}"
}
catch {
    Handle-Error "Failed to configure CMake. Error: $($_.Exception.Message)"
}

# 3. Build the optimized code
Write-Host "`n--- Step 3: Building optimized C++ libraries ---"
Write-Host "Starting the build process..."
try {
    cmake --build $BuildDir
    # Check CMake build's exit code
    if ($LASTEXITCODE -ne 0) {
        Handle-Error "Project build failed. Check build output above for errors."
    }
    Write-Host "${Blue}Project built successfully in '$BuildDir'.${NC}"
}
catch {
    Handle-Error "Failed to build the project. Error: $($_.Exception.Message)"
}

# --- Script End ---
Write-Host "`n${Blue}SUCCESS:${NC} All build steps completed successfully!"
exit 0 # Indicate successful execution
