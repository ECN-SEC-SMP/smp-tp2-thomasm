#pragma once
#include "entierlong.h" // pour t_EntierLong
#include <iostream>     //pour cout et cin

t_EntierLong *convStdToLong(const int *intStd);
bool equal2long(const t_EntierLong *longA, const t_EntierLong *longB);
bool compAbs2long(const t_EntierLong *longA, const t_EntierLong *longB);
u_int8_t *firstDigit(const t_EntierLong *intLong);