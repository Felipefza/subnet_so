#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// LOCAL FILES
#include "../include/string_view.h"
#include "../include/user_input.h"
#include "../include/ip_calc.h"

// ncurses LIBRARIES
#include <ncurses.h>
#include <panel.h>
#include <string.h>


int main(int argc, char *argv[])
{
  char* pUserIP = calloc(15, sizeof(char));
  char* pMessage = "INGRESE LA IP EJ: '192.168.1.1', SEPARADO POR UN PUNTO (.)";

  askUserInput(pUserIP, pMessage, "%15s");

  String_View sv_user_ip = sv(pUserIP);
  Octetcs pOctectUser = {0};

  arrayInput(&sv_user_ip, &pOctectUser);

  int pNumberAreas;
  askUserInput(&pNumberAreas, "INGRESE CANTIDAD DE AREAS (MAX 2 DIGITS)", "%2d");

  ResultIP* resultados = calloc(pNumberAreas, sizeof(*resultados));

  char* netAddrs = calloc(15, sizeof(netAddrs));
  char* ipType = calloc(15, sizeof(ipType));

  calcNetAdrrs(&pOctectUser, netAddrs);
  calcType(&pOctectUser, ipType);

  for (int i = 0; i < pNumberAreas; i++)
  {
    int* numberHosts = calloc(20, sizeof(numberHosts));
    char* broadcast = calloc(15, sizeof(broadcast));
    int* masc = calloc(2, sizeof(masc));
    char* mascPunteada = calloc(35, sizeof(mascPunteada));

    char* fistIP = calloc(20, sizeof(fistIP));
    char* lastIP = calloc(20, sizeof(lastIP));

    Octetcs pOctectNet = {0};
    Octetcs pOctectbroad = {0};

    printf("\nAREA NUMERO %d\n", i + 1);
    askUserInput(numberHosts, "INGRESE CANTIDAD DE HOSTS UTILIZABLES", "%5d");

    String_View sv_net_ip = sv(netAddrs);

    arrayInput(&sv_net_ip, &pOctectNet);

    calcMasc(numberHosts, masc, mascPunteada);

    *numberHosts += 2;

    int hosts = 0;
    int j = 0;
    while (hosts < *numberHosts) {
      hosts = pow(2, j);
      j++;
    }

    addIP(&pOctectNet, hosts - 1, broadcast);

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
    resultados[i] = resultadoIP;

    sprintf(netAddrs, "%s", "");
    addIP(&pOctectbroad, 1, netAddrs);

    Octetcs pOctectNewNet = {0};

    String_View sv_new_ip = sv(netAddrs);

    arrayInput(&sv_new_ip, &pOctectNewNet);

    pOctectUser = pOctectNewNet;

  }

  printResults(resultados, &pNumberAreas);

  return EXIT_SUCCESS;
}


