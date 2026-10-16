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

## Troubleshooting
- `No such file or directory` when compiling: you are in the wrong folder. Use `cd` to move into the repository folder.
- `Could not open pixels.dat`: `pixels.dat` is not in the folder you ran the program from.
- `Usage: ./main <input file>`: you forgot to give the input file. Run `./main pixels.dat`.
- `g++: command not found`: the compiler is not installed on that machine.
