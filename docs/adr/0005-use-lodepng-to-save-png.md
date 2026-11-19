# 5. Use LodePNG to save images as PNG

## Context

The ray tracer must write its images to disk. PNG is lossless (the studio needs the
same input to always give exactly the same image) and every image tool opens it.
Writing a PNG encoder ourselves (zlib compression, CRC checksums, chunks) is a
project of its own and not the client's problem.

The library must build inside our dev container on any machine, with no system
package to install, and be simple enough for the team to understand.

Options considered:

| Option          | For                                                                          | Against                                          |
| --------------- | ---------------------------------------------------------------------------- | ------------------------------------------------ |
| **LodePNG**     | 2 files (`lodepng.h`, `lodepng.cpp`), no dependencies, C++ API, zlib licence | No release tags: must pin a commit               |
| libpng          | The reference implementation, very widely used                               | C API, needs zlib, installed as a system package |
| stb_image_write | Single header, no dependencies                                               | C API, written for speed rather than readability |
| Write our own   | No dependency                                                                | Large amount of work and risk                    |

## Decision

We use **LodePNG**, fetched by CMake with `FetchContent` from
<https://github.com/lvandeve/lodepng>, pinned to commit
`7b2893e35891c0c85bee5595caafaf3c2044b409`, and built as a small static library.

Only `src/io/png_saver.cpp` includes LodePNG. The rest of the code saves images through
the `ImageSaver` interface (Strategy pattern), and `PngSaver` is the only class that
knows about LodePNG.

## Status

Accepted

## Consequences

- No system package: the first configure downloads LodePNG, as for Catch2 (ADR 3).
- The pinned commit makes builds reproducible. Updating LodePNG means changing the
  commit hash on purpose.
- Replacing LodePNG, or adding another format (e.g. EXR), means writing a new
  `ImageSaver`. No other class changes.
- Colours are stored as `double` and converted to 8 bits per channel when saving.
  Values outside [0, 1] are clamped.
