#include "utilitaires.h" // pour convStdToLong(), equal2long(), compAbs2long()
#include "operations.h"  // pour addSameSign(), subSameSign(), addAnySign(), subAnySign()

int main(int argc, char **argv)
{
  int *a_pos = new int(1234567);
  int *a_zero = new int(0);

  t_EntierLong *b = new t_EntierLong{false, {0}};                // recevra convStdToLong(a_pos)
  t_EntierLong *z = new t_EntierLong{false, {0}};                // zéro
  t_EntierLong *c = new t_EntierLong{false, {5, 5, 5, 5, 5, 5}}; // +555555
  t_EntierLong *d = new t_EntierLong{true, {4, 4, 4, 4, 4, 4}};  // -444444
  t_EntierLong *e = new t_EntierLong{true, {6, 6, 6, 6, 6, 6}};  // -666666
  t_EntierLong *u = new t_EntierLong{false, {1}};                // +1
  t_EntierLong *nine = new t_EntierLong{false, {0}};             // +999...9
  for (int i = 0; i < MAXCHIFFRES; ++i)
    nine->chiffres[i] = 9;

  t_EntierLong *tmp = nullptr; // tampon de resultats

  // --------- conversion ----------
  std::cout << "\n=== Conversion ===\n";
  b = convStdToLong(a_pos);                 // b = +1234567
  t_EntierLong *b0 = convStdToLong(a_zero); // test zero via conv

  // --------- egalite ----------
  std::cout << "\n=== Egalite ===\n";
  equal2long(b, c);
  equal2long(c, c);
  equal2long(z, b0);
  equal2long(d, e);

  // --------- comparaison absolue (|A| <= |B|) ----------
  std::cout << "\n=== Comparaison absolue (|A| <= |B|) ===\n";
  compAbs2long(b, c);
  compAbs2long(c, c);
  compAbs2long(d, c);
  compAbs2long(e, c);
  compAbs2long(z, c);

  // --------- addition même signe ----------
  std::cout << "\n=== addSameSign (meme signe) ===\n";
  tmp = addSameSign(b, c);
  delete tmp;
  tmp = addSameSign(d, e);
  delete tmp;
  tmp = addSameSign(z, z);
  delete tmp;
  tmp = addSameSign(nine, u);
  delete tmp;

  std::cout << "\n=== addSameSign (signes differents) ===\n";
  tmp = addSameSign(b, d);
  delete tmp;
  tmp = addSameSign(e, c);
  delete tmp;

  // --------- soustraction meme signe ----------
  std::cout << "\n=== subSameSign (meme signe, |A|>=|B|) ===\n";
  tmp = subSameSign(c, u);
  delete tmp; // emprunts en chaine
  tmp = subSameSign(c, c);
  delete tmp; // zero
  tmp = subSameSign(e, d);
  delete tmp; // negatif - negatif

  std::cout << "\n=== subSameSign (hors-contrat) ===\n";
  tmp = subSameSign(b, d);
  delete tmp; // signes differents
  tmp = subSameSign(u, c);
  delete tmp; // |A|<|B|

  // --------- addition signes quelconques ----------
  std::cout << "\n=== addAnySign (signes quelconques) ===\n";
  tmp = addAnySign(b, d);
  delete tmp; // +1234567 + (-444444)
  tmp = addAnySign(e, c);
  delete tmp; // -666666 + 555555
  tmp = addAnySign(z, d);
  delete tmp; // 0 + (-444444)
  tmp = addAnySign(d, z);
  delete tmp; // -444444 + 0
  tmp = addAnySign(c, b);
  delete tmp; //
  tmp = addAnySign(b, c);
  delete tmp; // test de commutativité

  // --------- soustraction signes quelconques ----------
  std::cout << "\n=== subAnySign (signes quelconques) ===\n";
  tmp = subAnySign(b, d);
  delete tmp; // +A - (-B) -> addition d'absolus
  tmp = subAnySign(d, b);
  delete tmp; // -A - (+B) -> negatif
  tmp = subAnySign(c, e);
  delete tmp; // +C - (-E) -> addition d'absolus
  tmp = subAnySign(z, c);
  delete tmp; // 0 - (+C) -> -C
  tmp = subAnySign(c, z);
  delete tmp; // +C - 0 -> +C
  tmp = subAnySign(b, b);
  delete tmp; // A - A -> 0

  // --------- libération ----------
  delete a_pos;
  delete a_zero;
  delete b;
  delete b0;
  delete c;
  delete d;
  delete e;
  delete z;
  delete u;
  delete nine;

  return EXIT_SUCCESS;
}