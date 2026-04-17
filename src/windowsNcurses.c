#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
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
    return 1;
  }

  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);

  return 0;
}

int windowInput(WINDOW* mainWindow)
{
  char* buffer = calloc(20, sizeof(buffer));
  char* ipUser = calloc(20, sizeof(char));

  int numberAreas;

  askUserInput(mainWindow, ipUser, "INGRESE LA IP");
  askUserInput(mainWindow, buffer, "INGRESE LA CANTIDAD DE AREAS");

  numberAreas = atoi(buffer);

  ResultIP* results = calloc(numberAreas, sizeof(*results));

  free(buffer);
  buffer = NULL;

  if (calcALL(mainWindow, results, ipUser, &numberAreas)) {
  
    return EXIT_FAILURE;
  }

  showResults(results, &numberAreas);
  return EXIT_SUCCESS;
}

void showResults(ResultIP* results, int* numberAreas)
{
  raw();
  noecho();
  curs_set(0);

  WINDOW* menuIP = newwin(LINES - 2, 20, 1, 2);
  box(menuIP, 0, 0);
  wrefresh(menuIP);

  WINDOW* informationIP = newwin(LINES - 2, COLS - 24, 1, 22);
  wrefresh(informationIP);

  bool isRunning = true;
  int highlight = 0;
  int information = 0;

  while (isRunning) {
    for (int i = 0; i < *numberAreas; i++) {
      if (i == highlight) {
        wattron(menuIP, COLOR_PAIR(1));
        mvwprintw(menuIP, i + 1, 5, "AREA %03d", i + 1);
        wattroff(menuIP, COLOR_PAIR(1));
      }
      else {
        mvwprintw(menuIP, i + 1, 5, "AREA %03d", i + 1);
      }

      if (i == information) {
        int x, y;
        getmaxyx(informationIP, y, x);

        wclear(informationIP);
        mvwprintw(informationIP, 10, x / 2 - 11, "SUBNET AREA NUMERO %03d", i + 1); 
        mvwprintw(informationIP, 12, x / 2 - 22, "IP:                            %s / %d", results[i].net, results[i].masc); 
        mvwprintw(informationIP, 14, x / 2 - 22, "MASCARA PUNTEADA:              %s", results[i].mascPunteada); 
        mvwprintw(informationIP, 16, x / 2 - 22, "RED:                           %s / %d\t\n", results[i].net, results[i].masc); 
        mvwprintw(informationIP, 18, x / 2 - 22, "PRIMERA IP UTILIZABLE:         %s", results[i].fistIP);                     
        mvwprintw(informationIP, 20, x / 2 - 22, "ULTIMA IP UTILIZABLE:          %s", results[i].lastIP);                     
        mvwprintw(informationIP, 22, x / 2 - 22, "BROADCAST:                     %s", results[i].broadcast);                  
        mvwprintw(informationIP, 24, x / 2 - 22, "CANTIDAD DE HOSTS TOTALES:     %d", results[i].numberHosts);                
        mvwprintw(informationIP, 26, x / 2 - 22, "CANTIDAD DE HOSTS UTILIZABLES: %d", results[i].numberHosts - 2);            
        mvwprintw(informationIP, 28, x / 2 - 22, "TIPO DE IP:                    %s", results[i].ipType);                     

        box(informationIP, 0, 0);


        wattron(informationIP, COLOR_PAIR(1));
        wattron(informationIP, A_BOLD);
        mvwprintw(informationIP, y - 1, 2, " q: salir ");                     
        mvwprintw(informationIP, y - 1, 14, " k: arriba ");                     
        mvwprintw(informationIP, y - 1, 27, " j: abajo ");                     
        wattroff(informationIP, A_BOLD);
        wattroff(informationIP, COLOR_PAIR(1));

        wrefresh(informationIP);
      }
    }
    switch (wgetch(menuIP)) {
      case KEY_UP:
        if (highlight > 0) highlight--;
        break;
      case KEY_DOWN:
        if (highlight < *numberAreas - 1) highlight++;
        break;
      case 'k':
        if (highlight > 0) highlight--;
        break;
      case 'j':
        if (highlight < *numberAreas - 1) highlight++;
        break;
      case 'q':
        isRunning = false;
        werase(informationIP);
        wrefresh(informationIP);
        delwin(informationIP);
        break;
      default:
        break;
    }
    information = highlight;
  }
}

void askUserInput (WINDOW* mainWindow, char* outString, const char* message)
{
  char* buffer = calloc(1024, sizeof(buffer));
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

  wborder(inputIPuser, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wclear(inputIPuser);
  wrefresh(inputIPuser);

  mvwprintw(mainWindow, inputY - 1, inputX - 4, "                            ");
  wrefresh(mainWindow);
  delwin(inputIPuser);
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

  wclear(mainWindow);
  wrefresh(mainWindow);
  delwin(mainWindow);
  endwin();
}

int calcALL (WINDOW* mainWindow, ResultIP* results, char* pUserIP, int* pNumberAreas)
{
  String_View sv_user_ip = sv(pUserIP);
  Octetcs pOctectUser = {0};


  if (arrayInput(&sv_user_ip, &pOctectUser)) {
    showError(mainWindow, "FORMATO INCORRECTO");
    return EXIT_FAILURE;
  }

  char* netAddrs = calloc(15, sizeof(netAddrs));
  char* ipType = calloc(15, sizeof(ipType));

  calcNetAdrrs(&pOctectUser, netAddrs);
  calcType(&pOctectUser, ipType);

  for (int i = 0; i < *pNumberAreas; i++)
  {
    int* numberHosts = calloc(20, sizeof(numberHosts));
    char* broadcast = calloc(15, sizeof(broadcast));
    int* masc = calloc(2, sizeof(masc));
    char* mascPunteada = calloc(35, sizeof(mascPunteada));

    char* fistIP = calloc(20, sizeof(fistIP));
    char* lastIP = calloc(20, sizeof(lastIP));

    Octetcs pOctectNet = {0};
    Octetcs pOctectbroad = {0};

    char* buffer = calloc(20, sizeof(buffer));

    char* messageFormated = calloc(40, sizeof(messageFormated));
    sprintf(messageFormated, "%s %d", "INGRESE LOS HOSTS DE AREA NUMERO", i);

    askUserInput(mainWindow, buffer, messageFormated);

    *numberHosts = atoi(buffer);

    free(buffer);
    buffer = NULL;

    String_View sv_net_ip = sv(netAddrs);

    if (arrayInput(&sv_net_ip, &pOctectNet)) {
      showError(mainWindow, "FORMATO INCORRECTO");
      return EXIT_FAILURE;
    }

    calcMasc(numberHosts, masc, mascPunteada);

    addIP(&pOctectNet, *numberHosts - 1, broadcast);

    String_View sv_broad_ip = sv(broadcast);

    arrayInput(&sv_broad_ip, &pOctectbroad);

    addIP(&pOctectNet, 1, fistIP);
    subIP(&pOctectbroad, lastIP, 1);

    ResultIP resultadoIP = {
      strdup(netAddrs), 
      *masc, 
      strdup(mascPunteada), 
      strdup(broadcast), 
      strdup(fistIP), 
      strdup(lastIP), 
      *numberHosts, 
      strdup(ipType)
    };
    results[i] = resultadoIP;

    sprintf(netAddrs, "%s", "");
    addIP(&pOctectbroad, 1, netAddrs);

    Octetcs pOctectNewNet = {0};

    String_View sv_new_ip = sv(netAddrs);

    arrayInput(&sv_new_ip, &pOctectNewNet);

    pOctectUser = pOctectNewNet;
  }

  return EXIT_SUCCESS;
}
