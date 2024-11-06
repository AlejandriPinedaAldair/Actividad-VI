#include <stdio.h> // Librería para la entrada y salida estándar
#include "pico/stdlib.h" // Librería estándar para la Raspberry Pi Pico
#include "hardware/i2c.h" // Librería para manejar la comunicación I2C
#include "ssd1306.h" // Cabecera de la librería personalizada para el controlador SSD1306

#define SLEEPTIME 25 // Tiempo de espera en milisegundos

void arranque(void);
void impre(void);

int main() {
    stdio_init_all(); // Inicializa toda la entrada y salida estándar

    // Configuración de los pines I2C y arranque del sistema
    arranque();

    // Impresión en pantalla OLED
    impre();

    return 0;
}

// Configura los pines para la comunicación I2C
void arranque(void) {
    i2c_init(i2c1, 400000); // Inicializa I2C en el puerto 1 a 400 kHz
    gpio_set_function(2, GPIO_FUNC_I2C); // Configura GPIO2 para la función I2C
    gpio_set_function(3, GPIO_FUNC_I2C); // Configura GPIO3 para la función I2C
    gpio_pull_up(2); // Activa la resistencia pull-up en GPIO2
    gpio_pull_up(3); // Activa la resistencia pull-up en GPIO3
}

// Imprime el nombre y apellidos en la pantalla OLED
void impre(void) {
    const char *words[] = {"Alejandri", "Pineda", "Aldair"}; // Array de cadenas con el nombre y apellidos

    ssd1306_t disp; // Estructura para el manejo de la pantalla OLED
    disp.external_vcc = false; // Configura el uso de la alimentación interna
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1); // Inicializa la pantalla OLED con tamaño 128x64, dirección I2C 0x3C, y puerto I2C1
    ssd1306_clear(&disp); // Limpia la pantalla OLED

    for (;;) { // Bucle infinito
        // Recorre cada palabra en el array
        for (int i = 0; i < sizeof(words) / sizeof(char *); ++i) {
            ssd1306_draw_string(&disp, 8, 24, 2, words[i]); // Dibuja la cadena en la pantalla OLED
            ssd1306_show(&disp); // Muestra los datos en la pantalla OLED
            sleep_ms(500); // Espera 500 milisegundos
            ssd1306_clear(&disp); // Limpia la pantalla OLED
        }
    }
}
