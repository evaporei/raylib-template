import json
import os
import re

# Paths to the json file and the src folder
json_path = 'parser/output/raylib_api.json'

# Load function names from raylib_api.json
with open(json_path, 'r') as f:
    data = json.load(f)

# Assuming functions are dictionaries with a "name" key
function_names = [func["name"] for func in data.get("functions", [])]

# Filter out any function that already has an `rl` prefix or is known to exist in rlgl.h
# Adjust the list based on rlgl functions you want to exclude.
excluded_functions = {
    'LoadTexture', 'LoadTextureCubemap', 'UpdateTexture', 'UnloadTexture', 
    'GenTextureMipmaps', 'GetPixelDataSize'
}
function_names = [name for name in function_names if name not in excluded_functions and not name.startswith('rl')]

# Sort by length in descending order to handle function names with common prefixes
function_names.sort(key=len, reverse=True)

# Build a dictionary for replacement (e.g., "InitWindow" -> "rlInitWindow")
replace_dict = {func_name: f"rl{func_name}" for func_name in function_names}

# Function to replace text in a file
def replace_in_file(file_path, replace_dict):
    with open(file_path, 'r') as file:
        content = file.read()

    # Replace all occurrences of each function name with its rl-prefixed version
    for original, replacement in replace_dict.items():
        content = re.sub(rf'\b{original}\b', replacement, content)

    # Write the modified content back to the file
    with open(file_path, 'w') as file:
        file.write(content)

# Traverse a directory and process all files
def replace_in_dir(folder_path, replace_dict):
    for root, _, files in os.walk(folder_path):
        for file_name in files:
            if file_name.endswith(('.c', '.h', '.cpp', '.hpp')):  # Adjust as needed for file types
                file_path = os.path.join(root, file_name)
                replace_in_file(file_path, replace_dict)

replace_in_dir('src', replace_dict)
replace_in_dir('examples', replace_dict)

print("Replacement complete!")
