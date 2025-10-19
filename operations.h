#pragma once
#include "entierlong.h"  // pour t_EntierLong
#include "lit_ecrit.h"   // pour afficherEntierLong()
#include "utilitaires.h" // pour firstDigit()
#include <iostream>      //pour cout et cin

/**
 * addition de deux entiers longs de même signe
 * @param longA : premier entier long
 * @param longB : second entier long
 * @return : pointeur vers le résultat (alloué dynamiquement)
 */
t_EntierLong *addSameSign(const t_EntierLong *longA, const t_EntierLong *longB);

/**
 * soustraction de deux entiers longs de même signe
 * @param longA : premier entier long
 * @param longB : second entier long
 * @return : pointeur vers le résultat (alloué dynamiquement)
 */
t_EntierLong *subSameSign(const t_EntierLong *longA, const t_EntierLong *longB);

/**
 * addition de deux entiers longs de signes quelconques
 * @param longA : premier entier long
 * @param longB : second entier long
 * @return : pointeur vers le résultat (alloué dynamiquement)
 */
t_EntierLong *addAnySign(const t_EntierLong *longA, const t_EntierLong *longB);

/**
 * soustraction de deux entiers longs de signes quelconques
 * @param longA : premier entier long
 * @param longB : second entier long
 * @return : pointeur vers le résultat (alloué dynamiquement)
 */
t_EntierLong *subAnySign(const t_EntierLong *longA, const t_EntierLong *longB);