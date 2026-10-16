# Assignment5_NaySanHtut

## Files
- `pixel.h` — defines the Pixel struct
- `main.cpp` — main program and function implementations
- `pixels.dat` — input file (131,072 pixels in `x,y,r,g,b` format)
- `flipped.dat` — output file with the vertically flipped image

## How to Compile
```bash
g++ -std=c++11 -Wall -o main main.cpp
```

## How to Run
```bash
./main <input file>
```
Example:
```bash
./main pixels.dat
```
This prints the average r, g, b values and creates `flipped.dat` in the same folder.

## How to Check the Output
```bash
wc -l flipped.dat
head -3 flipped.dat
```
- `wc -l` counts the lines. It should print `131072 flipped.dat` (512 x 256 pixels).
- `head -3` shows the first 3 lines, which should be in the `x,y,r,g,b` format and start with `0,0,...`, `0,1,...`, `0,2,...`.

To check that the flip worked, row 0 of the first column in the input should appear as row 255 in the output:
```bash
head -1 pixels.dat
sed -n '256p' flipped.dat
```
The r, g, b values on those two lines should match (the number of printed digits may differ slightly).

## Troubleshooting
- `No such file or directory` when compiling: you are in the wrong folder. Use `cd` to move into the repository folder.
- `Could not open pixels.dat`: `pixels.dat` is not in the folder you ran the program from.
- `Usage: ./main <input file>`: you forgot to give the input file. Run `./main pixels.dat`.
- `g++: command not found`: the compiler is not installed on that machine.
