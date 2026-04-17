#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// LOCAL FILES
#include "../include/windowsNcurses.h"

int main(void) {
  initNcurses();

  WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
  box(mainWindow, 0, 0);


  windowInput(mainWindow);

  werase(mainWindow);
  wrefresh(mainWindow);
  delwin(mainWindow);
  endwin();
  return EXIT_SUCCESS;
}
