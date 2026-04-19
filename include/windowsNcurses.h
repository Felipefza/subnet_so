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
void showInformation(WINDOW* window, int* index, ResultIP* results, int* maxX);
void showHints(WINDOW* informationIP, int* maxY);

void setMenuIP(WINDOW* menuIP, int* highlight, int* min, int* max);
void setIndex(WINDOW* informationIP, int* maxY, int* index, bool* isLast);

void exitWindow(WINDOW* window);

int calcALL (WINDOW* mainWindow, ResultIP* results, Octetcs* pOctectUser, int* pNumberAreas);

#endif // !WINDOWNCURSES_H

