#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LOCAL FILES
#include "../include/ip_calc.h"
#include "../include/windowsNcurses.h"

int initNcurses()
{
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(1);

  if (has_colors() == FALSE) {
    endwin();
    return EXIT_FAILURE;
  }

  start_color();

  /*
   * 1 : USER CHOICE AND HINTS
   * 2 : LIMIT INDEX *
   * 3 : CAN CHANGE PAGE TO THE RIGHT +
   * 4 : CAN CHANGE PAGE TO THE LEFT -
    */

  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);

  return EXIT_SUCCESS;
}

void endNcurses(WINDOW* mainWindow)
{
  curs_set(1);
  echo();
  exitWindow(mainWindow);
  endwin();
}

int showResults(WINDOW* mainWindow, ResultIP* results, int* numberAreas)
{
  raw();
  noecho();
  curs_set(0);

  WINDOW* menuIP = newwin(LINES - 2, 20, 1, 2);
  box(menuIP, 0, 0);
  wrefresh(menuIP);

  WINDOW* informationIP = newwin(LINES - 2, COLS - 24, 1, 22);
  wrefresh(informationIP);
  box(informationIP, 0, 0);

  int informationMaxX, informationMaxY;
  getmaxyx(informationIP, informationMaxY, informationMaxX);

  bool isRunning = true;
  int highlight = 0;

  wrefresh(informationIP);

  int AREAS_PER_PAGE = informationMaxY / 2 - 4;
  int index = 0;
  bool isLast = false;

  while (isRunning) {
    int tmp = AREAS_PER_PAGE * (index + 1);
    int min = AREAS_PER_PAGE * index;
    int max = minTwoNumbers(&tmp, numberAreas);

    if (max - *numberAreas == 0) {
      isLast = true;
    } else {
      isLast = false;
    }

    werase(menuIP);
    box(menuIP, 0, 0);

    werase(informationIP);

    if (LINES < 14) {
      showError(mainWindow, "LA VENTANA TIENE QUE SER MAYOR QUE 14 LINEAS");
      return EXIT_FAILURE;
    }

    setMenuIP(menuIP, &highlight, &min, &max);
    setIndex(menuIP, &informationMaxY, &index, &isLast);
    showInformation(informationIP, &highlight, results, &informationMaxX, &informationMaxY);

    box(informationIP, 0, 0);

    showHints(informationIP, &informationMaxY);

    wrefresh(informationIP);
    wrefresh(menuIP);

    switch (wgetch(menuIP)) {
      case KEY_UP:
        if (highlight > min) highlight--;
        break;
      case KEY_DOWN:
        if (highlight < max) highlight++;
        break;
      case 'k':
        if (highlight > min) highlight--;
        break;
      case 'j':
        if (highlight < max - 1) highlight++;
        break;
      case 'h':
        if (min != 0) {
          index--;
          highlight = min - AREAS_PER_PAGE;
        }
        break;
      case 'l':
        if (max - *numberAreas != 0) {
          index++;
          highlight = min + AREAS_PER_PAGE;
        }
        break;
      case 'q':
        isRunning = false;

        exitWindow(informationIP);
        exitWindow(menuIP);
        break;
      default:
        break;
    }
  }
  return EXIT_SUCCESS;
}

void askUserInput (WINDOW* mainWindow, char* outString, const char* message)
{
  werase(mainWindow);
  box(mainWindow, 0, 0);

  int inptWidth, inptHeight, inputX, inputY;

  int lengthMessage = strlen(message);

  inptHeight = 3;
  inptWidth = 20;
  inputY = LINES / 2;
  inputX = (COLS - 20) / 2;

  WINDOW* inputIPuser = newwin(inptHeight, inptWidth, inputY, inputX);
  box(inputIPuser, 0, 0);

  mvwprintw(mainWindow, inputY - 1, COLS / 2 - lengthMessage / 2, "%s", message);
  wrefresh(mainWindow);
  wrefresh(inputIPuser);

  mvwgetstr(inputIPuser, 1, 2, outString);

  exitWindow(inputIPuser);
  mvwprintw(mainWindow, inputY - 1, inputX - 4, "                            ");
  wrefresh(mainWindow);
}

void showError(WINDOW* mainWindow, const char* message)
{
  curs_set(0);

  int lengthMessage = strlen(message);

  WINDOW* errorWindow = newwin(LINES, COLS, 0, 0);
  box(errorWindow, 0, 0);

  WINDOW* messageWindow = newwin(3, lengthMessage + 4, LINES / 2, COLS / 2 - lengthMessage / 2);
  box(messageWindow, 0, 0);

  mvwprintw(messageWindow, 1, 2, "%s", message);

  wrefresh(errorWindow);
  wrefresh(messageWindow);

  wgetch(errorWindow);


  exitWindow(errorWindow);
  exitWindow(messageWindow);

  endNcurses(mainWindow);
}

void getResults(WINDOW* mainWindow, Octetcs* pOctectUser, int* numberAreas, ResultIP* results)
{
  char* messageFormated = calloc(40, sizeof(messageFormated));

  char* net = calloc(16, sizeof(*net));
  char* ipType = calloc(30, sizeof(*ipType));

  int* numberHosts = calloc(15, sizeof(*numberHosts));

  char* fistIP = calloc(15, sizeof(*fistIP));
  char* lastIP = calloc(15, sizeof(*lastIP));

  int* masc = calloc(3, sizeof(*masc));
  char* mascPunteada = calloc(35, sizeof(*mascPunteada));
  char* broadcast = calloc(16, sizeof(*broadcast));

  calcNetAdrrs(pOctectUser, net);
  calcType(pOctectUser, ipType);

  for (int index = 0; index < *numberAreas; index++) {
    *numberHosts = 0;
    *masc = 0;

    sprintf(mascPunteada, "%s", "");

    sprintf(fistIP, "%s", "");
    sprintf(lastIP, "%s", "");

    Octetcs pOctectNet = {0};
    Octetcs pOctectbroad = {0};

    sprintf(messageFormated, "%s %d", "INGRESE LOS HOSTS DE AREA NUMERO", index + 1);

    getHosts(mainWindow, numberHosts, messageFormated);

    calcMasc(numberHosts, masc, mascPunteada);

    String_View sv_net_ip = sv(net);
    arrayInput(&sv_net_ip, &pOctectNet);

    getBroadcast(mainWindow, numberHosts, broadcast, &pOctectNet);

    String_View sv_broad_ip = sv(broadcast);
    arrayInput(&sv_broad_ip, &pOctectbroad);

    addIP(&pOctectNet, 1, fistIP);
    subIP(&pOctectbroad, lastIP, 1);

    ResultIP tmpResult = {
      strdup(net),
      *masc,
      strdup(mascPunteada),
      strdup(broadcast),
      strdup(fistIP),
      strdup(lastIP),
      *numberHosts,
      strdup(ipType)
    };

    results[index] = tmpResult;

    resetNet(mainWindow, net, &pOctectbroad, pOctectUser);
  }
  free(numberHosts);
  free(masc);
  free(mascPunteada);
  free(fistIP);
  free(lastIP);


  free(net);
  free(ipType);
}

void showInformation(WINDOW* window, int* index, ResultIP* results, int* maxX, int* maxY)
{
  mvwprintw(window, *maxY / 2 - 10, *maxX / 2 - 11, "SUBNET AREA NUMERO %03d", *index + 1); 
  mvwprintw(window, *maxY / 2 - 10 + 2, *maxX / 2 - 22, "IP:                            %s / %d", results[*index].net, results[*index].masc); 
  mvwprintw(window, *maxY / 2 - 10 + 4, *maxX / 2 - 22, "MASCARA PUNTEADA:              %s", results[*index].mascPunteada); 
  mvwprintw(window, *maxY / 2 - 10 + 6, *maxX / 2 - 22, "RED:                           %s / %d\t\n", results[*index].net, results[*index].masc); 
  mvwprintw(window, *maxY / 2 - 10 + 8, *maxX / 2 - 22, "PRIMERA IP UTILIZABLE:         %s", results[*index].fistIP);                     
  mvwprintw(window, *maxY / 2 - 10 + 10, *maxX / 2 - 22, "ULTIMA IP UTILIZABLE:          %s", results[*index].lastIP);                     
  mvwprintw(window, *maxY / 2 - 10 + 12, *maxX / 2 - 22, "BROADCAST:                     %s", results[*index].broadcast);                  
  mvwprintw(window, *maxY / 2 - 10 + 14, *maxX / 2 - 22, "CANTIDAD DE HOSTS TOTALES:     %d", results[*index].numberHosts);                
  mvwprintw(window, *maxY / 2 - 10 + 16, *maxX / 2 - 22, "CANTIDAD DE HOSTS UTILIZABLES: %d", results[*index].numberHosts - 2);            
  mvwprintw(window, *maxY / 2 - 10 + 18, *maxX / 2 - 22, "TIPO DE IP:                    %s", results[*index].ipType);                     
}

int resetNet(WINDOW* mainWindow, char* net, Octetcs* pOctectbroad, Octetcs* pOctectUser)
{
  sprintf(net, "%s", "");
  if (addIP(pOctectbroad, 1, net)) {
    showError(mainWindow, "SE LLEGO AL MAXIMO IP");
    return EXIT_FAILURE;
  }
  Octetcs pOctectNewNet = {0};

  String_View sv_new_ip = sv(net);
  arrayInput(&sv_new_ip, &pOctectNewNet);

  *pOctectUser = pOctectNewNet;

  return EXIT_SUCCESS;
}

int getHosts(WINDOW* mainWindow, int* numberHosts, const char* message)
{
  *numberHosts = 0;

  char* buffer = calloc(20, sizeof(buffer));

  askUserInput(mainWindow, buffer, message);

  if (!isValidNumber(buffer)) {
    showError(mainWindow, "SOLO NUMEROS POSITIVOS");
    return EXIT_FAILURE;
  }

  *numberHosts = atoi(buffer);

  free(buffer);
  buffer = NULL;

  return EXIT_SUCCESS;
}

int getBroadcast(WINDOW* mainWindow, int* numberHosts, char* broadcast, Octetcs* pOctectNet)
{
  sprintf(broadcast, " ");
  if (addIP(pOctectNet, *numberHosts - 1, broadcast)) {
    showError(mainWindow, "SE LLEGO AL MAXIMO IP");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;

}


void setMenuIP(WINDOW* menuIP, int* highlight, int* min, int* max)
{
  int j = 1;
  for (int i = *min; i < *max; i++) {
    if (i == *highlight) {
      wattron(menuIP, COLOR_PAIR(1));
      mvwprintw(menuIP, j + 1, 5, "AREA %03d", i + 1);
      wattroff(menuIP, COLOR_PAIR(1));
    }
    else {
      mvwprintw(menuIP, j + 1, 5, "AREA %03d", i + 1);
    }
    j += 2;
  }
}

void setIndex(WINDOW* informationIP, int* maxY, int* index, bool* isLast)
{
  wattron(informationIP, A_BOLD);
  int Y_CHAR = (*maxY - 3);

  int X_FIRST_CHAR = 4;
  int X_MIDDLE_CHAR = 8;
  int X_LAST_CHAR = 14;

  int INDEX_COLOR = 1;
  int MULT_SIGN_COLOR = 2;
  int PLUS_SIGN_COLOR = 3;
  int NEGATIVE_SIGN_COLOR = 4;

  if (*index == 0 && *isLast) {
    setColorMvwprint(informationIP, &MULT_SIGN_COLOR, &Y_CHAR, &X_FIRST_CHAR, "%s", "*");
    setColorMvwprint(informationIP, &MULT_SIGN_COLOR, &Y_CHAR, &X_LAST_CHAR, "%s", "*");

  } else if (*index == 0) {
    setColorMvwprint(informationIP, &MULT_SIGN_COLOR, &Y_CHAR, &X_FIRST_CHAR, "%s", "*");
    setColorMvwprint(informationIP, &PLUS_SIGN_COLOR, &Y_CHAR, &X_LAST_CHAR, "%s", "+");

  } else if (*isLast) {
    setColorMvwprint(informationIP, &NEGATIVE_SIGN_COLOR, &Y_CHAR, &X_FIRST_CHAR, "%s", "-");
    setColorMvwprint(informationIP, &MULT_SIGN_COLOR, &Y_CHAR, &X_LAST_CHAR, "%s", "*");
  } else {
    setColorMvwprint(informationIP, &NEGATIVE_SIGN_COLOR, &Y_CHAR, &X_FIRST_CHAR, "%s", "-");
    setColorMvwprint(informationIP, &PLUS_SIGN_COLOR, &Y_CHAR, &X_LAST_CHAR, "%s", "+");
  }

  char* buffer = calloc(3, sizeof(buffer));
  sprintf(buffer, "%02d", *index + 1);


  setColorMvwprint(informationIP, &INDEX_COLOR, &Y_CHAR, &X_MIDDLE_CHAR, "%s", buffer);
  wattroff(informationIP, A_BOLD);

  free(buffer);
  buffer = NULL;
}

void showHints(WINDOW* informationIP, int* maxY)
{
  char* hintsList[] = {
    " q: salir ",
    " k: arriba ",
    " j: abajo ",
    " h: pagina anterior ",
    " l: pagina siguiente "
  };

  int hintLenght = sizeof(hintsList) / sizeof(*hintsList); 
  int sum = 2;

  wattron(informationIP, COLOR_PAIR(1));
  wattron(informationIP, A_BOLD);

  for (int i = 0; i < hintLenght; i++) {
    mvwprintw(informationIP, *maxY - 1, sum, "%s", hintsList[i]);
    sum = strlen(hintsList[i]) + 2 + sum;
  }

  wattroff(informationIP, A_BOLD);
  wattroff(informationIP, COLOR_PAIR(1));
}


void exitWindow(WINDOW* window)
{
  wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  werase(window);
  wrefresh(window);
  delwin(window);
}

void setColorMvwprint(WINDOW* window, int* indexColorPair, int* y, int* x, char* format, const char* message)
{
  wattron(window, COLOR_PAIR(*indexColorPair));
  mvwprintw(window, *y, *x, format, message);
  wattroff(window, COLOR_PAIR(*indexColorPair));
}
