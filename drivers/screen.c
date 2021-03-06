/*
  Uzhix Project

  (c) 2018 MrOnlineCoder (Nikita Kogut)
  github.com/MrOnlineCoder

  See license in LICENSE file
*/

#include <uzhix/drivers/screen.h>

char* video_mem = (char*) 0xB8000;

unsigned char cursor_x;
unsigned char cursor_y;
unsigned char screen_color;

int rowSize = SCREEN_WIDTH*2; //how much memory 1 row takes

static unsigned int get_memory_pos() {
  return (cursor_x + cursor_y * SCREEN_WIDTH) * 2;
}

static void advance_cursor() {
  cursor_x++;

  if (cursor_x > SCREEN_WIDTH) {
    cursor_x = 0;
    cursor_y++;
  }
}

void screen_init() {
  cursor_x = 0;
  cursor_y = 0;

  screen_set_color(SCREEN_COLOR_WHITE, SCREEN_COLOR_BLACK);
  screen_clear();
}

void screen_clear() {
  for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT*2; i++) {
    video_mem[i] = ' ';
    i++;
    video_mem[i] = screen_color;
  }
}

void screen_set_color(unsigned char bg, unsigned char fg) {
  screen_color = (fg << 4) | (bg & 0x0F);
}

void screen_putchar(char c) {
  if (c == '\n') {
    cursor_x = 0;
    cursor_y++;
  } else {
    unsigned int pos = get_memory_pos();

    video_mem[pos] = c;
    video_mem[pos+1] = screen_color;

    advance_cursor();
    screen_scroll();
  }
}

void screen_scroll() {
	if (cursor_y >= SCREEN_HEIGHT) {
		int i = rowSize; /* Starting position */

		/*Move every char a row up*/
		while (i < SCREEN_WIDTH*(SCREEN_HEIGHT-1)*2) {
			video_mem[i-rowSize] = video_mem[i];
			i++;
		}


		/*Clear the last row*/
		for (i = SCREEN_WIDTH * (SCREEN_HEIGHT-1) * 2;i<SCREEN_WIDTH*SCREEN_HEIGHT*2;i+=2) {
			video_mem[i] = ' ';
			video_mem[i+1] = screen_color;
		}

		/*Set cursor_y back*/
		cursor_y--;
	}
}
