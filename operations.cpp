#include "operations.h"

t_EntierLong *addSameSign(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "addSameSign : " << std::endl;
  t_EntierLong *res = new t_EntierLong({0, 0});
  if (longA->negatif != longB->negatif) // vérifie s'ils sont de même signes
    return res;

  bool carry = false;

  for (u_int8_t i = 0; i < MAXCHIFFRES; i++)
  {
    std::cout << longA->chiffres[i] << " + " << longB->chiffres[i] << (carry ? " + c" : "    ");
    res->chiffres[i] = (longA->chiffres[i] + longB->chiffres[i] + (carry ? 1 : 0)) % 10;
    std::cout << " = " << res->chiffres[i] << std::endl;
    if ((!(res->chiffres[i])) && !carry)
      break;
    // à la fin
    carry = ((longA->chiffres[i] + longB->chiffres[i]) < 10) ? false : true;
  }
  std::cout << "= ";
  afficheEntierLong(*res);
  return res;
}

t_EntierLong *subSameSign(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "subSameSign : " << std::endl;
  t_EntierLong *res = new t_EntierLong({0, 0});
  if ((longA->negatif != longB->negatif) && (!(compAbs2long(longA, longB)) || equal2long(longA, longB))) // vérifie s'ils sont de même signes, et que n1 >= n2
    return res;

  bool borrow = false;

  for (u_int8_t i = 0; i < MAXCHIFFRES; i++)
  {
    std::cout << longA->chiffres[i] << " - " << longB->chiffres[i] << (borrow ? " - b" : "    ");
    res->chiffres[i] = (longA->chiffres[i] - longB->chiffres[i] - (borrow ? 1 : 0));
    if (res->chiffres[i] < 0)
    {
      res->chiffres[i] += 10;
      borrow = true;
    }
    else
      borrow = false;
    std::cout << " = " << res->chiffres[i] << std::endl;
    if ((!(res->chiffres[i])) && !borrow)
      break;
  }
  std::cout << "= ";
  afficheEntierLong(*res);
  return res;
}