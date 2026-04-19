#include "../include/string_view.h"

#include <ctype.h>
#include <stdbool.h>

String_View sv(const char* cstr)
{
 return (String_View)
  {
    .data = cstr,
    .count = strlen(cstr),
  };
}

void sv_chop_right(String_View* sv, size_t n)
{
  if (n > sv->count) n = sv->count;
  sv->count -= n;
}

void sv_chop_left(String_View* sv, size_t n)
{
  if (n > sv->count) n = sv->count;
  sv->count -= n;
  sv->data += n;
}

void sv_trim_right(String_View* sv)
{
  while (sv->count > 0 && isspace(sv->data[sv->count - 1]))
  {
    sv_chop_right(sv, 1);
  }
}

void sv_trim_left(String_View* sv)
{
  while (sv->count > 0 && isspace(sv->data[0]))
  {
    sv_chop_left(sv, 1);
  }
}

void sv_trim(String_View* sv)
{
  sv_trim_right(sv);
  sv_trim_left(sv);
}

String_View chop_by_delim(String_View* sv, char delim)
{
  size_t i = 0;
  while (i < sv->count && sv->data[i] != delim) 
  {
    i++;
  }

  if (i < sv->count) 
  {
    String_View result = {
      .data = sv->data,
      .count = i,
    };
    sv_chop_left(sv, i + 1);
    return result;
  }

  String_View result = *sv;
  sv_chop_left(sv, sv->count);
  return result;
}

bool isValidNumber(char* string)
{
  if (*string == '\0') return false;
  if (*string == '-') return false;

  while (*string) {
    if (isdigit(*string)) {
      return false;
    }
    string++;
  }
  return true;
}

int minTwoNumbers(int* a, int* b)
{
  if (*a < *b) return *a;

  return *b;
}
