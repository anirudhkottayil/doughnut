# doughnut.c

A spinning 3D donut, rendered entirely in ASCII and animated live in your terminal.

## Build

```bash
gcc doughnut.c -o doughnut -lm
```

## Run

```bash
./doughnut
```

`Ctrl+C` to stop.

## Tweak it

A few constants near the top of `main`:

- `R`, `r` — overall size and tube thickness
- `tilt` — fixed viewing angle
- the `A +=` / `B +=` lines — how fast it spins

No dependencies beyond a C compiler and libm.
