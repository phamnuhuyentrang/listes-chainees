#ifndef _TP3_H
#define _TP3_H
#define N 5
#define M 6
#define MAX 30
#include <stdio.h>
#include <stdlib.h>

typedef struct element Element;
struct element {
   int ind;
   int val;
   Element* next;
};

typedef Element* liste_ligne;

struct matrice_creuse {
    liste_ligne* ligne;
    int Nlignes;
    int Ncolonnes;
};
typedef struct matrice_creuse matrice_creuse;

void constructMat(matrice_creuse *m, int t[N][M], int Nlig, int Ncol);
void lireFichier(matrice_creuse *m, char nomFichier[MAX]);
void afficherMat(matrice_creuse m);
int getValue(matrice_creuse m, int i, int j);
void putValue(matrice_creuse *m, int i, int j, int val);
void addMat(matrice_creuse m1, matrice_creuse m2);
int nombreOctetsGagnes(matrice_creuse m1);
int nombreLignes (FILE* fichier);
int nombreColonnes(FILE *fichier);
void delete(liste_ligne *ligne, int col);
void remplace(liste_ligne* ligne, int col, int val);
void deleteMat(matrice_creuse *m);
Element *creeEle(int col, int val);

#endif

