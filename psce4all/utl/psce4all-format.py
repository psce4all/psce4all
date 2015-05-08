#!/usr/bin/python

import os
import re

# Directories
GIT_DIR = os.path.abspath("..\..")
PS1E4ALL_DIR = os.path.join(GIT_DIR, "ps1e4all")
PS2E4ALL_DIR = os.path.join(GIT_DIR, "ps2e4all")
PSPE4ALL_DIR = os.path.join(GIT_DIR, "pspe4all")
PSCE4ALL_DIR = os.path.join(GIT_DIR, "psce4all")
PS1E4ALL_SRC = os.path.join(PS1E4ALL_DIR, "src")
PS2E4ALL_SRC = os.path.join(PS2E4ALL_DIR, "src")
PSPE4ALL_SRC = os.path.join(PSPE4ALL_DIR, "src")
PSCE4ALL_SRC = os.path.join(PSCE4ALL_DIR, "src")

# Formatting rules for *.c, *.cpp and *.h files
def formatGeneric(codeInput):

    # Replace LF with CRLF
    codeInput = re.sub(r'^[\r]\n', r'\r\n', codeInput)

    # Replace tabs with 4 spaces
    codeInput = codeInput.expandtabs(4)

    # Remove tabs or spaces at the end of lines
    codeInput = re.sub(r'([ \t]+)\r', r'\r', codeInput)
    
    return codeInput

# Search and edit files of the PSCE4ALL project
def main():
    for path in [PSCE4ALL_SRC, PS1E4ALL_SRC, PS2E4ALL_SRC, PSPE4ALL_SRC]:
        for root, dirs, files in os.walk(path):
            for filename in files:
                if not filename.endswith((".c",".cc",".cpp",".h",".hpp")):
                    continue

                # Read and format the code
                f = open(os.path.join(root, filename), "rb")
                codeInput = f.read()
                codeOutput = formatGeneric(codeInput)
                f.close()

                # Update file if necessary
                if codeInput != codeOutput:
                    w = open(os.path.join(root, filename), "wb")
                    w.write(codeOutput)
                    w.close()

if __name__ == "__main__":
    main()