#include "ssd1306.h"

static void ssd1306_send_command(ssd1306_t *display, uint8_t command) {
    uint8_t buf[2] = {0x00, command};
    i2c_write_blocking(display->i2c_instance, display->address, buf, 2, false);
}

void ssd1306_init(ssd1306_t *display, uint8_t width, uint8_t height, uint8_t address, i2c_inst_t *i2c_instance) {
    display->i2c_instance = i2c_instance;
    display->width = width;
    display->height = height;
    display->address = address;

    const uint8_t init_cmds[] = {
        0xAE, 0xD5, 0x80, 0xA8, 0x3F, 0xD3, 0x00, 0x40,
        0x8D, 0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA, 0x12,
        0x81, 0xCF, 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6,
        0x2E, 0xAF
    };

    for (uint8_t i = 0; i < sizeof(init_cmds); i++) {
        ssd1306_send_command(display, init_cmds[i]);
    }
}

void ssd1306_clear(ssd1306_t *display) {
    uint8_t buf[display->width];
    memset(buf, 0x00, display->width);

    for (uint8_t i = 0; i < display->height / 8; i++) {
        ssd1306_send_command(display, 0xB0 + i);
        ssd1306_send_command(display, 0x00);
        ssd1306_send_command(display, 0x10);
        i2c_write_blocking(display->i2c_instance, display->address, buf, display->width, false);
    }
}

void ssd1306_draw_string(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t scale, const char *str) {
    // Aquí deberías implementar el código para dibujar el texto en la pantalla.
    // Por simplicidad, esta función no está completamente implementada.
}

void ssd1306_show(ssd1306_t *display) {
    // Esta función se usaría para actualizar la pantalla, si fuera necesario.
}
