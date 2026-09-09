# MyLib

![Language](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-in%20development-yellow)

A lightweight C library implementing data structures and utilities from scratch, built for learning, experimentation, and real-world use.

MyLib explores how common data structures work under the hood by implementing them directly in C, with explicit memory management, predictable APIs, and a growing automated test suite.

The project currently provides a dynamic vector implementation and is designed to expand with additional data structures and utilities over time.

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
├── bin/
├── inc/
│   └── mylib/
│       ├── common.h
│       └── vector.h
├── src/
│   └── vector.c
├── tests/
│   └── test_vector.c
├── LICENSE
└── README.md
```

Public headers are kept under `inc/mylib`, while implementations live in `src` and tests are isolated under `tests`.

---

## Building

Compile a program using MyLib with:

```bash
gcc -Wall -Wextra -Wpedantic \
    -Iinc src/vector.c main.c \
    -o bin/main
```

Then run:

```bash
./bin/main
```

---

## Testing

MyLib includes an automated test suite covering the public vector API.

Compile the tests with:

```bash
gcc -Wall -Wextra -Wpedantic \
    -Iinc src/vector.c tests/test_vector.c \
    -o bin/test_vector
```

Run them with:

```bash
./bin/test_vector
```

### AddressSanitizer

For additional memory checking, compile the test suite with AddressSanitizer:

```bash
gcc -Wall -Wextra -Wpedantic \
    -fsanitize=address -g \
    -Iinc src/vector.c tests/test_vector.c \
    -o bin/test_vector
```

Then run:

```bash
./bin/test_vector
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

The goal is not only to recreate existing abstractions, but to understand what those abstractions are doing underneath.

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

### Future

- [ ] Map / dictionary
- [ ] Additional data structures
- [ ] Additional utility modules
- [ ] Improved build system
- [ ] Continuous integration

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

---

## Status

MyLib is currently under active development.

The vector implementation is usable and tested, but the library is still evolving and breaking API changes may occur before a stable release.

---

## License

MyLib is licensed under the MIT License.

You are free to use, modify, distribute, and include MyLib in personal, open-source, or commercial projects under the terms of the license.

See the `LICENSE` file for details.