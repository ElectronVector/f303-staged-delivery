#include <cstdint>

// Define GPIOE registers.
static volatile unsigned &RCC_AHB1 = *reinterpret_cast<unsigned *>(0x40021014);
static volatile unsigned &GPIOE_MODER = *reinterpret_cast<unsigned *>(0x48001000);
static volatile unsigned &GPIOE_BSRR = *reinterpret_cast<unsigned *>(0x48001018);

#define bit(x) (1 << x)

void delay (int delay_count) {
    for (volatile int i = 0; i < delay_count; i++);
}

void init_gpio_output(int selected_bit) {
    RCC_AHB1 |= bit(21);  // enable clock for GPIOE
    GPIOE_MODER |= 1 << (2 * selected_bit);  // set output
}

void set_gpio_output(int selected_bit) {
    GPIOE_BSRR = bit(selected_bit); // set output
}

void clear_gpio_output(int selected_bit) {
    GPIOE_BSRR = static_cast<unsigned int>(bit(selected_bit) << 16);  // clear output
}


// Select the GPIOE pin used by the LED and the flash rate.
#define LED 15
#define LED_DELAY 400000

// Initialize and flash the LED.
void main_app() {

    init_gpio_output(LED);

    while (true) {
        //delay(LED_DELAY);
        //set_gpio_output(LED);
        delay(LED_DELAY);
        clear_gpio_output(LED);
    }
}
