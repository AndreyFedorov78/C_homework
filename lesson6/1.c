#include <stdio.h>
#include <stdint.h>

uint64_t getHash(char const *s) {
  const int p = 31;
  uint64_t hash = 0,
  p_pow = 1;
  while(*s) {
    hash += (*s++ - 'a' + 1) * p_pow;
    p_pow *= p;
  }
  return hash;
}

_Bool checkPass(char *p) {
  if(getHash(p) == 577739920) return 1;
  return 0;
}

int main(void) {
  char password[100]; printf("Input your password: ");
  scanf("%s",password);
  if(checkPass(password)) printf("Access granted\n");
  else printf("Access denied\n");
  return 0;
}
