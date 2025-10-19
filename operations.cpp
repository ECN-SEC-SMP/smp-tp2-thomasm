#include "operations.h"

t_EntierLong *addSameSign(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "addSameSign :" << std::endl;

  t_EntierLong *res = new t_EntierLong({0, 0});
  if (longA->negatif != longB->negatif) // si signes differents
  {
    std::cout << "  -> Signes differents : addition impossible" << std::endl;
    return res; // retourne zero
  }

  res->negatif = longA->negatif; // résultat signe = signe des operandes
  std::cout << "  -> Signe resultat : " << (res->negatif ? "-" : "+") << std::endl;

  // détermination du chiffre max significatif
  u_int8_t *pa = firstDigit(longA);
  u_int8_t *pb = firstDigit(longB);
  u_int8_t imax = (*pa > *pb) ? *pa : *pb; // max entre les deux
  std::cout << "  -> Chiffres utiles jusqu’à " << (int)imax << std::endl;
  delete pa;
  delete pb;

  int carry = 0;
  for (u_int8_t i = 0; i <= imax; ++i) // pour chaque chiffre utile
  {
    int a = longA->chiffres[i];
    int b = longB->chiffres[i];
    int sum = a + b + carry; // somme

    std::cout << "  [" << (int)i << "] " << a << " + " << b << (carry ? " +1" : "   ") << " = " << sum;

    res->chiffres[i] = sum % 10; // chiffre resultat
    carry = sum / 10;            // nouveau carry

    std::cout << " -> chiffre=" << res->chiffres[i] << " carry=" << carry << std::endl;
  }

  if (carry && (imax + 1 < MAXCHIFFRES)) // propagation du carry final si possible
  {
    res->chiffres[imax + 1] = carry;
    std::cout << "  -> Report final propagé à [" << (int)(imax + 1) << "] = " << carry << std::endl;
  }
  else if (carry) // carry perdu
  {
    std::cout << "  -> ATTENTION : dépassement de capacité (carry perdu)" << std::endl;
  }

  std::cout << "  => Résultat final : ";
  afficheEntierLong(*res);
  std::cout << std::endl;

  return res; // retourne résultat
}

t_EntierLong *subSameSign(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "subSameSign :" << std::endl;

  t_EntierLong *res = new t_EntierLong({0, 0});
  if (longA->negatif != longB->negatif) // signes differents
  {
    std::cout << "  -> Signes differents : soustraction impossible" << std::endl;
    return res; // retourne zero
  }

  if (compAbs2long(longA, longB) && !equal2long(longA, longB)) // |A| < |B|
  {
    std::cout << "  -> |A| < |B| : soustraction impossible" << std::endl;
    return res; // retourne zero
  }

  res->negatif = longA->negatif; // résultat signe = signe des operandes
  std::cout << "  -> Signe resultat : " << (res->negatif ? "-" : "+") << std::endl;

  // détermination du chiffre max significatif
  u_int8_t *pa = firstDigit(longA);
  u_int8_t *pb = firstDigit(longB);
  u_int8_t imax = (*pa > *pb) ? *pa : *pb; // max entre les deux
  std::cout << "  -> Chiffres utiles jusqu’à " << (int)imax << std::endl;
  delete pa;
  delete pb;

  int borrow = 0;
  for (u_int8_t i = 0; i <= imax; ++i) // pour chaque chiffre utile
  {
    int a = longA->chiffres[i];
    int b = longB->chiffres[i];
    int diff = a - b - borrow; // soustraction

    std::cout << "  [" << (int)i << "] " << a << " - " << b << (borrow ? " -1" : "   ") << " = " << diff;

    if (diff < 0) // borrow nécessaire
    {
      diff += 10;
      borrow = 1;
      std::cout << " -> +10 = " << diff << " borrow" << std::endl;
    }
    else
    {
      borrow = 0;
      std::cout << " -> OK (pas de borrow)" << std::endl;
    }

    res->chiffres[i] = diff;
  }

  if (borrow)
    std::cout << "  -> ATTENTION : dépassement de capacité (borrow perdu)" << std::endl;

  // normalisation signe si résultat nul
  u_int8_t *pr = firstDigit(res);
  bool isZero = (res->chiffres[*pr] == 0);
  delete pr;
  if (isZero)
  {
    res->negatif = false;
    std::cout << "  -> Résultat nul, signe forcé à +" << std::endl;
  }

  std::cout << "  => Résultat final : ";
  afficheEntierLong(*res);
  std::cout << std::endl;

  return res;
}

t_EntierLong *addAnySign(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "addAnySign :" << std::endl;

  if (longA->negatif == longB->negatif) // signes identiques
  {
    std::cout << "  -> Signes identiques : delegation a addSameSign" << std::endl;
    t_EntierLong *r = addSameSign(longA, longB);
    return r;
  }

  // signes differents -> |A| - |B| avec signe du plus grand en valeur absolue
  std::cout << "  -> Signes differents : reduction a soustraction d'absolus" << std::endl;

  // construire des copies "absolues" positives pour la soustraction
  t_EntierLong *Apos = new t_EntierLong{false, {0}};
  t_EntierLong *Bpos = new t_EntierLong{false, {0}};
  for (int i = 0; i < MAXCHIFFRES; ++i)
  {
    Apos->chiffres[i] = longA->chiffres[i];
    Bpos->chiffres[i] = longB->chiffres[i];
  }

  // comparer |A| et |B|
  bool AleB = compAbs2long(longA, longB); // |A| <= |B|
  bool AeqB = equal2long(longA, longB);   // |A| == |B|

  t_EntierLong *res = nullptr;

  if (AeqB) // |A| == |B|
  {
    std::cout << "  -> |A| == |B| : somme nulle" << std::endl;
    res = new t_EntierLong({0, 0});
  }
  else if (!AleB) // |A| > |B|
  {
    std::cout << "  -> |A| > |B| : calcul (|A|-|B|), signe = signe(A)" << std::endl;
    res = subSameSign(Apos, Bpos); // Apos >= Bpos garanti par le test
    // forcer le signe = signe(A) sauf si res == 0
    u_int8_t *p = firstDigit(res);
    bool zero = (res->chiffres[*p] == 0);
    delete p;
    res->negatif = zero ? false : longA->negatif;
  }
  else // |A| < |B|
  {
    std::cout << "  -> |A| < |B| : calcul (|B|-|A|), signe = signe(B)" << std::endl;
    res = subSameSign(Bpos, Apos);
    u_int8_t *p = firstDigit(res);
    bool zero = (res->chiffres[*p] == 0);
    delete p;
    res->negatif = zero ? false : longB->negatif;
  }

  delete Apos;
  delete Bpos;

  std::cout << "  => Resultat : ";
  afficheEntierLong(*res);
  std::cout << std::endl;
  return res;
}

t_EntierLong *subAnySign(const t_EntierLong *longA, const t_EntierLong *longB)
{
  std::cout << "subAnySign :" << std::endl;

  // cas signes differents : A - (-B) = A + |B|  et  (-A) - B = -( |A| + |B| )
  if (longA->negatif != longB->negatif) // signes differents
  {
    std::cout << "  -> Signes differents : reduction a addition d'absolus" << std::endl;

    // Construire copies avec signe = signe(A) pour pouvoir utiliser addSameSign
    t_EntierLong *Ac = new t_EntierLong{longA->negatif, {0}};
    t_EntierLong *Bc = new t_EntierLong{longA->negatif, {0}}; // donner le meme signe a B
    for (int i = 0; i < MAXCHIFFRES; ++i)
    {
      Ac->chiffres[i] = longA->chiffres[i];
      Bc->chiffres[i] = longB->chiffres[i];
    }

    t_EntierLong *res = addSameSign(Ac, Bc);

    delete Ac;
    delete Bc;

    std::cout << "  => Resultat : ";
    afficheEntierLong(*res);
    std::cout << std::endl;
    return res;
  }

  // signes identiques
  // (+A) - (+B) : signe selon comparaison |A| ? |B|
  // (-A) - (-B) : -( |A| - |B| )
  std::cout << "  -> Signes identiques : reduction a soustraction d'absolus" << std::endl;

  // construire des copies "absolues" positives pour la soustraction
  t_EntierLong *Apos = new t_EntierLong{false, {0}};
  t_EntierLong *Bpos = new t_EntierLong{false, {0}};
  for (int i = 0; i < MAXCHIFFRES; ++i)
  {
    Apos->chiffres[i] = longA->chiffres[i];
    Bpos->chiffres[i] = longB->chiffres[i];
  }

  bool AleB = compAbs2long(longA, longB); // |A| <= |B|
  bool AeqB = equal2long(longA, longB);   // |A| == |B|

  t_EntierLong *res = nullptr;

  if (AeqB) // |A| == |B|
  {
    std::cout << "  -> |A| == |B| : difference nulle" << std::endl;
    res = new t_EntierLong({0, 0});
  }
  else if (!AleB) // |A| > |B|
  {
    std::cout << "  -> |A| > |B| : calcul (|A|-|B|)" << std::endl;
    res = subSameSign(Apos, Bpos); // (|A|>=|B|) respecte le contrat
    // Signe :
    //  (+A)-(+B) -> +
    //  (-A)-(-B) -> -
    u_int8_t *p = firstDigit(res);
    bool zero = (res->chiffres[*p] == 0);
    delete p;
    res->negatif = zero ? false : longA->negatif;
  }
  else // |A| < |B|
  {
    std::cout << "  -> |A| < |B| : calcul (|B|-|A|)" << std::endl;
    res = subSameSign(Bpos, Apos);
    // signe inversé
    //  (+A)-(+B) -> -
    //  (-A)-(-B) -> +
    u_int8_t *p = firstDigit(res);
    bool zero = (res->chiffres[*p] == 0);
    delete p;
    res->negatif = zero ? false : !longA->negatif;
  }

  delete Apos;
  delete Bpos;

  std::cout << "  => Resultat : ";
  afficheEntierLong(*res);
  std::cout << std::endl;
  return res;
}