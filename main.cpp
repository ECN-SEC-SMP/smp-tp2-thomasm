#include "entierlong.h"
#include "lit_ecrit.h"
#include "utilitaires.h"

int main(int argc, char **argv)
{
  bool egal = false;
  int *a = new int(1234567);
  t_EntierLong *b = new t_EntierLong({0, 0});
  t_EntierLong *c = new t_EntierLong({0, 555555});

  b = convStdToLong(a);
  egal = equal2long(b, c);
  egal = equal2long(c, c);
}