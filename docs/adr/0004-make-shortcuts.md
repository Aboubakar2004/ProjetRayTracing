# 4. Short `make` commands for everyday tasks

## Context

The CMake commands are long and easy to get wrong (`cmake --preset debug`,
`cmake --build --preset debug`, `ctest --preset debug`, then the path of the executable).
Team members, and the AI working with them, run them many times a day.

Options considered:

- **Keep the raw commands only:** nothing to maintain, but they are hard to remember.
- **Shell scripts** (`build.sh`, `test.sh`, ...): one file per task, and they don't run
  as-is on Windows outside the container.
- **A small Makefile wrapping CMake:** one file, well-known names, and `make` is already
  in the container.

## Decision

We add a `Makefile` at the root of the repository with four targets. They only call
CMake: the real build stays in CMake (ADR 2).

| Command      | Does                                                                            |
| ------------ | ------------------------------------------------------------------------------- |
| `make build` | configure and build with the `debug` preset                                     |
| `make run`   | build, then run the renderer (`./build/debug/render`, which writes `image.png`) |
| `make test`  | build, then run all the tests with CTest                                        |
| `make clean` | delete the `build/` folder                                                      |

## Status

Accepted

## Consequences

- Four short commands to remember, documented in the README and in `AGENTS.md`.
- The commands must be run from the root of the repository, inside the dev container:
  `make` does not exist in Windows PowerShell.
- The Makefile must be kept in line with the presets and the executable names. For
  example, `make run` was updated when the renderer replaced the `hello` demo.
- `make clean` is also the fix when the CMake cache points to another folder.
