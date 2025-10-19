
# SMP – TP2 — Entiers **longs**

## 1) Introduction
Objectif : réaliser des opérations sur des entiers à **grand nombre de chiffres** (base 10) représentés chiffre‑par‑chiffre, bornés par `MAXCHIFFRES`, avec un indicateur de signe. Les chiffres sont stockés **du moins significatif au plus significatif** (indice 0 → unités).

---

## 2) Fichiers utilisés
- `entierlong.h` : définition `struct t_EntierLong { bool negatif; int chiffres[MAXCHIFFRES]; }`. 
- `lit_ecrit.h/.cpp` : E/S : `ecrireEntierLong`, `lireEntierLong`. **Non modifiés**. 
- `utilitaires.h/.cpp` : conversions et comparaisons.
- `operations.h/.cpp` : opérations arithmétiques.
- `main.cpp` : jeux d’essais incrémentaux.

---

## 3) Fonctions et validations

### A. `convStdToLong(int std) → EntierLong`
- **Spécification** : convertir un entier standard en représentation « entier long ». 
- **Principe** : déterminer le signe, extraire les chiffres par divisions/modulo 10, remplir `chiffres[i]`. 
- **Essais (extrait exécution)** : 
```
=== Conversion ===
convStdToLong : 1234567 => +1234567
 (7 chiffres)
convStdToLong : 0 => +0
 (1 chiffre)
```

### B. `equal2long(const EntierLong& a, const EntierLong& b) → bool`
- **Spécification** : tester l’égalité stricte (signe + tous les chiffres). 
- **Principe** : comparer le booléen `negatif`, puis chaque case `chiffres[i]`. 
- **Essais** : 
```
=== Egalite ===
1234567 != 555555
555555  == 555555
0       == 0
-444444 != -666666
```

### C. `compAbs2long(const EntierLong& a, const EntierLong& b) → bool`  (retourne « |a| ≤ |b| »)
- **Spécification** : comparaison en **valeur absolue**. 
- **Principe** : ignorer le signe, sauter zéros de tête, comparer longueur utile puis chiffres de poids fort vers faible. 
- **Essais** : 
```
|1234567| !<= |555555|
|555555|  <= |555555|
|-444444| <= |555555|
|-666666| !<= |555555|
|0|      <= |555555|
```

### D. `addSameSign(const EntierLong& a, const EntierLong& b) → EntierLong`
- **Spécification** : addition **même signe** (contrat : `a.negatif == b.negatif`). 
- **Principe** : addition chiffre à chiffre avec **retient**; signe hérité; détection **overflow** si carry sortant au‑delà de `MAXCHIFFRES`. 
- **Essais** : 
```
+1234567 + +555555 = +1790122
-444444  + -666666 = -1111110
0 + 0 = 0
(Overflow attendu) 999..9 + 1 → ATTENTION : dépassement
```

### E. `subSameSign(const EntierLong& a, const EntierLong& b) → EntierLong`
- **Spécification** : soustraction **même signe**, avec précondition **|a| ≥ |b|**. Sinon, hors contrat.
- **Principe** : soustraction avec **borrow**; si résultat nul → signe forcé « + ». 
- **Essais** : 
```
+555555 - +1 = +555554
+555555 - +555555 = 0
-666666 - -444444 = -222222
(hors-contrat) signes différents → rejet
(hors-contrat) |a| < |b| → rejet
```

### F. `addAnySign(const EntierLong& a, const EntierLong& b) → EntierLong`
- **Spécification** : addition **tous signes**. 
- **Principe** : 
  - Si `signes égaux` → déléguer à `addSameSign`. 
  - Sinon → réduire à **soustraction d’absolus** : calculer `max(|a|,|b|) − min(|a|,|b|)` et reprendre le signe du plus grand en valeur absolue. 
- **Essais** : 
```
+1234567 + -444444 = +790123
-666666  + +555555 = -111111
0        + -444444 = -444444
-444444  + 0       = -444444
+1234567 + +555555 = +1790122
+555555  + +1234567= +1790122
```

### G. `subAnySign(const EntierLong& a, const EntierLong& b) → EntierLong`
- **Spécification** : soustraction **tous signes**.
- **Principe** : 
  - Si `signes différents` → réduire à **addition d’absolus** (déléguer à `addSameSign`). 
  - Si `signes identiques` → réduire à **soustraction d’absolus** ; comparer |a|/|b| pour déterminer l’ordre et le signe. 
- **Essais** : 
```
+1234567 - -444444 = +1679011
-444444  - +1234567= -1679011
-555555  - -666666 = +1222221
0        - +555555 = -555555
+555555  - 0       = +555555
+1234567 - +1234567= 0
```

## 7) Conclusion
Les fonctions de **conversion**, **égalité**, **comparaison absolue**, **addition/soustraction** (mêmes signes et signes quelconques) fonctionnent selon l’énoncé, avec gestion de cas limites (zéro, overflow).