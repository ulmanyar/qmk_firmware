#include "oled_driver.h"
#include "oled_writer.h"

void oled_write_sparse_map(uint8_t origin_x, uint8_t origin_y, uint8_t offsets[][2], uint8_t size, bool on) {
    uint8_t x;
    uint8_t y;

    for (int i = 0; i < size; i++) {
        x = origin_x + offsets[i][1];
        y = origin_y + offsets[i][2];
        // Concept:
        // For each X:
        //   Build char of Y-values in [0,7] using c |= 1 << offset, or similar
        //     TODO: Figure out how to handle Y >= 8
        //   Calculate index as write_pixel
        //   Write char to oled_buffer[index]

        if (x >= oled_rotation_width || y >= OLED_DISPLAY_HEIGHT) {
            return;
        }
        uint16_t index = x + (y / 8) * oled_rotation_width;
        if (index >= OLED_MATRIX_SIZE) {
            return;
        }
        uint8_t data = oled_buffer[index];
        if (on) {
            data |= (1 << (y % 8));
        } else {
            data &= ~(1 << (y % 8));
        }
        if (oled_buffer[index] != data) {
            oled_buffer[index] = data;
            oled_dirty |= ((OLED_BLOCK_TYPE)1 << (index / OLED_BLOCK_SIZE));
        }
    }
}
