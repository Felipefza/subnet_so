#ifndef IP_CALC_H
#define IP_CALC_H

#include "string_view.h"

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

typedef struct {
  String_View* items;
  size_t count;
  size_t capacity;
} Octetcs;

int arrayInput(String_View* sv_user_ip, Octetcs* pOctectArray);
void calcNetAdrrs (Octetcs* pOctectArray, char* netAddrs);
int addIP (Octetcs* pOctectNet, int numberHosts, char* broadcast);
void calcMasc(int* NumberHosts, int* masc, char* mascPunteada);
void calcType (Octetcs* pOctectArray, char* ipType);
int subIP (Octetcs* pOctectBroad, char* lastIP, int addNumber);
void printResults (ResultIP* results, int* pNumberAreas);

#endif // !IP_CALC_H



