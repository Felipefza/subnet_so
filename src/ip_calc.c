#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// LOCAL FILES
#include "../include/string_view.h"
#include "../include/user_input.h"



void calcType (Octetcs* pOctectArray, char* ipType)
{
  int fistOctect = atoi(pOctectArray->items[0].data);
  if (fistOctect == 10) {
    sprintf(ipType, "%s", "PRIVATO TIPO A");
  }
  else if (fistOctect ==  172) {
    sprintf(ipType, "%s", "PRIVATO TIPO B");

  } 
  else if (fistOctect == 192) {
    sprintf(ipType, "%s", "PRIVATO TIPO C");
  }
  else {
    sprintf(ipType,"%s", "PUBLICO");
  }
}

void calcNetAdrrs (Octetcs* pOctectArray, char* netAddrs)
{
  int i = 0;
  int power = 0;

  bool isRunning = true;

  while (isRunning) {
    power = pow(2, i);

    if (power > atoi(pOctectArray->items[3].data)) {
      i--;
      isRunning = false;
    } else {
      i++;
    }
  }

  for (int number = 0; number < 3; number++) {
    strncat(netAddrs, pOctectArray->items[number].data, pOctectArray->items[number].count + 1);
  }

  char* buffer = calloc(5, sizeof(char));

  power = pow(2, i);

  if (power == 1) power = 0;

  sprintf(buffer, "%d", power);
  strncat(netAddrs, buffer, 5);
}

void calcMasc(int* NumberHosts, int* masc, char* mascPunteada)
{
  int i = 0;
  int hosts;

  bool isRunning = true;

  while (isRunning) {

    hosts = pow(2, i);

    if (hosts > *NumberHosts) {
      *masc = 32 - i;

      int k = 1;

      for (int j = 0; j < *masc; j++) {
        strcat(mascPunteada, "1");
        if (k % 8 == 0) {
          strcat(mascPunteada, ".");
        }
        k++;
      }

      for (int j = 0; j < i; j++) {
        strcat(mascPunteada, "0");
        if (k % 8 == 0 && k != 32) {
          strcat(mascPunteada, ".");
        }
        k++;
      }

      for (int j = 0; j < 25; j++) {
      }

      isRunning = false;
    }

    i++;
  }
}

void addIP (Octetcs* pOctectNet, int numberHosts, char* broadcast)
{
  bool isRunning = true;
  int hosts = numberHosts;
  int i = 3;
  char* buffer = calloc(15, sizeof(char));
  int sum = hosts += atoi(pOctectNet->items[i].data);

  while (isRunning && i > -1) {
    int dec = sum / 255;
    int inv = sum % 255;

    if (dec == 0) {
      if (i == 3) {
        sprintf(buffer, "%d", inv);
      } else {
        sprintf(buffer, "%d.", inv);
      }
      strcat(buffer, broadcast);
      sprintf(broadcast, "%s", buffer);
    }

    if (dec > 0) {
      if (i == 3) {
        sprintf(buffer, "%d", inv);
      } else {
        sprintf(buffer, "%d.", inv);
      }
      strcat(buffer, broadcast);
      sprintf(broadcast, "%s", buffer);
    }

    i--;

    if (i > -1) {
      sum = dec + atoi(pOctectNet->items[i].data);
    }
  }
}

int subIP (Octetcs* pOctectBroad, char* outIP, int subNumber) {
  char* buffer = calloc(15, sizeof(buffer));
  int sum;
  int i = 3;
  bool isRunning = true;

  while (i > -1 && isRunning) {
    sum = atoi(pOctectBroad->items[i].data) - subNumber;
    if (sum < 0) {
      if (i == 0 ) {
        printf("IP RANGO MINIMO");
        return EXIT_FAILURE;
      };

      if (i == 3) {
        sprintf(buffer, "%s", "255");
      } else {
        sprintf(buffer, "%s.", "255");
      }
      strcat(buffer, outIP);
      sprintf(outIP, "%s", buffer);
      i--;
    } else {
      if (i == 3) {
        sprintf(buffer, "%d", sum);
      } else {
        sprintf(buffer, "%d.", sum);
      }
      strcat(buffer, outIP);
      sprintf(outIP, "%s", buffer);
      sprintf(buffer, "%s", "");
      i--;
      isRunning = false;
    }
  }
  while (i > -1) {
    sprintf(buffer,  "%.*s.",(int)pOctectBroad->items[i].count, pOctectBroad->items[i].data);
    strcat(buffer, outIP);
    sprintf(outIP, "%s", buffer);
    i--;
  }
  return EXIT_SUCCESS;
}
