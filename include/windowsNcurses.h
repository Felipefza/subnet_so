#ifndef WINDOWNCURSES_H
#define WINDOWNCURSES_H

#include <ncurses.h>

// LOCAL FILES
#include "../include/ip_calc.h"

int initNcurses();
void endNcurses(WINDOW* mainWindow);
void askUserInput (WINDOW* mainWindow, char* outString, const char* message);
void showResults(ResultIP* results, int* numberAreas);
void showError(WINDOW* mainWindow, const char* message);
int calcALL (WINDOW* mainWindow, ResultIP* results, Octetcs* pOctectUser, int* pNumberAreas);
void showInformation(WINDOW* window, int* index, ResultIP* results, int* maxX);

#endif // !WINDOWNCURSES_H

