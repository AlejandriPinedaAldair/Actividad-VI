#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include "hardware/i2c.h"

typedef struct {
    i2c_inst_t *i2c_instance;
    uint8_t width;
    uint8_t height;
    uint8_t address;
    bool external_vcc;
} ssd1306_t;

void ssd1306_init(ssd1306_t *display, uint8_t width, uint8_t height, uint8_t address, i2c_inst_t *i2c_instance);
void ssd1306_clear(ssd1306_t *display);
void ssd1306_draw_string(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t scale, const char *str);
void ssd1306_show(ssd1306_t *display);

#endif
