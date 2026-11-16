# Discovery report

## Problem statement

A Los Angeles film studio needs its own rendering tools so the team who works on it can understand it, fix it, and improve it easily because their previous tool is broken and nobody can fix it, however they got a commercial tool which costs $2M but the tool doesn't fit their needs.

## Client interview summary

### Maintainability

**Need:** The team must be able to understand and fix the renderer, even after its author leaves.

> **Q (classmate):** "Walk me through the last time you rendered a project."
>
> **A:** "We kept finding black artifacts in the images [...] Nobody could tell us why. [...] And we delivered 3 weeks later."

**My conclusion:** Readable, tested and documented code is the main need.

### Cost

**Need:** Much cheaper than today's licences.

> **Q (classmate):** "What did you spend on rendering last year?"
>
> **A:** "Over $2 million for the license." Later: "We would like to spend no more than €500,000."

### Success criteria

**Need:** Same input, same image, and any anomaly explained within the same day.

> **Q (classmate):** "What will demonstrate that it fits your needs?"
>
> **A:** "If I give it some inputs, I can always expect the same output. [...] If there is an image anomaly, we can figure out within the same day why."

### Performance

**Need:** A film rendered in 2 months at most, CPU only, on up to 100 machines.

> **Q (classmate):** "What kind of hardware do you have?"
>
> **A:** "Everything must be rendered by the CPU." And: "We have up to 100 machines." And: "No more than 2 months for [...] final rendering."

**My conclusion:** 90 minutes at 24 fps (to confirm) is 129,600 frames, so about 1 hour per frame per machine.

### Open questions

- Resolution and frame rate of the film?
- Input scene format and output image format?
- Does the €500,000 cover maintenance too?

## State of the art

| Solution  | Maker              | Licence     | Pricing (date checked)                                       | Capabilities             | Sources                                                                               |
| --------- | ------------------ | ----------- | ------------------------------------------------------------ | ------------------------ | ------------------------------------------------------------------------------------- |
| RenderMan | Pixar              | Proprietary | $595/license + $250/year (16 Nov 2026)                       | Film production renderer | [Pixar](https://renderman.pixar.com/store/)                                           |
| Arnold    | Autodesk           | Proprietary | Not published by Autodesk; $649.99/year at CDW (16 Nov 2026) | Film and TV ray tracer   | [CDW](https://www.cdw.com/product/arnold-2026-new-subscription-annual-1-seat/8331003) |
| Cycles    | Blender Foundation | Open source | Free (16 Nov 2026)                                           | Path tracer in Blender   | [Cycles](https://www.cycles-renderer.org/)                                            |

Commercial renderers are paid per machine and closed. Open-source ones are free but not controlled by the studio.

## What is ray tracing?

A scene (objects, lights, camera) goes in, an image comes out. For each pixel, a ray goes from the camera into the scene, finds the first object it hits, and its colour is computed from the material and the lights.

**Sources:** [Ray Tracing in One Weekend](https://raytracing.github.io/), [Physically Based Rendering](https://pbr-book.org/).

## What is C++?

### Programming paradigms

Procedural, object-oriented and generic. Unlike PHP and JavaScript, it is compiled and statically typed.

### What to watch out for

No garbage collector: memory leaks, invalid pointers, undefined behaviour, integer division.

### Shaping the domain model

Classes named with the client's words (ray, sphere, scene), and a shape interface so new shapes can be added without changing existing code.

**Sources:** [learncpp.com](https://www.learncpp.com/), [cppreference.com](https://en.cppreference.com/).
