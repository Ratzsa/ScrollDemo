#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "max72xx.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>
#include "millis.h"
#include "config.h"

uint8_t ALL[] = {0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111};
uint8_t EX[] = {0B00000000,0B00010000,0B00010000,0B00010000,0B00010000,0B00000000,0B00010000,0B00000000};
uint8_t A[] = {0B00000000,0B00111100,0B01100110,0B01100110,0B01111110,0B01100110,0B01100110,0B01100110};
uint8_t B[] = {0B01111000,0B01001000,0B01001000,0B01110000,0B01001000,0B01000100,0B01000100,0B01111100};
uint8_t C[] = {0B00000000,0B00011110,0B00100000,0B01000000,0B01000000,0B01000000,0B00100000,0B00011110};
uint8_t D[] = {0B00000000,0B00111000,0B00100100,0B00100010,0B00100010,0B00100100,0B00111000,0B00000000};
uint8_t E[] = {0B00000000,0B00111100,0B00100000,0B00111000,0B00100000,0B00100000,0B00111100,0B00000000};
uint8_t F[] = {0B00000000,0B00111100,0B00100000,0B00111000,0B00100000,0B00100000,0B00100000,0B00000000};
uint8_t G[] = {0B00000000,0B00111110,0B00100000,0B00100000,0B00101110,0B00100010,0B00111110,0B00000000};
uint8_t H[] = {0B00000000,0B00100100,0B00100100,0B00111100,0B00100100,0B00100100,0B00100100,0B00000000};
uint8_t I[] = {0B00000000,0B00111000,0B00010000,0B00010000,0B00010000,0B00010000,0B00111000,0B00000000};
uint8_t J[] = {0B00000000,0B00011100,0B00001000,0B00001000,0B00001000,0B00101000,0B00111000,0B00000000};
uint8_t K[] = {0B00000000,0B00100100,0B00101000,0B00110000,0B00101000,0B00100100,0B00100100,0B00000000};
uint8_t L[] = {0B00000000,0B00100000,0B00100000,0B00100000,0B00100000,0B00100000,0B00111100,0B00000000};
uint8_t M[] = {0B00000000,0B00000000,0B01000100,0B10101010,0B10010010,0B10000010,0B10000010,0B00000000};
uint8_t N[] = {0B00000000,0B00100010,0B00110010,0B00101010,0B00100110,0B00100010,0B00000000,0B00000000};
uint8_t O[] = {0B00000000,0B00111100,0B01000010,0B01000010,0B01000010,0B01000010,0B00111100,0B00000000};
uint8_t P[] = {0B00000000,0B00111000,0B00100100,0B00100100,0B00111000,0B00100000,0B00100000,0B00000000};
uint8_t Q[] = {0B00000000,0B00111100,0B01000010,0B01000010,0B01000010,0B01000110,0B00111110,0B00000001};
uint8_t R[] = {0B00000000,0B00111000,0B00100100,0B00100100,0B00111000,0B00100100,0B00100100,0B00000000};
uint8_t S[] = {0B00000000,0B00111100,0B00100000,0B00111100,0B00000100,0B00000100,0B00111100,0B00000000};
uint8_t T[] = {0B00000000,0B01111100,0B00010000,0B00010000,0B00010000,0B00010000,0B00010000,0B00000000};
uint8_t U[] = {0B00000000,0B01000010,0B01000010,0B01000010,0B01000010,0B00100100,0B00011000,0B00000000};
uint8_t V[] = {0B00000000,0B00100010,0B00100010,0B00100010,0B00010100,0B00010100,0B00001000,0B00000000};
uint8_t W[] = {0B00000000,0B10000010,0B10010010,0B01010100,0B01010100,0B00101000,0B00000000,0B00000000};
uint8_t X[] = {0B00000000,0B01000010,0B00100100,0B00011000,0B00011000,0B00100100,0B01000010,0B00000000};
uint8_t Y[] = {0B00000000,0B01000100,0B00101000,0B00010000,0B00010000,0B00010000,0B00010000,0B00000000};
uint8_t Z[] = {0B00000000,0B00111100,0B00000100,0B00001000,0B00010000,0B00100000,0B00111100,0B00000000};

void undoLED(uint8_t *letter, uint8_t startX, uint8_t offset);
void scrollLED(uint8_t *letter, uint8_t startX, uint8_t offset);
void clearScreen();

int main()
{
    // Set up serial, display and millis
    init_serial();
	max7219_init();
    millis_init();
    sei();

    // Clear screen in preparation for scroll
    clearScreen();
    _delay_ms(75);

    uint8_t startPos = 0;
    volatile millis_t startTime = millis_get();
    uint8_t letterWidth = 6;

    while(1)
    {
        if(millis_get() - startTime > TIME_BETWEEN_MOVES)
        {
            undoLED(F, startPos, 0);
            undoLED(R, startPos, letterWidth);
            undoLED(O, startPos, (letterWidth * 2));
            undoLED(G, startPos, (letterWidth * 3));
            startPos++;
            if(startPos > MAX_COLUMNS - 1)
            {
                startPos = 0;
            }
            scrollLED(F, startPos, 0);
            scrollLED(R, startPos, letterWidth);
            scrollLED(O, startPos, (letterWidth * 2));
            scrollLED(G, startPos, (letterWidth * 3));

            startTime = millis_get();
        }
    }

    return 0;
}

void clearScreen()
{
    for(int x = 0; x < MAX_COLUMNS; x++)
    {
        for(int y = 0; y < MAX_ROWS; y++)
        {
            max7219b_clr(x, y);
            max7219b_out();
        }
    }
}

void undoLED(uint8_t *letter, uint8_t startX, uint8_t offset)
{
    for(uint8_t row = 0; row < 8; row++)
    {
        uint8_t todo = letter[row];
        for(uint8_t col = 0; col < 8; col++)
        {
            if(BIT_CHECK(todo, col))
            {
                int8_t column = (8 - col) - startX;
                if((column + offset) < 0)
                {
                    column = MAX_COLUMNS + column;
                }
                max7219b_clr((column + offset), row);
            }
        }
    }
}

void scrollLED(uint8_t *letter, uint8_t startX, uint8_t offset)
{
    for(uint8_t row = 0; row < 8; row++)
    {
        uint8_t todo = letter[row];
        for(uint8_t col = 0; col < 8; col++)
        {
            if(BIT_CHECK(todo, col))
            {
                int8_t column = (8 - col) - startX;
                if((column + offset) < 0)
                {
                    column = MAX_COLUMNS + column;
                }
                max7219b_set((column + offset), row);
            }
        }
    }
    max7219b_out();
}