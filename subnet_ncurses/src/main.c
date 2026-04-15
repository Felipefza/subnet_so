#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>

int main(void) {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(1);

  /* smaller so it works on small terminals */
  WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);

  int inptWidth, inptHeight, inputX, inputY;

  inptHeight = 3;
  inptWidth = COLS * 0.8;
  inputY = LINES / 2;
  inputX = COLS * 0.2 / 2;

  WINDOW* inputIPuser = newwin(inptHeight, inptWidth, inputY, inputX);
  delwin(mainWindow);

  box(mainWindow, 0, 0);
  box(inputIPuser, 0, 0);

  wrefresh(mainWindow);
  wrefresh(inputIPuser);

  char* ipUser = calloc(20, sizeof(char));
  mvwgetstr(inputIPuser, 1, 1, ipUser);

  WINDOW* inputIPuser = newwin(inptHeight, inptWidth, inputY, inputX);
  wrefresh(inputIPuser);

  char* numberHosts = calloc(20, sizeof(char));
  mvwgetstr(inputIPuser, 1, 1, numberHosts);


  delwin(mainWindow);
  endwin();
  return EXIT_SUCCESS;
}
