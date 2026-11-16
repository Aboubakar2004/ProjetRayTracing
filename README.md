# ProjetRayTracing

A ray tracer in C++, built for a film studio as part of the Tech-Lead module.

## Documentation

- [Discovery report](docs/discovery/discovery-report.md)

## Getting started

### Toolchain strategy

Everyone builds inside the same **dev container** (Ubuntu 24.04, GCC, Clang, CMake, Ninja),
so the build is identical on Windows, macOS and Linux. The project itself is plain
CMake (C++20) and also builds natively if you already have a toolchain.

**VS Code:** install Docker and the *Dev Containers* extension, open the repo, then run
`Dev Containers: Reopen in Container`.
**Zed / other editors:** use the dev-container support, or run commands through Docker:

```sh
docker build -t rt-dev .devcontainer
docker run --rm -it -v "$PWD":/ws -w /ws rt-dev bash
```

### Build and run (inside the container)

```sh
cmake --preset debug            # configure (first run downloads Catch2)
cmake --build --preset debug    # compile
./build/debug/hello             # prints: Hello, world!
./build/debug/hello Alice       # prints: Hello, Alice!
```

Shortcuts: `make build`, `make run`, `make test`, `make clean` (wrappers around the commands above).

Use the `release` preset for optimised builds (`build/release/`).

## Testing (TDD)

Unit tests use [Catch2 v3](https://github.com/catchorg/Catch2), integrated with CTest.

```sh
ctest --preset debug                      # run all tests
./build/debug/tests/unit_tests            # run directly, more detail
./build/debug/tests/unit_tests "[greeting]"   # only tests with a tag
```

TDD loop:

1. Add a failing `TEST_CASE` in `tests/` (new file: add it to `add_executable(unit_tests ...)` in `tests/CMakeLists.txt`).
2. `cmake --build --preset debug && ctest --preset debug` → see it **fail**.
3. Write the minimum code in `src/lib/` (add new `.cpp` files to `raytracer_core` in the root `CMakeLists.txt`) to make it pass.
4. Refactor, re-run, commit.

## Layout

```
.devcontainer/   dev container definition
app/             executables (hello)
src/lib/         raytracer_core library (all testable logic)
tests/           Catch2 unit tests
```
