![Demo]("assets/Demo.png")
> screenshot

# 📖 English Dictionary Console Program

This is a simple console-based English dictionary application written in C. The program allows users to manage a collection of words using a text-based menu interface.

## Features
- Add new words to the dictionary
- Delete existing words
- Search for words
- Display all words
- Sort dictionary entries
- Save dictionary to a file
- Load dictionary on startup

## Project Structure
- src/ – source code files
- includes/ – header files
- saves/ – saved dictionary data
- build/ – compiled executable

## Build Instructions
Compile and run the project using GCC:

```gcc src/*.c -I include/ -o build/program && ./build/program```

## Notes
- The dictionary is stored in memory during execution.
- Changes are saved to a file in the saves/ directory.
- Make sure the saves folder exists before running the program.
