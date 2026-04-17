#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// LOCAL FILES
#include "../include/windowsNcurses.h"

int main(void) {

  if (initNcurses()) {
    return EXIT_FAILURE;
  }

  WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
  box(mainWindow, 0, 0);

  int numberAreas;

  char* buffer = calloc(20, sizeof(buffer));
  char* ipUser = calloc(20, sizeof(char));

  askUserInput(mainWindow, ipUser, "INGRESE LA IP");
  askUserInput(mainWindow, buffer, "INGRESE LA CANTIDAD DE AREAS");

  numberAreas = atoi(buffer);
  ResultIP* results = calloc(numberAreas, sizeof(*results));

  free(buffer);
  buffer = NULL;

  if (calcALL(mainWindow, results, ipUser, &numberAreas)) {
    return EXIT_FAILURE;
  }

  free(ipUser);
  ipUser = NULL;

  showResults(results, &numberAreas);

  werase(mainWindow);
  wrefresh(mainWindow);
  delwin(mainWindow);
  endwin();
  return EXIT_SUCCESS;
}
