#include "utilitaires.h"

t_EntierLong *convStdToLong(const int *intStd)
{
  t_EntierLong *intLong = new t_EntierLong({0, 0});
  int intStdEditable = *intStd;
  int nbChiffre = 0;

  intLong->negatif = (*intStd < 0) ? true : false; // check if int est négatif ou positif
  std::cout << "convStdToLong : " << *intStd << " => " << (intLong->negatif ? "-" : "+");
  do
  {
    if (nbChiffre > MAXCHIFFRES) // overflow
    {
      std::cout << " Nombre trop grand !" << std::endl;
      break;
    }
    intLong->chiffres[nbChiffre] = intStdEditable % 10; // extraire chiffre des unités
    nbChiffre++;                                        // incrémenter le nombre de chiffres
  } while ((intStdEditable /= 10) > 0); // diviser par 10 pour passer au chiffre suivant
  afficheEntierLong(*intLong);
  std::cout << " (" << nbChiffre << " chiffre" << ((nbChiffre >= 2) ? "s)" : ")") << std::endl;
  return intLong;
}

bool equal2long(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "equal2long : ";
  for (int i = 0; i < MAXCHIFFRES; i++) // comparer chiffre par chiffre
  {
    if (longA->chiffres[i] != longB->chiffres[i]) // differents
    {
      afficheEntierLong(*longA);
      std::cout << " != ";
      afficheEntierLong(*longB);
      return false; // differents
    }
  }
  afficheEntierLong(*longA);
  std::cout << " == ";
  afficheEntierLong(*longB);
  return true; // égaux
}

bool compAbs2long(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "compAbs2long : ";
  for (int i = 0; i < MAXCHIFFRES; i++) // comparer chiffre par chiffre
  {
    if (longA->chiffres[i] > longB->chiffres[i]) // A > B
    {
      afficheEntierLong(*longA);
      std::cout << " !<= ";
      afficheEntierLong(*longB);
      return false; // A > B
    }
  }
  afficheEntierLong(*longA);
  std::cout << " <= ";
  afficheEntierLong(*longB);
  return true; // A <= B
}

u_int8_t *firstDigit(const t_EntierLong *intLong)
{
  u_int8_t *i = new u_int8_t(0);
  /* on recherche le 1er chiffre non nul (ou le chiffre des unites dans le cas d'un entier nul*/
  *i = MAXCHIFFRES - 1;                            // position du chiffre des unités
  while ((intLong->chiffres[*i] == 0) && (*i > 0)) // tant que chiffre nul et pas au bout
  {
    *i = *i - 1; // reculer d'une position
  }
  return i; // retourner la position du 1er chiffre
}