#include "operations.h"

t_EntierLong *addSameSign(const t_EntierLong *longA, const t_EntierLong *longB)
{
  t_EntierLong *res = new t_EntierLong({0, 0});
  if (longA->negatif != longB->negatif) // vérifie s'ils sont de même signes
    return res;

  bool carry = false;

  for (u_int8_t i = 0; i < MAXCHIFFRES; i++)
  {
    std::cout << longA->chiffres[i] << " + " << longB->chiffres[i] << (carry ? " + r" : "    ");
    res->chiffres[i] = (longA->chiffres[i] + longB->chiffres[i] + (carry ? 1 : 0)) % 10;
    std::cout << " = " << res->chiffres[i] << std::endl;
    if ((!(res->chiffres[i])) && !carry)
      break;
    // à la fin
    carry = ((longA->chiffres[i] + longB->chiffres[i]) < 10) ? false : true;
  }
  return res;
}