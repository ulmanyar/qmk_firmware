#pragma once

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#define AURORA_WIDTH 32     // px
#define AURORA_HEIGHT 128   // px
#define AURORA_CANVAS_SIZE AURORA_WIDTH * AURORA_HEIGHT / 8 // bytes
#define AURORA_SKY_FRAME_DURATION 50
#define AURORA_PHASE_MODIFIER 300 / AURORA_SKY_FRAME_DURATION

// Tuning parameters for both aurora strains
// TODO: Add ifdef checks for other OLED sizes? NOTE: There is no canvas (yet)
// Upper
#define AURORA_UPPER_SLOPE          1
#define AURORA_UPPER_PERIOD         2
#define AURORA_UPPER_AMPLITUDE      7
#define AURORA_UPPER_AMPLITUDE_RATE 10
#define AURORA_UPPER_START_X        12
#define AURORA_UPPER_START_Y        90
// Lower
#define AURORA_LOWER_SLOPE          2
#define AURORA_LOWER_PERIOD         2
#define AURORA_LOWER_AMPLITUDE      7
#define AURORA_LOWER_AMPLITUDE_RATE 6
#define AURORA_LOWER_START_X        6
#define AURORA_LOWER_START_Y        75

typedef struct AuroraParams {
    uint8_t k;      // slope
    uint8_t A_r;    // Inverse amplitude rate (scaling: 4)
    uint8_t A;      // Amplitude
    uint8_t T;      // Period (scaling: 2*pi)
    uint8_t phi;    // Current phase offset
    uint8_t x0;     // Start x coordinate
    uint8_t y0;     // Start y coordinate
} aurora_params;

typedef struct AuroraSegment {
    uint8_t y_upper;    // Upper tail y coordinate
    uint8_t y_lower;    // Lower tail y coordinate
    uint8_t x;          // Current x coordinate
} aurora_segment;

void set_aurora_typing_state(bool);
bool get_aurora_typing_state(void);

void render_aurora_sky(void);

void generate_aurora(aurora_params *aurora, char canvas[]);

void draw_aurora_on_canvas(aurora_segment *segment, char canvas[]);