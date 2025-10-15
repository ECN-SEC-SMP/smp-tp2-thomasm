#include "entierlong.h"
#include "lit_ecrit.h"
#include "utilitaires.h"
#include "operations.h"

int main(int argc, char **argv)
{
  bool egal = false;
  int *a = new int(1234567);
  t_EntierLong *b = new t_EntierLong{false, {0}};
  t_EntierLong *c = new t_EntierLong{false, {5, 5, 5, 5, 5, 5}};
  t_EntierLong *d = new t_EntierLong{true, {4, 4, 4, 4, 4, 4}};
  t_EntierLong *e = new t_EntierLong{true, {6, 6, 6, 6, 6, 6}};
  t_EntierLong *f = new t_EntierLong{false, {0}};

  b = convStdToLong(a);

  egal = equal2long(b, c);
  egal = equal2long(c, c);

  egal = compAbs2long(b, c);
  egal = compAbs2long(c, c);
  egal = compAbs2long(d, c);
  egal = compAbs2long(e, c);

  f = addSameSign(b, c);
  afficheEntierLong(*f);
}