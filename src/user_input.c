#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LOCAL FILES
#include "../include/user_input.h"
#include "../include/ip_calc.h"


void askUserInput(void* pVar, char* pMessage, char* format)
{
  if (pVar == NULL || pMessage == NULL)
  {
    printf("MEMORY ALLOCATION FAILED");
  }

  printf("%s", pMessage);
  printf("\n-> :");
  scanf(format, pVar);
}

void arrayInput(String_View* sv_user_ip, Octetcs* pOctectArray)
{
  for (int i = 0; i < 4; i++) {
    if (pOctectArray->count >= pOctectArray->capacity) {
      if (pOctectArray->capacity == 0) pOctectArray->capacity = 256;
      else pOctectArray->capacity *= 2;
      pOctectArray->items = realloc(pOctectArray->items, pOctectArray->capacity * sizeof(*pOctectArray->items));
    }

    pOctectArray->items[pOctectArray->count++] = chop_by_delim(sv_user_ip, '.');

    if (pOctectArray->items[i].count == 0 || pOctectArray->items[i].count > 3) {
      printf("FORMATO INCORRECTO\n");
      return;
    }
  }
}

void printResults (ResultIP* results, int* pNumberAreas) {
  for (int i = 0; i < *pNumberAreas; i++) {

    printf("\n=== SUBNET AREA NUMERO %d ===\n", i + 1);

    printf("MASCARA PUNTEADA:              %s\n", results[i].mascPunteada);
    printf("RED:                           %s / %d\t\n", results[i].net, results[i].masc);
    printf("PRIMERA IP UTILIZABLE:         %s \n", results[i].fistIP);
    printf("ULTIMA IP UTILIZABLE:          %s \n", results[i].lastIP);
    printf("BROADCAST:                     %s \n", results[i].broadcast);
    printf("CANTIDAD DE HOSTS TOTALES:     %d \n", results[i].numberHosts);
    printf("CANTIDAD DE HOSTS UTILIZABLES: %d \n", results[i].numberHosts - 2);
    printf("TIPO DE IP:                    %s \n", results[i].ipType);
  }
}
