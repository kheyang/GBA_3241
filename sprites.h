#include "gba.h"

#define NCOLS 20

// RGB palette used for sprites. The sprites defined below use the index of the color in the palette (so black = 0, white = 1, ...)
int palette[] = {
RGB(0,0,0), // pure black 0
RGB(31,31,31), // pure white 1
RGB(0,31,31), // light blue 2
RGB(26,26,26), // light grey 3
RGB(9,9,9), // darkest grey 4
RGB(31,31,0), // pure yellow 5
RGB(31,0,0), // pure red 6
RGB(0,0,31), // pure blue 7
RGB(11,8,3), // dark brown 8
RGB(27,27,27), // lightest grey 9
RGB(16,16,16), // dark grey 10
RGB(31,17,17), // light red 11
RGB(31,24,24), // lighter red 12
RGB(27,0,0), // dark red 13
RGB(0,16,0), // darkest green 14
RGB(0,31,0), // pure green 15
RGB(16,31,16), // light green 16
RGB(23,31,23) // lightest green 17
};


// Sprite array, defining each big 16x16 sprite as 4 8x8 tiles, using the palette above

u16 sprites[] = {
#define S_LR 0 // Shooter Looking RIGHT
// Tile 00
0,0,0,0,0,0,1,1,
0,0,0,0,0,1,1,2,
0,0,0,0,0,1,2,2,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,4,4,4,1,4,4,
0,0,4,4,4,1,4,4,
0,0,4,4,4,1,1,2,
// Tile 01
1,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,
2,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,
4,4,4,4,4,4,0,0,
4,4,4,4,4,4,0,0,
4,4,2,4,4,4,0,0,
// Tile 02
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,0,0,0,2,2,2,
0,0,0,0,0,2,2,2,
0,0,0,0,0,2,2,2,
0,0,0,0,0,2,2,2,
0,0,0,0,0,3,1,1,
// Tile 03
1,1,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,

#define S_LL 1 // Shooter Looking LEFT
// Tile 00
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,11,
0,0,0,0,0,0,0,11,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,1,1,
0,0,4,4,4,4,4,4,
0,0,4,4,4,4,4,4,
0,0,4,4,4,11,4,4,
// Tile 01
1,1,0,0,0,0,0,0,
11,1,1,0,0,0,0,0,
11,11,1,0,0,0,0,0,
1,1,1,1,0,0,0,0,
1,1,1,1,0,0,0,0,
4,4,1,4,4,4,0,0,
4,4,1,4,4,4,0,0,
11,1,1,4,4,4,0,0,
// Tile 02
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,1,1,
// Tile 03
1,1,1,1,0,0,0,0,
1,1,1,1,0,0,0,0,
1,1,1,1,0,0,0,0,
11,11,11,0,0,0,0,0,
11,11,11,0,0,0,0,0,
11,11,11,0,0,0,0,0,
11,11,11,0,0,0,0,0,
1,1,3,0,0,0,0,0,

#define A_L_NF 2 // Astro looking Left with NO FIRE
// Tile 00
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,2,
0,0,0,0,0,0,0,2,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,
0,0,0,0,3,1,1,1,
0,0,0,0,0,0,0,0,
// Tile 01
1,1,0,0,0,0,0,0,
2,1,1,0,0,0,0,0,
2,2,1,0,0,0,0,0,
1,1,0,0,3,0,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,4,3,4,0,
// Tile 02
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
// Tile 03
1,1,1,3,4,3,4,0,
1,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
1,1,3,0,0,0,0,0,

#define A_L_F 3 // Astro looking Left with FIRE
// Tile 00
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,2,
0,0,0,0,0,0,0,2,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,
0,0,0,0,3,1,1,1,
0,0,0,0,0,0,0,0,
// Tile 01
1,1,0,0,0,0,0,0,
2,1,1,0,0,0,0,0,
2,2,1,0,0,0,0,0,
1,1,0,0,3,0,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,3,3,0,0,
1,1,1,3,4,3,4,0,
// Tile 02
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
// Tile 03
1,1,1,3,4,3,4,0,
1,1,1,5,6,5,0,0,
0,1,1,5,6,5,0,0,
0,1,1,0,5,0,0,0,
0,1,1,0,5,0,0,0,
0,1,1,0,0,0,0,0,
0,1,1,0,0,0,0,0,
1,1,3,0,0,0,0,0,

#define PLATFORM_L 4 // platform left edge
// Tile 00
1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,

// Tile 01
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 02
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,

// Tile 03
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,

#define PLATFORM_M PLATFORM_L+1 // Platform middle part

// Tile 00
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 01
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 02
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,

// Tile 03
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,

#define PLATFORM_R PLATFORM_M+1 // Platform Right Edge

// Tile 00
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 01
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,

// Tile 02
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,

// Tile 03
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,

#define PLATFORM8_L 7
// Tile 00
1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,

// Tile 01
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 02
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 03
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

#define PLATFORM8_R PLATFORM8_L+1

// Tile 00
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 01
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,

// Tile 02
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 03
1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

#define LIFE_1 9

// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,6,6,6,0,0,
0,0,6,12,12,11,6,0,
0,6,12,11,11,6,6,6,
0,6,12,11,6,6,6,6,
0,6,12,11,6,6,6,6,
0,0,6,12,11,6,6,6,
0,0,0,6,12,11,6,6,

// Tile 01
0,0,0,0,0,0,0,0,
0,0,6,6,6,0,0,0,
0,6,12,12,11,6,0,0,
6,12,11,6,6,6,6,0,
6,11,11,6,6,6,6,0,
6,6,6,6,6,6,6,0,
6,6,6,6,6,6,0,0,
6,6,6,6,6,0,0,0,

// Tile 02
0,0,0,6,12,11,6,6,
0,0,0,0,6,12,6,6,
0,0,0,0,6,12,11,6,
0,0,0,0,0,6,11,6,
0,0,0,0,0,0,6,6,
0,0,0,0,0,0,6,6,
0,0,0,0,0,0,0,6,
0,0,0,0,0,0,0,0,

// Tile 03

6,6,6,6,6,0,0,0,
6,6,6,6,0,0,0,0,
6,6,6,0,0,0,0,0,
6,6,6,0,0,0,0,0,
6,6,0,0,0,0,0,0,
6,6,0,0,0,0,0,0,
6,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

#define LIFE_2 LIFE_1+1

// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,3,3,3,0,0,
0,0,3,4,4,10,3,0,
0,3,4,10,10,3,3,3,
0,3,4,10,3,3,3,3,
0,3,4,10,3,3,3,3,
0,0,3,4,10,3,3,3,
0,0,0,3,4,10,3,3,

// Tile 01
0,0,0,0,0,0,0,0,
0,0,3,3,3,0,0,0,
0,3,4,4,10,3,0,0,
3,4,10,3,3,3,3,0,
3,10,10,3,3,3,3,0,
3,3,3,3,3,3,3,0,
3,3,3,3,3,3,0,0,
3,3,3,3,3,0,0,0,

// Tile 02
0,0,0,3,4,10,3,3,
0,0,0,0,3,4,3,3,
0,0,0,0,3,4,10,3,
0,0,0,0,0,3,10,3,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,0,

// Tile 03

3,3,3,3,3,0,0,0,
3,3,3,3,0,0,0,0,
3,3,3,0,0,0,0,0,
3,3,3,0,0,0,0,0,
3,3,0,0,0,0,0,0,
3,3,0,0,0,0,0,0,
3,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

#define LIFE_3 LIFE_2+1

// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,14,14,15,0,0,
0,0,14,15,15,17,15,0,
0,14,15,17,15,17,17,15,
0,14,15,15,17,17,17,17,
0,14,15,17,15,17,17,17,
0,14,15,17,17,17,17,17,
0,14,15,15,15,17,17,17,

// Tile 01
0,0,0,0,0,0,0,0,
0,0,16,16,16,0,0,0,
0,16,16,17,16,16,0,0,
15,16,17,16,17,16,16,0,
17,17,17,16,17,16,16,0,
17,17,17,17,16,17,16,0,
17,17,17,17,17,16,16,0,
17,17,17,17,16,17,16,0,

// Tile 02
0,0,14,15,17,15,17,17,
0,0,0,14,15,15,15,17,
0,0,0,0,14,15,17,15,
0,0,0,0,0,14,15,15,
0,0,0,0,0,0,14,15,
0,0,0,0,0,0,0,14,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 03
17,17,17,16,17,16,0,0,
17,17,16,17,16,0,0,0,
17,16,17,16,0,0,0,0,
16,17,16,0,0,0,0,0,
17,16,0,0,0,0,0,0,
16,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

#define ROCK_1 LIFE_3+1

// Tile 00
0,0,0,0,0,6,6,6,
0,0,0,0,0,6,6,6,
0,0,0,0,13,6,6,13,
0,0,0,13,13,13,6,13,
0,0,0,13,13,13,6,13,
0,0,13,13,13,13,6,13,
0,0,13,13,13,13,6,13,
0,6,13,13,13,0,0,13,

// Tile 01
6,6,6,0,0,0,0,0,
6,6,6,0,0,0,0,0,
13,6,6,13,0,0,0,0,
13,6,13,13,13,0,0,0,
13,6,13,13,13,0,0,0,
13,6,13,13,13,13,0,0,
13,6,13,13,13,13,0,0,
13,0,0,13,13,13,6,0,

// Tile 02
0,6,13,13,0,0,0,13,
0,6,6,13,0,0,0,13,
0,6,6,13,0,0,0,6,
0,6,6,13,0,0,0,6,
6,6,6,6,0,0,6,6,
6,6,6,6,0,0,6,6,
6,6,6,6,0,0,6,6,
0,6,6,0,0,0,0,6,

// Tile 03
13,0,0,13,13,13,6,0,
6,0,0,0,13,6,6,0,
6,0,0,0,13,6,6,0,
6,0,0,0,13,6,6,0,
6,6,0,0,6,6,6,6,
6,6,0,0,6,6,6,6,
6,6,0,0,6,6,6,6,
6,0,0,0,0,6,6,0,

#define ROCK_2 ROCK_1+1

// Tile 00
0,0,0,1,1,1,6,6,
0,0,0,1,1,1,6,6,
0,0,0,1,1,1,6,6,
0,0,0,1,1,1,6,6,
0,0,0,1,1,1,6,6,
0,0,0,6,6,6,1,1,
0,0,0,6,6,6,1,1,
0,0,0,0,6,6,1,1,

// Tile 01
6,1,1,1,6,0,0,0,
6,1,1,1,6,0,0,0,
6,1,1,1,6,0,0,0,
6,1,1,1,6,0,0,0,
6,1,1,1,6,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,0,0,0,0,

// Tile 02
0,0,0,0,6,6,1,1,
0,0,0,0,6,6,1,1,
0,0,0,0,1,1,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,0,6,6,6,

// Tile 03
1,6,6,6,0,0,0,0,
1,6,6,6,0,0,0,0,
6,1,1,1,0,0,0,0,
6,1,1,0,0,0,0,0,
6,1,1,0,0,0,0,0,
6,1,1,0,0,0,0,0,
6,1,1,0,0,0,0,0,
6,6,6,0,0,0,0,0,

#define ROCK_3 ROCK_2+1

// Tile 00
0,0,0,0,0,0,0,6,
0,0,0,0,0,0,6,6,
0,0,0,0,0,0,6,6,
0,0,0,0,0,6,6,6,
0,0,0,0,0,6,6,6,
0,0,0,0,0,6,6,6,
0,0,0,0,0,1,6,6,
0,0,0,0,1,1,6,6,

// Tile 01
6,0,0,0,0,0,0,0,
6,6,0,0,0,0,0,0,
6,6,0,0,0,0,0,0,
6,6,6,0,0,0,0,0,
6,6,6,0,0,0,0,0,
6,6,6,0,0,0,0,0,
6,1,1,0,0,0,0,0,
6,1,1,1,0,0,0,0,

// Tile 02
0,0,0,0,1,1,6,6,
0,0,0,0,1,1,6,6,
0,0,0,0,1,1,6,6,
0,0,0,0,6,6,1,1,
0,0,0,6,6,6,1,1,
0,0,0,6,6,6,1,1,
0,0,0,6,6,6,1,1,
0,0,0,6,6,6,1,1,

// Tile 03
6,1,1,1,0,0,0,0,
6,1,1,1,0,0,0,0,
6,1,1,1,0,0,0,0,
1,6,6,6,0,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,6,0,0,0,
1,6,6,6,6,0,0,0,

#define SATV_1 ROCK_3+1

// Tile 00
0,0,1,1,7,7,7,1,
0,0,1,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,1,1,7,7,7,1,
0,0,3,1,7,7,7,3,
0,4,1,3,7,7,7,3,
0,4,1,3,7,7,4,1,

// Tile 01
1,1,1,7,7,7,0,0,
6,1,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,1,1,7,7,7,0,0,
1,1,1,7,7,3,0,0,
3,1,1,7,4,1,3,0,
1,3,1,7,4,1,3,0,

// Tile 02
0,4,4,1,3,7,4,1,
1,1,4,1,3,7,4,1,
1,1,1,4,3,7,4,1,
0,4,4,4,0,0,4,4,
0,0,0,8,0,0,0,8,
0,0,8,8,0,0,0,8,
0,8,8,8,8,0,8,8,
0,8,8,8,8,0,8,8,

// Tile 03
1,3,1,4,1,4,3,0,
1,3,1,4,1,4,1,3,
1,3,1,4,4,1,1,3,
4,4,0,0,4,4,4,0,
8,0,0,0,8,0,0,0,
8,0,0,0,8,8,0,0,
8,8,0,8,8,8,8,0,
8,8,0,8,8,8,8,0,

#define SATV_2 SATV_1+1

// Tile 00
0,0,3,3,3,3,3,3,
0,0,1,1,3,1,1,1,
0,0,1,1,3,1,1,1,
0,0,3,3,3,3,3,3,
0,0,1,1,3,1,1,1,
0,0,7,7,7,7,7,7,
0,0,7,7,7,7,7,7,
0,0,1,1,7,7,7,1,

// Tile 01
3,3,3,3,3,3,0,0,
1,1,1,1,1,1,0,0,
1,1,1,1,1,1,0,0,
3,3,3,3,3,3,0,0,
1,1,1,1,1,1,0,0,
7,7,7,7,7,7,0,0,
7,7,7,7,7,7,0,0,
1,1,1,7,7,7,0,0,

// Tile 02
0,0,1,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,1,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,

// Tile 03
1,1,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,1,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,6,1,7,7,7,0,0,

#define SATV_3 SATV_2+1

// Tile 00
0,0,7,7,7,7,7,7,
0,0,7,7,7,7,7,7,
0,0,1,1,7,7,7,1,
0,0,1,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,1,1,7,7,7,1,

// Tile 01
7,7,7,7,7,7,0,0,
7,7,7,7,7,7,0,0,
1,1,1,7,7,7,0,0,
1,1,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,1,1,7,7,7,0,0,

// Tile 02
0,0,6,1,7,7,7,1,
0,0,6,1,7,7,7,1,
0,0,1,1,3,1,1,1,
0,0,1,1,3,1,1,1,
0,0,3,3,3,3,3,3,
0,0,6,1,3,1,1,7,
0,0,1,1,3,1,1,7,
0,0,6,1,3,1,1,6,

// Tile 03
6,6,1,7,7,7,0,0,
6,6,1,7,7,7,0,0,
1,1,1,1,1,1,0,0,
1,1,1,1,1,1,0,0,
3,3,3,3,3,3,0,0,
7,6,6,1,1,1,0,0,
7,1,1,1,1,1,0,0,
6,6,6,1,1,1,0,0,

#define SATV_4 SATV_3+1

// Tile 00
0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,
0,0,1,1,1,1,1,1,
0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,
0,0,3,3,3,6,3,3,
0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,

// Tile 01
1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,
1,1,1,1,1,1,0,0,
1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,
3,3,3,6,3,3,0,0,
1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,

// Tile 02
0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,
0,0,1,1,1,6,1,1,
0,0,1,1,1,1,1,1,
0,0,1,1,1,6,1,1,
0,0,3,3,3,3,3,3,
0,0,1,3,1,3,1,3,
0,0,1,3,1,3,1,3,

// Tile 03
1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,
1,1,1,6,1,1,0,0,
1,1,1,1,1,1,0,0,
1,1,1,6,1,1,0,0,
3,3,3,3,3,3,0,0,
1,3,1,3,1,3,0,0,
1,3,1,3,1,3,0,0,

#define SATV_5 SATV_4+1

// Tile 00
0,0,0,0,3,3,3,3,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,3,1,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,0,0,1,1,1,1,
0,0,0,0,3,1,3,1,

// Tile 01
3,3,3,3,0,0,0,0,
1,1,1,1,0,0,0,0,
1,1,3,1,0,0,0,0,
1,1,3,1,0,0,0,0,
1,1,3,1,0,0,0,0,
1,1,3,1,0,0,0,0,
1,1,1,1,0,0,0,0,
3,1,3,1,0,0,0,0,

// Tile 02
0,0,0,0,3,3,3,7,
0,0,0,0,1,3,1,7,
0,0,0,0,1,3,1,7,
0,0,0,1,3,1,7,7,
0,0,0,1,3,1,7,7,
0,0,1,3,1,7,7,7,
0,0,1,3,1,7,7,7,
0,0,3,3,3,7,7,7,

// Tile 03
7,7,7,7,0,0,0,0,
7,7,7,7,0,0,0,0,
7,7,7,7,0,0,0,0,
7,7,7,1,3,0,0,0,
7,7,7,1,3,0,0,0,
7,7,7,7,1,3,0,0,
7,7,0,7,1,3,0,0,
7,7,7,7,3,3,0,0,

#define SATV_6 SATV_5+1

// Tile 00
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,1,

// Tile 01
3,1,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,
1,3,1,0,0,0,0,0,
1,3,1,0,0,0,0,0,
1,3,1,0,0,0,0,0,

// Tile 02
0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,0,1,1,1,
0,0,0,0,3,3,3,3,
0,0,0,0,7,7,7,7,
0,0,0,0,7,7,7,7,
0,0,0,0,3,1,3,1,
0,0,0,0,3,1,3,1,

// Tile 03
1,3,1,0,0,0,0,0,
1,3,1,0,0,0,0,0,
1,3,1,0,0,0,0,0,
3,3,3,3,0,0,0,0,
7,7,7,7,0,0,0,0,
7,7,7,7,0,0,0,0,
3,1,3,1,0,0,0,0,
3,1,3,1,0,0,0,0,

#define SATV_7 SATV_6+1

// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,3,
0,0,0,0,0,0,0,1,

// Tile 01
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
3,0,0,0,0,0,0,0,
1,0,0,0,0,0,0,0,

// Tile 02
0,0,0,0,0,0,1,4,
0,0,0,0,0,0,1,1,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,3,4,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,3,3,
0,0,0,0,0,0,4,3,
0,0,0,0,0,0,1,1,

// Tile 03
1,1,0,0,0,0,0,0,
1,1,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
4,3,0,0,0,0,0,0,
3,1,0,0,0,0,0,0,

#define METEOR SATV_7+1

// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,3,3,9,9,3,
0,4,0,3,3,3,3,3,
4,4,4,3,3,3,3,3,
4,10,3,3,3,3,3,10,
4,4,10,10,3,3,10,10,
4,4,10,3,3,3,4,10,
4,4,10,3,3,3,4,10,

// Tile 01
9,9,9,0,0,0,0,0,
3,3,9,9,9,0,0,0,
9,3,3,9,9,9,0,0,
10,9,3,3,3,3,0,0,
10,10,9,3,3,9,0,0,
4,10,10,9,3,9,9,0,
3,4,10,9,9,3,9,0,
10,10,3,3,3,3,9,0,

// Tile 02
10,10,3,10,3,3,3,4,
4,10,3,10,3,3,3,3,
4,4,10,3,10,3,3,3,
0,4,10,10,3,3,10,3,
0,4,10,10,10,10,3,10,
0,0,4,4,4,10,10,3,
0,0,0,0,4,4,4,10,
0,0,0,0,0,0,4,4,

// Tile 03
10,10,3,3,3,3,9,9,
4,4,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,10,3,3,9,0,
3,3,10,3,3,9,3,0,
10,3,3,3,3,3,0,0,
3,4,3,3,3,0,0,0,
4,4,0,0,0,0,0,0,

#define MET_XPLODIN METEOR+1

// Tile 00
0,0,0,0,0,0,0,0,
0,14,14,0,0,0,0,14,
0,14,15,15,0,0,0,14,
0,0,0,16,16,0,0,0,
0,0,0,16,0,0,9,0,
0,0,0,0,0,10,3,9,
0,14,15,16,0,10,3,3,
0,14,15,16,16,1,1,1,

// Tile 01
14,14,0,0,0,0,0,0,
15,15,14,0,0,0,0,0,
17,17,14,0,0,0,0,0,
17,17,0,0,0,16,15,15,
1,0,0,17,16,16,15,14,
1,10,3,9,17,0,14,14,
1,10,3,3,0,0,0,0,
1,0,10,10,0,0,3,0,

// Tile 02
0,0,15,0,1,1,9,1,
0,0,17,17,17,10,1,1,
0,0,17,0,10,0,1,0,
0,17,17,0,17,0,1,3,
14,15,17,17,17,0,0,0,
15,15,16,0,0,0,0,3,
14,15,14,0,0,0,10,0,
0,14,0,0,0,0,0,0,

// Tile 03
1,1,1,0,0,10,10,0,
3,3,1,10,0,0,0,0,
3,0,1,1,0,0,0,0,
3,3,17,17,0,0,0,0,
0,17,0,17,17,0,0,0,
0,0,0,0,16,16,14,0,
0,0,0,0,16,15,14,0,
0,0,0,0,0,14,14,0,

#define LASER MET_XPLODIN+1

// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
6,6,6,6,6,6,6,6,

// Tile 01
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
6,6,6,6,6,6,6,6,

// Tile 02
6,6,6,6,6,6,6,6,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 03
6,6,6,6,6,6,6,6,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

#define S_T LASER+1 // Letters S and T

// Tile 00
0,0,1,1,1,1,0,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,0,0,0,
0,1,1,1,1,1,0,0,
0,0,1,1,1,1,1,0,
0,0,0,0,0,0,1,0,
0,1,1,1,1,1,1,0,
0,0,1,1,1,1,0,0,

// Tile 01
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,

// Tile 02
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 03
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

#define A_R S_T+1 // Letters A and R

// Tile 00
0,0,1,1,1,1,0,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,

// Tile 01
0,1,1,1,1,1,0,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,1,1,1,0,0,
0,1,1,1,1,0,0,0,
0,1,1,0,1,1,0,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,0,1,1,

// Tile 02
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 03
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

#define T A_R+1 // Letter T #27

// Tile 00
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,
0,0,0,1,1,0,0,0,

// Tile 01
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 02
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

// Tile 03
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
};