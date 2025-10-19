#pragma once
#include "entierlong.h" // pour t_EntierLong
#include "lit_ecrit.h"  // pour afficherEntierLong()
#include <iostream>     //pour cout et cin

/**
 * Conversion d'un entier standard en entier long
 * @param intStd : pointeur vers l'entier standard à convertir
 * @return : pointeur vers l'entier long résultant (alloué dynamiquement
 */
t_EntierLong *convStdToLong(const int *intStd);

/**
 * Test d'égalité de deux entiers longs
 * @param longA : pointeur vers le premier entier long
 * @param longB : pointeur vers le second entier long
 * @return : true si égaux, false sinon
 */
bool equal2long(const t_EntierLong *longA, const t_EntierLong *longB);

/**
 * Comparaison absolue de deux entiers longs
 * @param longA : pointeur vers le premier entier long
 * @param longB : pointeur vers le second entier long
 * @return : true si |A| <= |B|, false sinon
 */
bool compAbs2long(const t_EntierLong *longA, const t_EntierLong *longB);

/**
 * Recherche de la position du premier chiffre non nul dans un entier long
 * @param intLong : pointeur vers l'entier long
 * @return : pointeur vers la position du premier chiffre non nul (alloué dynamiquement)
 */
u_int8_t *firstDigit(const t_EntierLong *intLong);