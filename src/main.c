#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// LOCAL FILES
#include "../include/string_view.h"
#include "../include/user_input.h"
#include "../include/ip_calc.h"

// ncurses LIBRARIES
#include <ncurses.h>
#include <panel.h>


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

  for (int i = 0; i < pNumberAreas; i++)
  {
    int* numberHosts = calloc(5, sizeof(numberHosts));

    int* masc = calloc(2, sizeof(masc));
    char* mascPunteada = calloc(34, sizeof(mascPunteada));

    char* netAddrs = calloc(15, sizeof(netAddrs));
    char* broadcast = calloc(15, sizeof(broadcast));

    char* ipType = calloc(15, sizeof(ipType));

    char* fistIP = calloc(15, sizeof(fistIP));
    char* lastIP = calloc(15, sizeof(lastIP));

    askUserInput(numberHosts, "INGRESE CANTIDAD DE HOSTS (SUMANDO RED Y BROADCAST) (MAX 5 DIGITS)", "%5d");

    calcNetAdrrs(&pOctectUser, netAddrs);

    String_View sv_net_ip = sv(netAddrs);
    Octetcs pOctectNet = {0};

    arrayInput(&sv_net_ip, &pOctectNet);

    calcMasc(numberHosts, masc, mascPunteada);
    calcType(&pOctectUser, ipType);
    calcBroadcast(&pOctectNet, numberHosts, broadcast);

    String_View sv_broad_ip = sv(broadcast);
    Octetcs pOctectbroad = {0};

    arrayInput(&sv_broad_ip, &pOctectbroad);

    calcFistIP(&pOctectNet, fistIP);
    calcLastIP(&pOctectbroad, lastIP);

    // ResultIP resultado = {netAddrs, masc, broadcast, fistIP, lastIP};


    printf("RED:                           %s / %d\t\n", netAddrs, *masc);
    printf("MASCARA PUNTEADA:              %s\n", mascPunteada);
    printf("BROADCAST:                     %s \n", broadcast);
    printf("PRIMERA IP UTILIZABLE:         %s \n", fistIP);
    printf("ULTIMA IP UTILIZABLE:          %s \n", lastIP);
    printf("CANTIDAD DE HOSTS TOTALES:     %d \n", *numberHosts);
    printf("CANTIDAD DE HOSTS UTILIZABLES: %d \n", *numberHosts - 2);
    printf("TIPO DE IP:                    %s \n", ipType);
  }
  return EXIT_SUCCESS;
}
