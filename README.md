# MyLib

[![Vector Tests](https://github.com/amgartendev/MyLib/actions/workflows/tests.yaml/badge.svg)](https://github.com/amgartendev/MyLib/actions/workflows/tests.yaml)
![Language](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-in%20development-yellow)

A lightweight C library implementing data structures and utilities from scratch, built for learning, experimentation, and real-world use.

MyLib explores how common data structures work under the hood by implementing them directly in C, with explicit memory management, predictable APIs, and a growing automated test suite.

The project currently provides a dynamic vector implementation and is designed to expand with additional data structures and utilities over time.

MyLib is developed and continuously tested on both Linux and Windows.

> **Current limitation:** the vector stores `char` elements only.
> Generic element support is planned for a future version.

---

## Features

### Dynamic Vector

The current vector implementation includes:

- Dynamic memory allocation
- Automatic capacity growth
- Push and insert operations
- Pop and remove operations
- Indexed element access
- Get and set operations
- First and last element access
- Find elements
- Count occurrences
- Contains checks
- Swap elements
- Reverse vectors
- Deep vector copying
- Manual capacity reservation
- Shrink-to-fit
- Clear and free operations
- Consistent status/error handling

The vector manages its own capacity automatically, growing when additional storage is required while keeping logical size and allocated capacity separate.

---

## Example

```c
#include <stdio.h>

#include "mylib/vector.h"

int main(void) {
    Vector_t *v = vec_init(2);

    if (v == NULL) {
        return 1;
    }

    char a = 'A';
    char b = 'B';
    char c = 'C';

    vec_push(v, &a);
    vec_push(v, &b);
    vec_push(v, &c);

    vec_output(v);

    vec_free(v);

    return 0;
}
```

MyLib handles the vector's capacity internally. In the example above, inserting the third element automatically grows the allocated storage when necessary.

---

## Project Structure

```text
MyLib/
├── .github/
│   └── workflows/
│       └── tests.yaml
├── bin/
├── inc/
│   └── mylib/
│       ├── common.h
│       └── vector.h
├── src/
│   └── vector.c
├── tests/
│   └── test_vector.c
├── .gitignore
├── LICENSE
├── Makefile
└── README.md
```

Public headers are kept under `inc/mylib`, implementations live in `src`, and tests are isolated under `tests`.

---

## Building

MyLib uses a Makefile to manage compilation on both Linux and Windows.

### Linux

Make sure GCC and GNU Make are installed.

Build the project with:

```bash
make
```

The test executable is generated at:

```text
bin/tests
```

### Windows

The supported Windows toolchain is GCC through MSYS2 UCRT64.

With MSYS2 UCRT64 and the MinGW-w64 GCC and Make packages installed, build the project with:

```powershell
mingw32-make
```

The test executable is generated at:

```text
bin\tests.exe
```

If `mingw32-make` is aliased to `make` in your PowerShell environment, you can also use:

```powershell
make
```

The Makefile automatically detects Windows and adjusts the executable path and platform-specific commands accordingly.

---

## Testing

MyLib includes an automated test suite covering the public vector API.

### Linux

Build and run the tests with:

```bash
make test
```

Clean the generated executable with:

```bash
make clean
```

### Windows

Build and run the tests with:

```powershell
mingw32-make test
```

Clean the generated executable with:

```powershell
mingw32-make clean
```

If `mingw32-make` is aliased to `make`, the equivalent commands are:

```powershell
make test
make clean
```

---

## Continuous Integration

Every push and pull request is automatically built and tested through GitHub Actions on both:

- Ubuntu with GCC and GNU Make
- Windows with GCC and MinGW-w64 Make through MSYS2 UCRT64

The CI matrix ensures that changes to MyLib continue to compile and pass the vector test suite on both supported platforms.

---

### AddressSanitizer

For additional memory checking on supported environments, the test suite can be compiled manually with AddressSanitizer:

```bash
gcc -Wall -Wextra -Werror -Wpedantic \
    -fsanitize=address -g \
    -Iinc src/*.c tests/test_*.c \
    -o bin/tests
```

Then run:

```bash
./bin/tests
```

AddressSanitizer can help detect problems such as invalid memory accesses, use-after-free errors, and memory leaks.

---

## Design Philosophy

MyLib is built around a few simple ideas:

- Understand data structures by implementing them from scratch
- Keep memory ownership explicit
- Separate logical size from allocated capacity
- Prefer small and predictable APIs
- Handle errors explicitly
- Test public behavior rather than internal implementation details
- Keep the implementation understandable before making it clever
- Keep platform-specific build behavior separate from library logic

The goal is not only to recreate existing abstractions, but to understand what those abstractions are doing underneath.

---

## Platform Support

MyLib currently targets:

| Platform | Compiler | Build Tool | CI |
| --- | --- | --- | --- |
| Linux | GCC | GNU Make | ✅ |
| Windows | GCC (MSYS2 UCRT64) | MinGW-w64 Make | ✅ |

The library implementation itself relies on standard C functionality and does not currently depend on platform-specific operating system APIs.

Platform-specific differences required for building and running the test suite are handled by the Makefile.

---

## Roadmap

### Vector

- [x] Dynamic allocation
- [x] Automatic capacity growth
- [x] Push / pop
- [x] Insert / remove
- [x] Get / set
- [x] First / last
- [x] Find / contains / count
- [x] Swap / reverse
- [x] Deep copy
- [x] Reserve
- [x] Shrink-to-fit
- [x] Clear / free
- [x] Automated API tests
- [ ] Generic element storage
- [ ] Additional vector operations
- [ ] Opaque vector type

### Infrastructure

- [x] Makefile build system
- [x] Linux support
- [x] Windows support
- [x] Continuous integration
- [x] Linux CI testing
- [x] Windows CI testing

### Future

- [ ] Map / dictionary
- [ ] Additional data structures
- [ ] Additional utility modules

---

## Why MyLib?

Many languages provide dynamic arrays, maps, and other containers out of the box.

C does not.

MyLib is an exploration of what happens underneath those abstractions: allocation, reallocation, capacity management, element movement, ownership, error handling, and API design.

Instead of treating those details as implementation magic, MyLib makes them part of the project.

---

## Contributing

Contributions, suggestions, bug reports, and discussions are welcome.

MyLib is still evolving, so APIs may change as new data structures are introduced and existing implementations are improved.

If you find a bug or have an idea for an improvement, feel free to open an issue or submit a pull request.

When contributing changes, make sure the test suite passes on the supported platforms.

---

## Status

MyLib is currently under active development.

The vector implementation is usable and tested on both Linux and Windows, but the library is still evolving and breaking API changes may occur before a stable release.

---

## License

MyLib is licensed under the MIT License.

You are free to use, modify, distribute, and include MyLib in personal, open-source, or commercial projects under the terms of the license.

See the `LICENSE` file for details.