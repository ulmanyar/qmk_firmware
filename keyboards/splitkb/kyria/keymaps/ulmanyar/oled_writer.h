
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "oled_driver.h"

void oled_write_sparse_map(uint8_t origin_x, uint8_t origin_y, uint8_t offsets[][2], uint8_t size, bool on);

extern uint8_t         oled_rotation_width;
extern uint8_t         oled_buffer[OLED_MATRIX_SIZE];
extern OLED_BLOCK_TYPE oled_dirty;
