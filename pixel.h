#ifndef PIXEL_H
#define PIXEL_H

// rgb are in the range 0 to 1
// xy are the locations of the pixels on the screen

struct _pixel {
    float r;
    float g;
    float b;
    int x;
    int y;
};
typedef struct _pixel Pixel;

#endif
