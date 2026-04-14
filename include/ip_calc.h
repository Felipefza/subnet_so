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
void calcBroadcast (Octetcs* netAddrs, int* numberHosts, char* broadcast);
void calcMasc(int* NumberHosts, int* masc, char* mascPunteada);
void calcType (Octetcs* pOctectArray, char* ipType);
int calcFistIP (Octetcs* pOctectNet , char* fistIP);
int calcLastIP (Octetcs* pOctectBroad, char* lastIP);

#endif // !IP_CALC_H



