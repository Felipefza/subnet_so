#ifndef WINDOWNCURSES_H
#define WINDOWNCURSES_H

#include <ncurses.h>

// LOCAL FILES
#include "../include/ip_calc.h"

int initNcurses();
void endNcurses(WINDOW* mainWindow);
void askUserInput (WINDOW* mainWindow, char* outString, const char* message);

int showResults(WINDOW* mainWindow, ResultIP* results, int* numberAreas);
void showError(WINDOW* mainWindow, const char* message);
void showInformation(WINDOW* window, int* index, ResultIP* results, int* maxX, int* maxY);
void showHints(WINDOW* informationIP, int* maxY);

void setMenuIP(WINDOW* menuIP, int* highlight, int* min, int* max);
void setIndex(WINDOW* informationIP, int* maxY, int* index, bool* isLast);

void exitWindow(WINDOW* window);

int getHosts(WINDOW* mainWindow, int* numberHosts, const char* message);
int getBroadcast(WINDOW* mainWindow, int* numberHosts, char* broadcast, Octetcs* pOctectNet);
int resetNet(WINDOW* mainWindow, char* net, Octetcs* pOctectbroad, Octetcs* pOctectUser);
void getResults(WINDOW* mainWindow, Octetcs* pOctectUser, int* numberAreas, ResultIP* results);

void setColorMvwprint(WINDOW* window, int* indexColorPair, int* y, int* x, char* format, const char* message);

#endif // !WINDOWNCURSES_H

