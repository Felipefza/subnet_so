#ifndef IP_CALC_H
#define IP_CALC_H

typedef struct {
  const char* net;
  const char* masc;
  const char* broadcast;
  const char* fistIP;
  const char* lastIP;
} ResultIP;


void calcNetAdrrs (Octetcs* pOctectArray, char* netAddrs);
void calcBroadcast (Octetcs* netAddrs, int* numberHosts, char* broadcast);
void calcMasc(int* NumberHosts, int* masc, char* mascPunteada);
void calcType (Octetcs* pOctectArray, char* ipType);

#endif // !IP_CALC_H



