#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "stringutil.h"


char *
dupstr(const char *s, const char *e) {
  int l = e ? e-s : strlen(s);
  char *ss = (char*)malloc(l+1);
  memcpy(ss, s, l);
  ss[l] = 0;
  return ss;
}



int stringlen(const char* s1) {
  if (s1 == NULL) {
    return 0;
  } else {
    return strlen(s1);
  }
}


int stringlen(const char* s1, const char* s2, const char* s3, const char* s4,
              const char* s5) {
  return stringlen(s1) + stringlen(s2) + stringlen(s3) + stringlen(s4) + 
    stringlen(s5);
}


char* stringcpy(const char* s1) {
  char* s = (char*)malloc(stringlen(s1) + 1);
  strcpy(s, s1);
  return s;
}


char* stringcat(const char* s1, const char* s2, const char* s3, const char* s4,
                const char* s5) {
  char* s = (char*)malloc(stringlen(s1, s2, s3, s4, s5) + 1);
  sprintf(s, "%s%s%s%s%s", s1, s2, s3, s4, s5);
  return s;
}


char* stringinsert(const char* sorig, const char* pos, const char* insertme) {
  return stringcat(dupstr(sorig, pos), insertme, dupstr(pos+1));
}


char* intstring(int i) {
  char buf[64];
  if (sprintf(buf, "%d", i) > 63)
    INT_FATAL("intstring() buffer overflow");
  return stringcpy(buf);
}
