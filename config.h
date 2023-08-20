#ifndef _CONFIG_LEDSCROLL_
#define _CONFIG_LEDSCROLL_

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))

// SET number of LED matrix displays in use. Wokwi simulation uses 2.
// This is used in max72xx.h
#define NUMBER_OF_SEGMENTS 4

// SET MAX_COLUMNS to number of segments times 8.
// 1 segment -> 8, 2 segments -> 16, 3 segments -> 24, 4 segments -> 32, 5 segments -> no, 6 segments -> stop, 7 segments -> what are you doing
#define MAX_COLUMNS 32
#define MAX_ROWS 8

#define TIME_BETWEEN_MOVES 40

#endif