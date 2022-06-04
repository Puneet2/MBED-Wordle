#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "globals.h"
 

// The bottom of the screen => y=127
// A macro to reverse the coordinate for convenience (optional).
#define REVERSE_Y(x) (SIZE_Y-(x))

/**
 * Draws a sprite
 */
void draw_w();
void draw_o();
void draw_r();
void draw_d();
void draw_l();
void draw_e();
void draw_y();
void draw_o2();
void draw_u();
void draw_w2();
void draw_o3();
void draw_n();
void draw_lower_status();

 
#endif // GRAPHICS_H
