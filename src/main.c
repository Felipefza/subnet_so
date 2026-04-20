#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LOCAL FILES
#include "../include/windowsNcurses.h"

/*
  * RETURNING VALUES
  * 0 : FUNCTION ENDED SUCCESSFULL
  * 1 : FUNCTION ENDED FAILED
  * 2 : THE USER WANT TO CONTINUE
*/

int main(void) {

  bool isRunning = true;

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

  while (isRunning) {
    askUserInput(mainWindow, buffer, "INGRESE LA CANTIDAD DE AREAS");

    if (!isValidNumber(buffer)) {
      if (showError(mainWindow, "SOLO NUMEROS POSITIVOS") != 2) {
        return EXIT_FAILURE;
      }
      printf(buffer, "%s", "");
      continue;
    }
    isRunning = false;
  }

  int numberAreas = atoi(buffer);
  ResultIP* results = calloc(numberAreas, sizeof(*results));

  free(buffer);
  buffer = NULL;

  if (getResults(mainWindow, &pOctectUser, &numberAreas, results)) {
    endNcurses(mainWindow);
    return EXIT_FAILURE;
  }

  free(ipUser);
  ipUser = NULL;

  if (showResults(mainWindow, results, &numberAreas)) {
    return EXIT_FAILURE;
  }

  free(results);

  endNcurses(mainWindow);
  return EXIT_SUCCESS;
}
