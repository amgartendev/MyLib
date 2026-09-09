# MyLib

MyLib is a personal C library created to explore and implement common data structures and utilities from scratch.

The project currently includes a dynamic vector implementation with automatic capacity management, element access, insertion, removal, search, copy, reverse operations, and explicit memory control.

> Current limitation: the vector stores `char` elements only.
> Generic element support is planned for a future version.

## Features

- Dynamic vector allocation
- Automatic capacity growth
- Push and insert
- Pop and remove
- Get, set, first and last
- Find, count and contains
- Swap and reverse
- Copy
- Reserve
- Shrink to fit
- Clear and free
- Consistent error handling
- Public API tests

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

## Building

Compile a program using MyLib with:

```bash
gcc -Iinc src/vector.c main.c -o bin/main
```

## Running Tests

Compile the vector test suite:

```bash
gcc -Wall -Wextra -Wpedantic -Iinc \
    src/vector.c tests/test_vector.c \
    -o bin/test_vector
```

Then run:

```bash
./bin/test_vector
```

For additional memory checking with AddressSanitizer:

```bash
gcc -Wall -Wextra -Wpedantic -fsanitize=address -g \
    -Iinc src/vector.c tests/test_vector.c \
    -o bin/test_vector

./bin/test_vector
```

## Roadmap

- Expand vector test coverage
- Add more vector operations
- Convert vector storage to generic elements
- Introduce additional data structures
- Add map/dictionary support

## Status

MyLib is currently an experimental learning project.

The vector implementation is usable, but the API may still change while the library evolves.

## License

This project is licensed under the MIT License.

See the `LICENSE` file for details.