# AGENTS.md

C++20 ray tracer built with CMake, CTest and Catch2, inside a dev container (see README.md).

## Commands

Run inside the dev container:

```sh
cmake --preset debug            # configure
cmake --build --preset debug    # build
./build/debug/hello             # run the demo
ctest --preset debug            # run all tests
```

Shortcuts: `make build`, `make run`, `make test`, `make clean`.

## Architecture decisions

- Our architecture decisions are in `docs/adr/`. Read them before changing the build, the tools or the test setup.
- Never go against an accepted ADR. To change a decision, write a new ADR with status Proposed and ask the user.
- Never set an ADR's status to Accepted. Only the user does that.

## Code style

- All private member variables must have a `_` prefix (e.g. `_x`).
