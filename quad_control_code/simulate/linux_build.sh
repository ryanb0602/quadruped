#!/bin/bash

# Enable error handling
set -e
set -o pipefail

# Define paths
BASE_DIR="$HOME/Documents/quadruped"
FLATTENED_DIR="$BASE_DIR/simulate/__TEMP_BUILD_DIR"
LIB_DIR="$BASE_DIR/lib"

# Create the flattened directory if it doesn't exist
mkdir -p "$FLATTENED_DIR"

# Copy all .cpp and .h files from nested folders to the flattened directory, excluding files with unwanted dependencies
find "$LIB_DIR" -type f \( -name "*.cpp" -o -name "*.h" \) | while read -r file; do
    if ! grep -q '#include <Arduino.h>' "$file"; then
        cp "$file" "$FLATTENED_DIR"
    fi
done

# Compile the necessary files
g++ -I"$FLATTENED_DIR" -fPIC -shared -m64 -o "$BASE_DIR/simulate/kinecore.so" "$FLATTENED_DIR"/*.cpp simlink.cpp

# Clean up the temporary build directory
rm -rf "$FLATTENED_DIR"
