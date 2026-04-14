#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/user_input.h"


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
