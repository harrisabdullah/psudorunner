# psudorunner
This project is a pure C implementation of an interpreter that executes IGCSE / A-Level pseudocode as defined by the Cambridge International syllabus. It supports a subset of structured pseudocode commands such as loops and conditions.

## Features

- Execute pseudocode written in Cambridge IGCSE/A-Level style
- Supports:
  - Control flow: `IF` / `ELSE IF` / `ELSE` / `ENDIF`
  - Loops: `FOR` / `WHILE` / `REPEAT` / `UNTIL`
  - I/O: `INPUT`, `OUTPUT`
- Written in pure C (C99)
- Unit tested with Google Test
- Build system: CMake

## Installation

```bash
git clone --recurse-submodules https://github.com/harrisabdullah/psudorunner
cd psudorunner
mkdir build && cd build
cmake ..
make
```

## usage

1. Edit main.c, assign your pseudocode to the char* code variable.
2. Build & run:
```bash
./psudo_interprator_EXE
```

## Roadmap

### testing

- [ ] Parser unit testing.
- [ ] Execution engine unit testing.
- [ ] Integration testing.

### other

- [ ] Revamp error handling to return error structs that can then be passed to an error-raising function.
- [ ] Syntax error on invalid identifier name in tokenisation.
- [ ] Clean command-line interface: pass a `.pseudo` file or read from STDIN.
- [ ] Memory safety.
