#ifndef IP_CALC_H
#define IP_CALC_H

#include "user_input.h"

typedef struct {
  char* net;
  int masc;
  char* mascPunteada;
  char* broadcast;
  char* fistIP;
  char* lastIP;
  int numberHosts;
  char* ipType;
} ResultIP;

void calcNetAdrrs (Octetcs* pOctectArray, char* netAddrs);
void addIP (Octetcs* netAddrs, int numberHosts, char* broadcast);
void calcMasc(int* NumberHosts, int* masc, char* mascPunteada);
void calcType (Octetcs* pOctectArray, char* ipType);
int subIP (Octetcs* pOctectBroad, char* lastIP, int addNumber);
void printResults (ResultIP* results, int* pNumberAreas);

#endif // !IP_CALC_H



