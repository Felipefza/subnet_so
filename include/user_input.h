#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <string.h>
#include "string_view.h"

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

void askUserInput(void* pVar, char* pMessage, char* format);
void arrayInput(String_View* sv_user_ip, Octetcs* pOctectArray);

#endif // !USER_INPUT_H
