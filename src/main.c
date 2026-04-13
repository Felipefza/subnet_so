#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/string_view.h"

// ncurses LIBRARIES
#include <ncurses.h>
#include <panel.h>

typedef struct {
  String_View* items;
  size_t count;
  size_t capacity;
} Octetcs;

typedef struct {
  int* items;
  size_t count;
  size_t capacity;
} Areas;

void userInput(char* pVar, char* pMessage);
void arrayInput(String_View* sv_user_ip, Octetcs* pOctectArray);

int main(int argc, char *argv[])
{
  char* pUserIP = calloc(15, sizeof(char));
  char* pMessage = "INGRESE LA IP EJ: '192.168.1.1', SEPARADO POR UN PUNTO (.)";

  userInput(pUserIP, pMessage);

  String_View sv_user_ip = sv(pUserIP);

  Octetcs pOctectArray = {0};

  arrayInput(&sv_user_ip, &pOctectArray);

  for (int i = 0; i < pOctectArray.count; i++) printf("%.*s\n", (int)pOctectArray.items[i].count, pOctectArray.items[i].data);

  // Areas pNumberHosts = {0};

  return EXIT_SUCCESS;
}

void userInput(char* pVar, char* pMessage)
{
  if (pVar == NULL || pMessage == NULL)
  {
    printf("MEMORY ALLOCATION FAILED");
  }

  printf("\n%s", pMessage);
  printf("\n-> :");
  scanf("%15s", pVar);
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

  printf("FORMATO CORRECTO\n");
}
