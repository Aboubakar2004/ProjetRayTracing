# 2. Build with CMake, and run tests with CTest

## Context

The ray tracer is made of many C++ files, a library, executables, tests and
third-party code. We need a build description that:

- works with several compilers (GCC and Clang in the container, MSVC if needed);
- can download and build dependencies;
- runs the tests with one command;
- is understood by editors and by the next maintainers.

Options considered:

- **Hand-written Makefile:** simple to start, but hard to maintain, tied to one platform,
  and with no standard way to handle dependencies.
- **Meson or Bazel:** modern, but less common in C++ teams, with fewer resources for the team.
- **CMake:** the de-facto standard for C++, supported by all major editors, with
  `FetchContent` for dependencies and CTest for tests.

## Decision

We use **CMake** (minimum 3.20), with **C++20**, and the **Ninja** generator.

- `CMakePresets.json` defines a `debug` and a `release` preset, which build into
  `build/debug/` and `build/release/`.
- All the logic lives in a library, `raytracer_core` (`src/`). The executables (`app/`)
  and the tests (`tests/`) link to it.
- Warnings are turned on: `-Wall -Wextra -Wpedantic` (`/W4` with MSVC).
- **CTest** runs the tests: `ctest --preset debug`.
- Third-party code is fetched with `FetchContent` and pinned to a version.

## Status

Accepted

## Consequences

- One way to build, on every platform, and editors understand the project directly
  through `compile_commands.json`.
- Every new `.cpp` file must be added by hand to `raytracer_core` (or to `unit_tests`
  for a test), and forgetting it gives a link error.
- CMake has its own language, which the team must learn.
- The `build/` folder is generated: it is ignored by git and can be deleted at any time.
