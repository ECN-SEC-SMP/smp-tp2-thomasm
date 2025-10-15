#include "utilitaires.h"
#include "lit_ecrit.h"

t_EntierLong *convStdToLong(const int *intStd)
{
  t_EntierLong *intLong = new t_EntierLong({0, 0});
  int intStdEditable = *intStd;
  int nbChiffre = 0;

  intLong->negatif = (*intStd < 0) ? true : false; // check if int est négatif ou positif
  std::cout << "convStdToLong : " << *intStd << " => " << (intLong->negatif ? "-" : "+");
  do
  {
    if (nbChiffre > MAXCHIFFRES)
    {
      std::cout << " Nombre trop grand !" << std::endl;
      break;
    }
    intLong->chiffres[nbChiffre] = intStdEditable % 10;
    nbChiffre++;
  } while ((intStdEditable /= 10) > 0);
  afficheEntierLong(*intLong);
  std::cout << " (" << nbChiffre << " chiffres)" << std::endl;
  return intLong;
}

bool equal2long(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "equal2long : ";
  for (int i = 0; i < MAXCHIFFRES; i++)
  {
    if (longA->chiffres[i] != longB->chiffres[i])
    {
      afficheEntierLong(*longA);
      std::cout << " != ";
      afficheEntierLong(*longB);
      return false;
    }
  }
  afficheEntierLong(*longA);
  std::cout << " == ";
  afficheEntierLong(*longB);
  return true;
}