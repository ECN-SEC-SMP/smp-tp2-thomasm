#include "utilitaires.h"

t_EntierLong convStdToLong(const int *intStd)
{
  t_EntierLong intLong = {0, 0};
  int intStdEditable = *intStd;
  int nbChiffre = 0;

  intLong.negatif = (*intStd < 0) ? true : false; // check if int est négatif ou positif
  std::cout << "convStdToLong : " << *intStd << " => " << (intLong.negatif ? "-" : "+");
  do
  {
    if (nbChiffre > MAXCHIFFRES)
    {
      std::cout << " Nombre trop grand !" << std::endl;
      break;
    }
    intLong.chiffres[nbChiffre] = intStdEditable % 10;
    nbChiffre++;
  } while ((intStdEditable /= 10) > 0);

  for (int i = nbChiffre - 1; i >= 0; i--)
  {
    std::cout << intLong.chiffres[i];
  }

  std::cout << " (" << nbChiffre << " chiffres)" << std::endl;

  return intLong;
}