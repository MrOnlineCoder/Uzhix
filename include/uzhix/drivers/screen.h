/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#ifndef _SCREEN_H
#define _SCREEN_H

#define SCREEN_COLOR_BLACK 0
#define SCREEN_COLOR_BLUE 1
#define SCREEN_COLOR_GREEN 2
#define SCREEN_COLOR_CYAN 3
#define SCREEN_COLOR_RED 4
#define SCREEN_COLOR_MAGENTA 5
#define SCREEN_COLOR_BROWN 6
#define SCREEN_COLOR_LIGHT_GREY 7
#define SCREEN_COLOR_DARK_GREY 8
#define SCREEN_COLOR_LIGHT_BLUE 9
#define SCREEN_COLOR_LIGHT_GREEN 10
#define SCREEN_COLOR_LIGHT_CYAN 11
#define SCREEN_COLOR_LIGHT_RED 12
#define SCREEN_COLOR_LIGHT_MAGENTA 13
#define SCREEN_COLOR_LIGHT_BROWN 14
#define SCREEN_COLOR_WHITE 15

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCREEN_ROW_SIZE SCREEN_WIDTH*2

void screen_init();

void screen_clear();

void screen_putchar(char c);

void screen_set_color(unsigned char bg, unsigned char fg);

#endif
