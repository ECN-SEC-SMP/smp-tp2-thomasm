#include "entierlong.h"
#include "lit_ecrit.h"
#include "utilitaires.h"

int main(int argc, char **argv)
{
  int *a = new int(1234567);
  t_EntierLong b = {0, 0};
  b = convStdToLong(a);
}