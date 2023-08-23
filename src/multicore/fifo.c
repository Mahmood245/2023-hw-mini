/* https://www.raspberrypi.com/documentation/pico-sdk/high_level.html#pico_multicore */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#define FLAG_VALUE 123


void core1_entry() {

    multicore_fifo_push_blocking(FLAG_VALUE);

    uint32_t g = multicore_fifo_pop_blocking();

    if (g != FLAG_VALUE)
        printf("Hmm, that's not right on core 1!\n");
    else

        printf("Its all gone well on core 1!");

    while (1)
        tight_loop_contents();
}


int main() {
    stdio_init_all();
    printf("Hello, multicore!\n");


    multicore_launch_core1(core1_entry);

    // Wait for it to start up


    uint32_t g = multicore_fifo_pop_blocking();

    if (g != FLAG_VALUE)
        printf("Hmm, that's not right on core 0!\n");
    else {
        multicore_fifo_push_blocking(FLAG_VALUE);
        printf("It's all gone well on core 0!");
    }

}
