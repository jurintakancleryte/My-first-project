# Student Grade Management System — V1.5

## Overview

V1.5 extends the V1.2 Student Grade Management System by introducing an abstract base class, `Human`, and deriving `Student` from it. The existing V1.2 functionality should continue to work.

> The assignment wording previously shared used both `Man` and `Human`. This README uses `Human`, matching the class name selected for the implementation. Confirm the required name with the instructor if the exact name is assessed.

## V1.5 objectives

- Create an abstract base class named `Human`.
- Make it impossible to instantiate `Human` directly.
- Derive `Student` publicly from `Human`.
- Move shared person information, such as first and last name, into `Human`.
- Implement the pure virtual `print()` function in `Student`.
- Preserve the Rule of Three functionality introduced in V1.2.
- Preserve the existing V1.2 grade-management and stream/file I/O functionality.

## Class design

### `Human`

`Human` stores the shared person information and declares a pure virtual function:

```cpp
virtual void print(std::ostream& out) const = 0;
```

The pure virtual function makes `Human` an abstract class. Its objects cannot be instantiated directly.

### `Student`

`Student` publicly inherits from `Human` and implements:

```cpp
void print(std::ostream& out) const override;
```

Student-specific information, such as grades and student identifiers, remains in `Student`. Shared first-name and last-name fields should not be duplicated in the derived class.

## Inheritance structure

```text
       Human (abstract)
              |
              | public inheritance
              v
           Student
```

<img width="416" height="48" alt="Screenshot 2026-11-26 192119" src="https://github.com/user-attachments/assets/7dd1ea45-4801-4c0b-853e-1e3c00c1de9d" />

<img width="1133" height="540" alt="paveikslas" src="https://github.com/user-attachments/assets/a0b8ac25-ea8c-4167-87e1-dae5b6804d61" />


## Rule of Three with inheritance

| Special member function | Expected responsibility |
|---|---|
| Copy constructor | Copies the inherited `Human` data and the `Student`-specific data. |
| Copy assignment operator | Assigns both the base-class portion and the derived-class portion; handles self-assignment. |
| Destructor | Cleans up the derived object; the base-class destructor is called automatically. |

The base class should have a virtual destructor so that deleting a derived object through a base-class pointer is safe.

## Build and run

For a CMake project, a typical workflow is:

```bash
cmake -S . -B build
cmake --build build
```
