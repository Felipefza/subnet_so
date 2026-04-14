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
  calcNetAdrrs(&pOctectUser, netAddrs);

  char* ipType = calloc(15, sizeof(ipType));
  calcType(&pOctectUser, ipType);

  for (int i = 0; i < pNumberAreas; i++)
  {
    int* numberHosts = calloc(5, sizeof(numberHosts));

    int* masc = calloc(2, sizeof(masc));
    char* mascPunteada = calloc(34, sizeof(mascPunteada));

    char* broadcast = calloc(15, sizeof(broadcast));


    char* fistIP = calloc(15, sizeof(fistIP));
    char* lastIP = calloc(15, sizeof(lastIP));

    Octetcs pOctectNet = {0};
    Octetcs pOctectbroad = {0};


    printf("\nAREA NUMERO %d\n", i + 1);
    askUserInput(numberHosts, "INGRESE CANTIDAD DE HOSTS (SUMANDO RED Y BROADCAST) (MAX 5 DIGITS)", "%5d");


    String_View sv_net_ip = sv(netAddrs);

    arrayInput(&sv_net_ip, &pOctectNet);

    calcMasc(numberHosts, masc, mascPunteada);
    calcBroadcast(&pOctectNet, numberHosts, broadcast);

    String_View sv_broad_ip = sv(broadcast);

    arrayInput(&sv_broad_ip, &pOctectbroad);

    calcFistIP(&pOctectNet, fistIP);
    calcLastIP(&pOctectbroad, lastIP);

    ResultIP resultadoIP = {strdup(netAddrs), *masc, strdup(mascPunteada), strdup(broadcast), strdup(fistIP), strdup(lastIP), *numberHosts, strdup(ipType)};
    resultados[i] = resultadoIP;


    sprintf(netAddrs, "%s", "");
    calcFistIP(&pOctectbroad, netAddrs);

    Octetcs pOctectNewNet = {0};

    String_View sv_new_ip = sv(netAddrs);
    printf("%s\n", netAddrs);

    arrayInput(&sv_new_ip, &pOctectNewNet);

    pOctectUser = pOctectNewNet;

    for (int j = 0; j < 4; j++) {
      printf("%s\n", pOctectUser.items[j].data);
    }
  }

  for (int i = 0; i < pNumberAreas; i++) {

    printf("\n=== SUBNET AREA NUMERO %d ===\n", i + 1);

    printf("RED:                           %s / %d\t\n", resultados[i].net, resultados[i].masc);
    printf("MASCARA PUNTEADA:              %s\n", resultados[i].mascPunteada);
    printf("BROADCAST:                     %s \n", resultados[i].broadcast);
    printf("PRIMERA IP UTILIZABLE:         %s \n", resultados[i].fistIP);
    printf("ULTIMA IP UTILIZABLE:          %s \n", resultados[i].lastIP);
    printf("CANTIDAD DE HOSTS TOTALES:     %d \n", resultados[i].numberHosts);
    printf("CANTIDAD DE HOSTS UTILIZABLES: %d \n", resultados[i].numberHosts - 2);
    printf("TIPO DE IP:                    %s \n", resultados[i].ipType);
  }
  return EXIT_SUCCESS;
}
