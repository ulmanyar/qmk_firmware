#include "sisyphos.h"
#include "quantum.h"

static const int ground_dither = 0b1110110010001;
static const int ground_width = 13;

// Sisyphos must walk on ground, so let's make some
bool ground_setup = false;
static void setup_ground(void) {
    for (size_t y = 0; y < HEIGHT; y++) {
        int x_max = 2*y + ground_width;
        x_max = x_max > WIDTH ? WIDTH : x_max;
        for (size_t x = 0; x < x_max; x++) {
            if (ground_dither & (1 << x)) {
                oled_write_pixel(x + 2*y, y, true);
            } else {
                continue;
            }
        }
    }
}

// Sisyphos must push a boulder, so let's make one
bool boulder_setup = false;
struct Boulder {
    int x;
    int y;
    const unsigned int width = 13;
    const unsigned int size = width * width;
    const unsigned int bitmap[] = {
        0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 
        0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
        0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
        0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
        1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
        1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 
        0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 
        0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 
        0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 
        0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 
        0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 
    };
} boulder;

static void draw_boulder(void) {
    for (size_t i; i < boulder.size; i++) {
        if (boulder.bitmap[i]) {
            oled_write_pixel(
                boulder.x + i % boulder.width,
                boulder.y + i / boulder.width,
                !reset);
        }
    }
}

static void setup_boulder(void) {
    boulder.x = 10; // TODO: Define properly
    boulder.y = HEIGHT - 20; // TODO: Define properly
    draw_boulder(&boulder);
}

static void animate_boulder(void) {
    // boulder.x += 1;
    // boulder.y += 1;
    // boulder.is_updated = true;
}

// Main rendering function
void render_sisyphos(void) {
    if (!ground_setup) {
        setup_ground();
    }
    if (!boulder_setup) {
        setup_boulder(&boulder);
        boulder_setup = true;
    }
}