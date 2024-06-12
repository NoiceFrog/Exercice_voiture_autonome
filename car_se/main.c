#include <stdio.h>
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define FRAME_TIME 110000

typedef struct {
    int x;
    int y;
} vec2;

bool collide(vec2 a, vec2 b) {
    if (a.x == b.x && a.y == b.y) {
        return true;
    }  
    else return false;
};

void init();
void draw_car();
void process_movement();
void update();

WINDOW* win;

vec2 car = { 25, 20};
vec2 dir = { 0, 1};

int screen_width = 25;
int screen_height = 20;

int main() {
    init();
    while (true) {
        process_movement();
        draw_car();
        refresh();
    }
    return 0;
}

void init() {
  srand(time(NULL));
  win = initscr();
  keypad(win, true);
  noecho();
  nodelay(win, true);
  curs_set(0);

  if (has_colors() == FALSE) {
    endwin();
    fprintf(stderr, "Your terminal is shit get a new one u fucking nigger\n");
    exit(0);
  }
  start_color();
  use_default_colors();
  init_pair(1, COLOR_RED, -1);
  init_pair(2, COLOR_GREEN, -1);
  init_pair(3, COLOR_YELLOW, -1);
  init_pair(4, COLOR_BLUE, -1);
};

void process_movement() {
    car.x += dir.x;
    car.y += dir.y;

    if (car.y >= screen_height) {
        dir.y = -1;
    } else if (car.y <= 0) {
        dir.y = 1;
    }

    usleep(FRAME_TIME);
};

void draw_border(int y, int x, int width, int height) {
  //top row
  mvaddch(y, x, ACS_ULCORNER);
  mvaddch(y, x + width * 2 + 1, ACS_URCORNER);
  for (int i = 1; i < width * 2 + 1; i++) {
    mvaddch(y, x + i, ACS_HLINE);
  }
  // vertical lines
  for (int i = 1; i < height + 1; i++) {
    mvaddch(y + i, x, ACS_VLINE);
    mvaddch(y + i, x + width * 2 + 1, ACS_VLINE);
  }

  // bottom row
  mvaddch(y + height + 1, x, ACS_LLCORNER);
  mvaddch(y + height + 1, x + width * 2 + 1, ACS_LRCORNER);
  for (int i = 1; i < width * 2 + 1; i++) {
    mvaddch(y + height + 1, x + i, ACS_HLINE);
  }
};

void draw_car() {
    erase();
    attron(COLOR_PAIR(1));
    mvaddch(car.y, car.x, '@');
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
    draw_border(0, 0, screen_width, screen_height); // love iron maiden <3
    attroff(COLOR_PAIR(4));
}