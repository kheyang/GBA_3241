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

#define R_GL 2 // Rocket Going LEFT
// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
13,13,11,11,11,11,11,11,
13,11,11,11,11,11,11,11,
13,13,11,11,11,11,11,11,
// Tile 01
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
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

#define R_GR 3 // Rocket Going RIGHT 
// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
// Tile 01
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
2,2,2,2,2,2,7,7,
2,2,2,2,2,2,2,7,
2,2,2,2,2,2,7,7,
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

#define HEALTH_USER 4 // Health bar for the user
// Tile 00
4,4,4,4,4,4,4,4,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,

// Tile 01
4,4,4,4,4,4,4,4,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,

// Tile 02
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
4,4,4,4,4,4,4,4,

// Tile 03
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,
4,4,4,4,4,4,4,4,

#define HEALTH_ENEMY 5 // Health bar for the enemy

// Tile 00
4,4,4,4,4,4,4,4,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,

// Tile 01
4,4,4,4,4,4,4,4,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,

// Tile 02
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
4,4,4,4,4,4,4,4,

// Tile 03
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
11,11,11,11,11,11,11,11,
4,4,4,4,4,4,4,4,

#define HEALTH_SEPARATOR 6 // Centre portion splitting the health bars

// Tile 00
4,4,4,4,4,4,4,4,
2,4,4,4,3,3,3,3,
2,4,4,4,4,3,3,3,
2,2,4,4,4,3,3,3,
2,2,4,4,4,3,3,3,
2,2,2,4,4,4,3,3,
2,2,2,4,4,4,3,3,
2,2,2,2,4,4,3,3,

// Tile 01
4,4,4,4,4,4,4,4,
3,3,3,3,4,4,4,11,
3,3,3,4,4,4,4,11,
3,3,3,4,4,4,11,11,
3,3,3,4,4,4,11,11,
3,3,4,4,4,11,11,11,
3,3,4,4,4,11,11,11,
3,3,4,4,11,11,11,11,

// Tile 02
2,2,2,2,4,4,3,3,
2,2,2,2,2,4,4,3,
2,2,2,2,2,4,4,3,
2,2,2,2,2,2,4,3,
2,2,2,2,2,2,4,4,
2,2,2,2,2,2,4,4,
2,2,2,2,2,2,2,4,
4,4,4,4,4,4,4,4,

// Tile 03
3,3,4,4,11,11,11,11,
3,4,4,11,11,11,11,11,
3,4,4,11,11,11,11,11,
3,4,11,11,11,11,11,11,
4,4,11,11,11,11,11,11,
4,4,11,11,11,11,11,11,
4,11,11,11,11,11,11,11,
4,4,4,4,4,4,4,4,

#define HEALTH_EMPTY 7 //depleted health bar
// Tile 00
4,4,4,4,4,4,4,4,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,

// Tile 01
4,4,4,4,4,4,4,4,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,

// Tile 02
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,

// Tile 03
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
3,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,

#define S_LR_WS 8 // Shooter Looking Right With Shield
// Tile 00
0,0,0,0,5,5,1,1,
0,0,0,0,5,1,1,2,
0,0,0,5,5,1,2,2,
0,0,0,5,1,1,1,1,
0,0,0,5,1,1,1,1,
0,0,4,4,5,1,4,4,
0,0,4,4,5,1,5,5,
0,0,4,4,5,1,1,2,
// Tile 01
1,5,0,0,0,0,0,0,
2,5,0,0,0,0,0,0,
2,5,0,0,0,0,0,0,
1,5,5,0,0,0,0,0,
1,1,5,0,0,0,0,0,
4,4,4,4,4,4,0,0,
4,5,5,5,4,4,0,0,
4,5,2,5,4,4,0,0,
// Tile 02
0,0,0,5,1,1,1,1,
0,0,0,5,1,1,1,1,
0,0,0,5,1,1,1,1,
0,0,0,5,5,2,2,2,
0,0,0,0,5,2,2,2,
0,0,0,0,5,2,2,2,
0,0,0,0,5,2,2,2,
0,0,0,0,5,3,1,1,
// Tile 03
1,1,5,0,0,0,0,0,
1,1,5,0,0,0,0,0,
1,1,5,0,0,0,0,0,
5,0,0,0,0,0,0,0,
5,0,0,0,0,0,0,0,
5,0,0,0,0,0,0,0,
5,5,0,0,0,0,0,0,
1,1,5,0,0,0,0,0,

#define MID_DIVIDER 9 // divide the middle for user to see easier

// Tile 00
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,

// Tile 01
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,

// Tile 02
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,
0,0,0,0,0,0,0,4,

// Tile 03
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,
4,0,0,0,0,0,0,0,

#define HEALTH_SEPARATOR_LOSE 10 // divider when user loses

// Tile 00
4,4,4,4,4,4,4,4,
3,4,4,4,3,3,3,3,
3,4,4,4,4,3,3,3,
3,3,4,4,4,3,3,3,
3,3,4,4,4,3,3,3,
3,3,3,4,4,4,3,3,
3,3,3,4,4,4,3,3,
3,3,3,3,4,4,3,3,

// Tile 01
4,4,4,4,4,4,4,4,
3,3,3,3,4,4,4,11,
3,3,3,4,4,4,4,11,
3,3,3,4,4,4,11,11,
3,3,3,4,4,4,11,11,
3,3,4,4,4,11,11,11,
3,3,4,4,4,11,11,11,
3,3,4,4,11,11,11,11,

// Tile 02
3,3,3,3,4,4,3,3,
3,3,3,3,3,4,4,3,
3,3,3,3,3,4,4,3,
3,3,3,3,3,3,4,3,
3,3,3,3,3,3,4,4,
3,3,3,3,3,3,4,4,
3,3,3,3,3,3,3,4,
4,4,4,4,4,4,4,4,

// Tile 03
3,3,4,4,11,11,11,11,
3,4,4,11,11,11,11,11,
3,4,4,11,11,11,11,11,
3,4,11,11,11,11,11,11,
4,4,11,11,11,11,11,11,
4,4,11,11,11,11,11,11,
4,11,11,11,11,11,11,11,
4,4,4,4,4,4,4,4,

#define HEALTH_SEPARATOR_WIN 11 // divider when player wins

// Tile 00
4,4,4,4,4,4,4,4,
2,4,4,4,3,3,3,3,
2,4,4,4,4,3,3,3,
2,2,4,4,4,3,3,3,
2,2,4,4,4,3,3,3,
2,2,2,4,4,4,3,3,
2,2,2,4,4,4,3,3,
2,2,2,2,4,4,3,3,

// Tile 01
4,4,4,4,4,4,4,4,
3,3,3,3,4,4,4,3,
3,3,3,4,4,4,4,3,
3,3,3,4,4,4,3,3,
3,3,3,4,4,4,3,3,
3,3,4,4,4,3,3,3,
3,3,4,4,4,3,3,3,
3,3,4,4,3,3,3,3,

// Tile 02
2,2,2,2,4,4,3,3,
2,2,2,2,2,4,4,3,
2,2,2,2,2,4,4,3,
2,2,2,2,2,2,4,3,
2,2,2,2,2,2,4,4,
2,2,2,2,2,2,4,4,
2,2,2,2,2,2,2,4,
4,4,4,4,4,4,4,4,

// Tile 03
3,3,4,4,3,3,3,3,
3,4,4,3,3,3,3,3,
3,4,4,3,3,3,3,3,
3,4,3,3,3,3,3,3,
4,4,3,3,3,3,3,3,
4,4,3,3,3,3,3,3,
4,3,3,3,3,3,3,3,
4,4,4,4,4,4,4,4,

#define MAGICIAN_LL 12 //level 2 Magician Looking Left

// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,8,8,
0,0,0,0,0,8,8,8,
0,0,8,8,0,0,11,11,
0,0,8,8,0,0,9,1,
0,0,0,8,0,0,9,1,
0,0,0,8,0,0,13,9,
0,0,0,8,0,13,13,9,
// Tile 01
8,8,8,8,0,0,0,0,
8,8,0,0,8,0,0,0,
8,8,8,0,0,8,0,0,
11,11,9,8,0,0,0,0,
1,1,1,9,0,0,0,0,
3,3,9,13,0,0,0,0,
1,9,13,13,13,0,0,0,
9,13,13,13,13,0,0,0,
// Tile 02
0,0,0,11,13,13,13,13,
0,0,0,8,0,13,13,13,
0,0,0,8,0,0,13,13,
0,0,0,8,0,0,13,13,
0,0,0,8,0,0,13,13,
0,0,0,8,0,0,13,13,
0,0,0,8,0,0,13,13,
0,0,0,8,0,13,13,13,
// Tile 03
13,13,13,13,13,0,0,0,
13,13,13,13,13,0,0,0,
13,13,13,13,13,0,0,0,
13,13,13,13,11,0,0,0,
13,13,13,13,13,0,0,0,
13,13,13,13,13,0,0,0,
13,13,13,13,13,0,0,0,
13,13,13,13,13,13,0,0,

#define FIREBALL_GL 13 //Fireball going left

// Tile 00
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,6,6,6,11,11,11,12,
6,6,11,11,11,12,12,12,
6,11,11,12,12,12,5,5,
6,6,11,11,11,12,12,12,
// Tile 01
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
12,12,12,11,6,6,6,6,
5,5,5,12,12,11,6,0,
5,5,12,12,11,11,11,6,
5,5,5,12,12,11,6,0,
// Tile 02
0,6,6,6,11,11,11,12,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
// Tile 03
12,12,12,11,6,6,6,6,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,

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

#define G_A T+1 // Letter T #28

// Tile 00
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,0,0,0,
0,1,1,0,1,1,1,0,
0,1,1,0,1,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,

// Tile 01
0,0,1,1,1,1,0,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,

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

#define M_E G_A+1 // Letter T #29

// Tile 00
0,1,0,0,0,0,1,0,
0,1,1,0,0,1,1,0,
0,1,1,1,1,1,1,0,
0,1,0,1,1,0,1,0,
0,1,0,1,1,0,1,0,
0,1,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,

// Tile 01
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,0,0,0,
0,1,1,1,1,1,0,0,
0,1,1,1,1,1,0,0,
0,1,1,0,0,0,0,0,
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,

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

#define O_V M_E+1 // Letter T #30

// Tile 00
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,

// Tile 01
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,
0,1,1,0,0,1,1,0,
0,0,1,0,0,1,0,0,
0,0,1,0,0,1,0,0,
0,0,1,0,0,1,0,0,
0,0,1,1,1,1,0,0,
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

#define E_R O_V+1 // Letter T #31

// Tile 00
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,
0,1,1,0,0,0,0,0,
0,1,1,1,1,1,0,0,
0,1,1,1,1,1,0,0,
0,1,1,0,0,0,0,0,
0,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,0,

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
0,0,0,0,0,0,0,0
};