#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// LOCAL FILES
#include "../include/string_view.h"
#include "../include/user_input.h"

// ncurses LIBRARIES
#include <ncurses.h>
#include <panel.h>
#include <string.h>

struct ResultIP {
  const char* net;
  const char* masc;
  const char* broadcast;
  const char* fistIP;
  const char* lastIP;
};

struct ResultIP calcSubnet(Octetcs* pOctectArray, int* pNumberhosts);

int main(int argc, char *argv[])
{
  char* pUserIP = calloc(15, sizeof(char));
  char* pMessage = "INGRESE LA IP EJ: '192.168.1.1', SEPARADO POR UN PUNTO (.)";

  askUserInput(pUserIP, pMessage, "%15s");

  String_View sv_user_ip = sv(pUserIP);

  Octetcs pOctectArray = {0};

  arrayInput(&sv_user_ip, &pOctectArray);

  for (int i = 0; i < pOctectArray.count; i++) printf("%.*s\n", (int)pOctectArray.items[i].count, pOctectArray.items[i].data);

  // Areas pNumberHosts = {0};

  int pNumberAreas;

  askUserInput(&pNumberAreas, "INGRESE CANTIDAD DE AREAS (MAX 2 DIGITS)", "%2d");

  printf("%d\n", pNumberAreas);

  int* pNumberHosts = calloc(1, sizeof(*pNumberHosts));

  for (int i = 0; i < pNumberAreas; i++)
  {
    askUserInput(pNumberHosts, "INGRESE CANTIDAD DE HOSTS (MAX 5 DIGITS)", "%5d");

    calcSubnet(&pOctectArray, pNumberHosts);
  }



  return EXIT_SUCCESS;
}

struct ResultIP calcSubnet(Octetcs* pOctectArray, int* pNumberhosts)
{
  for (int i = 3; i > -1; i--) {
    char* tmpString = calloc(4, sizeof(char));

    if (!strncmp(pOctectArray->items[i].data, "255", 3)) {
      tmpString = ".0";
      printf("%s\n", pOctectArray->items[i].data);
      printf("%s\n", tmpString);
    }

    strcat(tmpString, const char *)
  }
}
