#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// LOCAL FILES
#include "../include/ip_calc.h"
#include "../include/string_view.h"

void askUserInput (WINDOW* mainWindow, char* ipUser, int* numberAreas);
void askUserHosts (WINDOW* mainWindow, int* numberHosts, int* i);
void calcALL (WINDOW* mainWindow, ResultIP* results, char* pUserIP, int* pNumberAreas);

int main(void) {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(1);

  /* smaller so it works on small terminals */
  WINDOW* mainWindow = newwin(LINES, COLS, 0, 0);
  box(mainWindow, 0, 0);

  char* ipUser = calloc(20, sizeof(char));
  int numberAreas;

  askUserInput(mainWindow, ipUser, &numberAreas);

  ResultIP* results = calloc(numberAreas, sizeof(*results));

  calcALL(mainWindow, results, ipUser, &numberAreas);

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
    for (int i = 0; i < numberAreas; i++) {
      if (i == highlight) {
        wattron(menuIP, A_REVERSE);
        mvwprintw(menuIP, i * 2 + 2, 5, "AREA %03d", i + 1);
        wattroff(menuIP, A_REVERSE);
      }
      else {
        mvwprintw(menuIP, i * 2 + 2, 5, "AREA %03d", i + 1);
      }

      if (i == information) {
        int x;
        x = getmaxx(informationIP);

        wclear(informationIP);
        mvwprintw(informationIP, 10, x / 3, "========== SUBNET AREA NUMERO %03d ==========", i + 1); 
        mvwprintw(informationIP, 12, x / 3, "IP: %s / %d", results[i].net, results[i].masc); 
        mvwprintw(informationIP, 14, x / 3, "MASCARA PUNTEADA:              %s", results[i].mascPunteada); 
        mvwprintw(informationIP, 16, x / 3, "RED:                           %s / %d\t\n", results[i].net, results[i].masc); 
        mvwprintw(informationIP, 18, x / 3, "PRIMERA IP UTILIZABLE:         %s", results[i].fistIP);                     
        mvwprintw(informationIP, 20, x / 3, "ULTIMA IP UTILIZABLE:          %s", results[i].lastIP);                     
        mvwprintw(informationIP, 22, x / 3, "BROADCAST:                     %s", results[i].broadcast);                  
        mvwprintw(informationIP, 24, x / 3, "CANTIDAD DE HOSTS TOTALES:     %d", results[i].numberHosts);                
        mvwprintw(informationIP, 26, x / 3, "CANTIDAD DE HOSTS UTILIZABLES: %d", results[i].numberHosts - 2);            
        mvwprintw(informationIP, 28, x / 3, "TIPO DE IP:                    %s", results[i].ipType);                     
        box(informationIP, 0, 0);
        wrefresh(informationIP);
      }
    }
    switch (wgetch(menuIP)) {
      case KEY_UP:
        if (highlight > 0) highlight--;
        break;
      case KEY_DOWN:
        if (highlight < numberAreas - 1) highlight++;
      case 'k':
        if (highlight > 0) highlight--;
        break;
      case 'j':
        if (highlight < numberAreas - 1) highlight++;
      default:
        break;
    }
    information = highlight;
  }

  delwin(mainWindow);
  endwin();
  return EXIT_SUCCESS;
}

void askUserInput (WINDOW* mainWindow, char* ipUser, int* numberAreas)
{
  char* buffer = calloc(1024, sizeof(buffer));
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

  mvwprintw(mainWindow, inputY - 1, inputX - 4, "INGRESE LA CANTIDAD DE AREAS");
  wrefresh(mainWindow);
  wrefresh(inputIPuser);

  mvwgetstr(inputIPuser, 1, 2, buffer);
  *numberAreas = atoi(buffer);


  wborder(inputIPuser, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wclear(inputIPuser);
  wrefresh(inputIPuser);

  mvwprintw(mainWindow, inputY - 1, inputX - 4, "                            ");
  wrefresh(mainWindow);
  delwin(inputIPuser);
}


void askUserHosts (WINDOW* mainWindow, int* numberHosts, int* i)
{
  char* buffer = calloc(1024, sizeof(buffer));
  int inptWidth, inptHeight, inputX, inputY;

  inptHeight = 3;
  inptWidth = 20;
  inputY = LINES / 2;
  inputX = (COLS - 20) / 2;

  WINDOW* inputIPuser = newwin(inptHeight, inptWidth, inputY, inputX);
  box(inputIPuser, 0, 0);

  mvwprintw(mainWindow, inputY - 3, inputX + 3, "AREA NUMERO %d", *i + 1);
  mvwprintw(mainWindow, inputY - 1, inputX - 9, "INGRESE LA CANTIDAD DE HOSTS UTILIZABLES");
  wrefresh(mainWindow);
  wrefresh(inputIPuser);

  mvwgetstr(inputIPuser, 1, 2, buffer);
  *numberHosts = atoi(buffer);

  wborder(inputIPuser, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wclear(inputIPuser);
  wrefresh(inputIPuser);

  mvwprintw(mainWindow, inputY - 3, inputX - 4, "                            ");
  mvwprintw(mainWindow, inputY - 1, inputX - 4, "                            ");
  wrefresh(mainWindow);
  delwin(inputIPuser);
}

void calcALL (WINDOW* mainWindow, ResultIP* results, char* pUserIP, int* pNumberAreas)
{
  String_View sv_user_ip = sv(pUserIP);
  Octetcs pOctectUser = {0};
  arrayInput(&sv_user_ip, &pOctectUser);

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

    askUserHosts(mainWindow, numberHosts, &i);

    String_View sv_net_ip = sv(netAddrs);

    arrayInput(&sv_net_ip, &pOctectNet);

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
}


