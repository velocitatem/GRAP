# Grap Language

Grap is a simple, custom programming language designed for creating and manipulating graphs. This document provides a brief overview of how to use the Grap language.

## Installation

To install the Grap interpreter, clone the repository and build the project using CMake:

```bash
git clone https://github.com/username/grap.git
cd grap
mkdir build
cd build
cmake ..
make
```

This will generate an executable in the `build` directory.

## Usage

To run a Grap program, pass the `.grap` file as an argument to the Grap interpreter:

```bash
./grap_interpreter path_to_your_program.grap
```

## Language Syntax

Grap programs consist of commands separated by the `|` character. Each command has a module, an action, and zero or more parameters. Here's a basic example of a Grap program:

```grap
mem | save | (int | "num1" | "2")
mem | save | (int | "num2" | "3")
io | say | ( mem | get | "num1")
io | say | ( mem | get | "num2")
```

In this program, the `mem | save` command saves a value into memory, and the `io | say` command prints a value from memory.

## Modules

Grap has several built-in modules:

- `mem`: Used for saving and retrieving values in memory.
- `io`: Used for input and output operations.
- `bits`: Used for bitwise operations.

Each module has its own set of actions and parameters.

## Contributing

Contributions to the Grap language are welcome. Please submit a pull request with your changes.

## License

The Grap language is licensed under the MIT License.