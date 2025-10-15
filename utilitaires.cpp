#include "utilitaires.h"

t_EntierLong convStdToLong(const int *intStd)
{
  t_EntierLong intLong;

  intLong.negatif = (*intStd < 0) ? true : false;

  while (*intStd)
  {
    /* code */
  }
  return intLong;
}