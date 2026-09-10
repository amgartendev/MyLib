# MyLib

[![Vector Tests](https://github.com/amgartendev/MyLib/actions/workflows/tests.yaml/badge.svg)](https://github.com/amgartendev/MyLib/actions/workflows/tests.yaml)

MyLib is a lightweight C library implementing data structures and utilities from scratch, built for learning, experimentation, and real-world use.

The project focuses on understanding how common data structures work internally by implementing memory management, dynamic allocation, resizing strategies, and utility functions directly in C.

MyLib is currently developed and tested on both Linux and Windows.

---

## Features

### Vector

A dynamic array implementation with automatic memory management.

Currently supports `char` elements.

Implemented operations include:

- Initialization and destruction
- Push and insert
- Pop and remove
- Get and set
- First and last element access
- Size and capacity queries
- Empty checks
- Find and contains
- Count occurrences
- Swap elements
- Reverse
- Copy
- Reserve capacity
- Shrink to fit
- Clear
- Vector information output
- Vector contents output

---

## Project Structure

```text
MyLib/
├── .github/
│   └── workflows/
│       └── tests.yaml
│
├── bin/
│   └── tests(.exe)
│
├── inc/
│   └── mylib/
│       ├── common.h
│       └── vector.h
│
├── obj/
│   ├── vector.o
│   ├── test_main.o
│   └── test_vector.o
│
├── src/
│   └── vector.c
│
├── tests/
│   ├── test_common.h
│   ├── test_main.c
│   ├── test_vector.h
│   └── test_vector.c
│
├── .gitignore
├── LICENSE
├── Makefile
└── README.md
```

The `inc/` directory contains the public headers exposed by the library.

The `src/` directory contains the library implementations.

The `tests/` directory contains the test framework, test runner, and individual module test suites.

The `obj/` directory contains intermediate object files generated during compilation.

The `bin/` directory contains the final test executable.

Both `obj/` and `bin/` contain build artifacts and are ignored by Git.

---

## Build System

MyLib uses GNU Make to manage compilation and testing.

Source files are compiled individually into object files before being linked into the final executable.

For example:

```text
src/vector.c        → obj/vector.o
tests/test_main.c   → obj/test_main.o
tests/test_vector.c → obj/test_vector.o

                         ↓

                    bin/tests
```

This allows Make to avoid recompiling unchanged source files and only rebuild what is necessary.

Header files are also tracked as build dependencies so changes to the library or test headers trigger recompilation.

---

## Building

### Linux

Requirements:

- GCC
- GNU Make

Build the project with:

```bash
make
```

The resulting executable will be created at:

```text
bin/tests
```

### Windows

MyLib can be built on Windows using MSYS2 with the UCRT64 environment.

Requirements:

- MSYS2 UCRT64
- GCC (MinGW-w64 UCRT64)
- MinGW-w64 Make

Using the native MinGW Make executable:

```powershell
mingw32-make
```

If `mingw32-make` is aliased to `make` in PowerShell:

```powershell
make
```

The resulting executable will be created at:

```text
bin\tests.exe
```

---

## Testing

The project includes a test suite covering the public Vector API.

Run the tests with:

```bash
make test
```

The test system is split into separate components:

```text
tests/test_common.h
```

Contains shared test utilities, counters, output formatting, and the `TEST` macro.

```text
tests/test_vector.h
tests/test_vector.c
```

Contain the Vector test suite.

```text
tests/test_main.c
```

Acts as the central test runner and executes the available test suites.

The test executable returns a failure exit status when one or more tests fail, allowing the same suite to be used both locally and in Continuous Integration.

---

## Cleaning

Remove generated object files and the test executable with:

```bash
make clean
```

This removes build artifacts from:

```text
obj/
bin/
```

The directories themselves may remain, but their generated build files are removed.

---

## Continuous Integration

MyLib uses GitHub Actions to automatically build and test the project.

The CI pipeline runs on:

| Platform | Compiler | Build Tool | Status |
| --- | --- | --- | --- |
| Linux | GCC | GNU Make | ✅ |
| Windows | GCC (MSYS2 UCRT64) | MinGW-w64 Make | ✅ |

The test suite runs automatically on pushes and pull requests.

This helps ensure that changes remain compatible with both supported platforms.

---

## Current Limitations

The Vector currently stores only `char` values.

This is intentional while the core API, memory management, testing infrastructure, and build system are being developed and stabilized.

A future version is planned to support generic element types.

---

## Roadmap

### Vector

- [x] Dynamic allocation
- [x] Automatic capacity growth
- [x] Push
- [x] Insert
- [x] Pop
- [x] Remove
- [x] Get
- [x] Set
- [x] First
- [x] Last
- [x] Find
- [x] Contains
- [x] Count
- [x] Swap
- [x] Reverse
- [x] Copy
- [x] Reserve
- [x] Shrink to fit
- [x] Clear
- [x] Size and capacity queries
- [x] Empty checks
- [x] Memory cleanup
- [ ] Resize
- [ ] Generic element support

### Infrastructure

- [x] Public header structure
- [x] Automated test suite
- [x] Modular test architecture
- [x] Makefile
- [x] Object-based compilation
- [x] Incremental builds
- [x] Header dependency tracking
- [x] Build artifact cleanup
- [x] Linux support
- [x] Windows support
- [x] Continuous Integration
- [x] Linux CI
- [x] Windows CI

### Future

- [ ] Generic Vector
- [ ] Map / Dictionary
- [ ] Additional data structures
- [ ] Additional utility modules
- [ ] Expanded cross-platform testing

---

## Design Goals

MyLib is designed around a few simple goals:

- Learn how common data structures work internally
- Practice manual memory management
- Build reusable C utilities from scratch
- Maintain a small and understandable codebase
- Keep the public API consistent and predictable
- Test behavior across multiple platforms
- Eventually use the library in real-world personal C projects

The goal is not to replace established C libraries, but to build a practical library while developing a deeper understanding of systems programming and data structure implementation.

---

## License

This project is licensed under the MIT License.

See the `LICENSE` file for details.