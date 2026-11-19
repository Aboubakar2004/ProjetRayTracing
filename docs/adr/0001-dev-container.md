# 1. Build inside a dev container

## Context

The team works on Windows, macOS and Linux. A C++ project depends on its toolchain:
compiler and version, CMake, build tool, debugger. If everyone installs these by hand,
builds differ from one machine to another ("it works on my machine"). The client also
asked for the same input to always give the same output, which starts with the same
build.

Options considered:

- **Install the tools on each machine:** nothing to learn, but versions drift, and
  Windows needs a different setup (MSVC or MinGW).
- **A virtual machine:** fully isolated, but heavy and slow to share.
- **A dev container** (a Docker image described in the repository): the same Linux
  environment for everyone, opened directly by VS Code and other editors.

## Decision

Everyone builds, runs and tests inside the dev container described in `.devcontainer/`:

- Ubuntu 24.04, with GCC (`build-essential`), Clang, CMake, Ninja, Git, GDB,
  clang-format and clangd;
- the non-root user `ubuntu`;
- the VS Code extensions CMake Tools, C/C++ and clangd, with the `debug` preset selected.

`.gitattributes` forces LF line endings, so files are identical on Windows and Linux.

## Status

Accepted

## Consequences

- One documented environment: a new team member opens the repository in the container
  and can build straight away.
- Docker Desktop must be installed and running. Without it, `make` and `cmake` are not
  available, because nothing is installed on the host.
- The first container build takes a few minutes, since it downloads the Ubuntu packages.
- The project is still plain CMake, so it can also be built without the container by
  anyone who already has a toolchain.
- Ubuntu package versions are not pinned, so rebuilding the image later can bring newer
  tool versions.
