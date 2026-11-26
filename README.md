# Student Grade Management System — V1.2

## Overview

V1.2 extends the Student Grade Management System with copy-control functionality and stream-based input/output. The existing grade-management logic and workflows should remain unchanged.

## V1.2 objectives

- Implement the Rule of Three in the `Student` class:
  - Copy constructor
  - Copy assignment operator
  - Destructor
- Overload `operator<<` and `operator>>` for `Student`.
- Demonstrate that the stream operators work with both console streams and file streams.
- Preserve the existing grade calculations, student handling, and other V1.2 project functionality.

## Key implementation details

| Feature | Description |
|---|---|
| Copy constructor | Creates a new `Student` by copying another student's data. |
| Copy assignment operator | Copies data into an already-existing `Student`; handles self-assignment. |
| Destructor | Performs the class's required cleanup. |
| `operator<<` | Writes a student's information to the supplied output stream. |
| `operator>>` | Reads a student's information from the supplied input stream. |

The stream operators should use the stream passed to them rather than directly using `cout` or `cin`. This allows the same operators to work with console and file streams.

1. **Rule of Three demonstration** — show the relevant test/output proving that copying and assignment work as expected.
2. **Stream operator demonstration** — show student input/output using `operator>>` and `operator<<`.
3. **File I/O demonstration** — include this only if it is a distinct required demonstration in your implementation; show data being written to and/or read from a file.

<img width="405" height="105" alt="Screenshot 2026-11-26 191414" src="https://github.com/user-attachments/assets/90b6d2af-f9a4-48d6-8126-8250c861a8ce" />

## Build and run

Use the build instructions configured for this repository. For a CMake project, a typical workflow is:

```bash
cmake -S . -B build
cmake --build build
```

Run the generated executable from the build directory appropriate to your environment.
