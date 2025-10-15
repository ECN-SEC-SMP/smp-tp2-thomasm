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

bool compAbs2long(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "compAbs2long : ";
  for (int i = 0; i < MAXCHIFFRES; i++)
  {
    if (longA->chiffres[i] > longB->chiffres[i])
    {
      afficheEntierLong(*longA);
      std::cout << " !<= ";
      afficheEntierLong(*longB);
      return false;
    }
  }
  afficheEntierLong(*longA);
  std::cout << " <= ";
  afficheEntierLong(*longB);
  return true;
}

u_int8_t *firstDigit(const t_EntierLong *intLong)
{
  u_int8_t *i = new u_int8_t(0);
  /* on recherche le 1er chiffre non nul (ou le chiffre des unites dans le cas d'un entier nul*/
  *i = MAXCHIFFRES - 1;
  while ((intLong->chiffres[*i] == 0) && (*i > 0))
  {
    *i = *i - 1;
  }
  return i;
}