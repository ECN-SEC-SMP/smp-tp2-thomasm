#pragma once
#include "entierlong.h"  // pour t_EntierLong
#include "lit_ecrit.h"   // pour afficherEntierLong()
#include "utilitaires.h" // pour firstDigit()
#include <iostream>      //pour cout et cin
#include <algorithm>     // pour max()

t_EntierLong *addSameSign(const t_EntierLong *longA, const t_EntierLong *longB);
t_EntierLong *subSameSign(const t_EntierLong *longA, const t_EntierLong *longB);