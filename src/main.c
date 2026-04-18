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

  char* ipUser = calloc(20, sizeof(char));

  askUserInput(mainWindow, ipUser, "INGRESE LA IP");

  String_View sv_user_ip = sv(ipUser);
  Octetcs pOctectUser = {0};

  if (arrayInput(&sv_user_ip, &pOctectUser)) {
    free(ipUser);

    showError(mainWindow, "FORMATO INCORRECTO");
    endNcurses(mainWindow);
    return EXIT_FAILURE;
  }

  char* buffer = calloc(20, sizeof(buffer));

  askUserInput(mainWindow, buffer, "INGRESE LA CANTIDAD DE AREAS");

  numberAreas = atoi(buffer);
  ResultIP* results = calloc(numberAreas, sizeof(*results));

  free(buffer);
  buffer = NULL;


  if (calcALL(mainWindow, results, &pOctectUser, &numberAreas)) {
    showError(mainWindow, "FORMATO INCORRECTO");
    endNcurses(mainWindow);
    return EXIT_FAILURE;
  }

  free(ipUser);
  ipUser = NULL;

  showResults(results, &numberAreas);

  endNcurses(mainWindow);
  return EXIT_SUCCESS;
}
