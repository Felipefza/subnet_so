#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// LOCAL FILES
#include "../include/windowsNcurses.h"

int main(void) {

  if (initNcurses()) {
    return EXIT_FAILURE;
  }

  WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
  box(mainWindow, 0, 0);

  char* ipUser = calloc(20, sizeof(char));

  askUserInput(mainWindow, ipUser, "INGRESE LA IP");

  String_View sv_user_ip = sv(ipUser);
  Octetcs pOctectUser = {0};

  if (arrayInput(&sv_user_ip, &pOctectUser)) {
    free(ipUser);

    showError(mainWindow, "FORMATO INCORRECTO");
    return EXIT_FAILURE;
  }

  char* buffer = calloc(20, sizeof(buffer));

  askUserInput(mainWindow, buffer, "INGRESE LA CANTIDAD DE AREAS");

  if (isValidNumber(buffer)) {
    showError(mainWindow, "SOLO NUMEROS");
    return EXIT_FAILURE;
  }

  int numberAreas = atoi(buffer);
  ResultIP* results = calloc(numberAreas, sizeof(*results));

  free(buffer);
  buffer = NULL;

  if (calcALL(mainWindow, results, &pOctectUser, &numberAreas)) {
    return EXIT_FAILURE;
  }

  free(ipUser);
  ipUser = NULL;

  showResults(results, &numberAreas);

  endNcurses(mainWindow);
  return EXIT_SUCCESS;
}
