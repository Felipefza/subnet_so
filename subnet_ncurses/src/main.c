#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  char* net;
  int masc;
  char* mascPunteada;
  char* broadcast;
  char* fistIP;
  char* lastIP;
  int numberHosts;
  char* ipType;
} ResultIP;

void askUserInput (WINDOW* mainWindow, char* ipUser, char* numberHosts);

int main(void) {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(1);

  /* smaller so it works on small terminals */
  WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
  box(mainWindow, 0, 0);

  char* ipUser = calloc(20, sizeof(char));
  char* numberHosts = calloc(20, sizeof(char));

  askUserInput(mainWindow, ipUser, numberHosts);

  // CREAR MENU
  ResultIP results = {"", 21, "", "", "", "", 2, ""};
  int resultsLenght = sizeof(results) / sizeof(int);

  noecho();
  curs_set(0);

  WINDOW* menuIP = newwin(LINES - 2, 20, 1, 2);
  box(menuIP, 0, 0);

  bool isRunning = true;
  int highlight = 0;

  while (isRunning) {
    for (int i = 0; i < resultsLenght; i++) {
      if (i == highlight) {
        wattron(menuIP, A_REVERSE);
        mvwprintw(menuIP, 2, 2, "AREA %03d", i + 1);
        wattroff(menuIP, A_REVERSE);
      }
    }
    switch (wgetch(menuIP)) {
      case KEY_UP:

    }
  }

  delwin(mainWindow);
  endwin();
  return EXIT_SUCCESS;
}

void askUserInput (WINDOW* mainWindow, char* ipUser, char* numberHosts)
{
  int inptWidth, inptHeight, inputX, inputY;

  inptHeight = 3;
  inptWidth = 20;
  inputY = LINES / 2;
  inputX = (COLS - 20) / 2;

  WINDOW* inputIPuser = newwin(inptHeight, inptWidth, inputY, inputX);
  box(inputIPuser, 0, 0);

  mvwprintw(mainWindow, inputY - 1, inputX + 2, "INGRESE LA IP");
  wrefresh(mainWindow);
  wrefresh(inputIPuser);

  mvwgetstr(inputIPuser, 1, 2, ipUser);

  inputIPuser = newwin(inptHeight, inptWidth, inputY, inputX);
  box(inputIPuser, 0, 0);

  mvwprintw(mainWindow, inputY - 1, inputX - 4, "INGRESE LA CANTIDAD DE HOSTS");
  wrefresh(mainWindow);
  wrefresh(inputIPuser);

  mvwgetstr(inputIPuser, 1, 2, numberHosts);

  wborder(inputIPuser, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wclear(inputIPuser);
  wrefresh(inputIPuser);

  mvwprintw(mainWindow, inputY - 1, inputX - 4, "                            ");
  wrefresh(mainWindow);
  delwin(inputIPuser);
}






