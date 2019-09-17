#include "tp3.h"
#include <string.h>

void constructMat(matrice_creuse *m, int t[N][M], int Nlig, int Ncol) {
   int i=0, j=0;

   /*Initialisation*/
   m->Ncolonnes = Ncol;
   m->Nlignes = Nlig;
   m->ligne = malloc(sizeof(liste_ligne)*Nlig);

   for (i=0;i<Nlig;i++){
        m->ligne[i]=NULL;
        Element *last;
        for (j=0;j<Ncol;j++){
            if (t[i][j]!=0){
                Element *temp = malloc(sizeof(Element));
                temp->ind = j;
                temp->val = t[i][j];
                temp->next = NULL;
                if (m->ligne[i]==NULL){
                    m->ligne[i] = temp;
                } else {
                    last->next = temp;
                }
                last=temp;
            }
        }
   }
}

Element *creeEle(int col, int val) {
    Element *temp = malloc(sizeof(Element));
    if (temp == NULL) {
        printf("Erreur pour créer l'element \n");
        exit(-1);
    }
    temp->ind = col;
    temp->val = val;
    temp->next = NULL;
    return temp;
}


int nombreLignes(FILE *fichier) {
    if (fichier != NULL) {
        rewind(fichier);
        //fseek(fichier,0,SEEK_SET);
        unsigned int lignes = 1;
        while (!feof(fichier)) {
            fgetc(fichier);
            if (fgetc(fichier) == '\n')
                lignes++;
        }
        return lignes;
    }else {return 0;}

}

int nombreColonnes(FILE *fichier) {
    if (fichier != NULL) {
        rewind(fichier);
        unsigned int colonnes = 1;
        char c;
        do {
            c = fgetc(fichier);
            if (c == ';')
                colonnes++;
        } while (c != '\n');
        return colonnes;
    }
    return 0;
}

void lireFichier(matrice_creuse *m, char nomFichier[MAX]){
    int i,j,k;
    int lig, col;
    int tab[N][M];
    char c;
    FILE *fp;
    fp=fopen(nomFichier,"r+");
    if(fp == NULL) {
      perror("Error opening file");
      exit(-1);
    }
    else {
    	lig = nombreLignes(fp);
    	col = nombreColonnes(fp);
    	printf("lignes = %d\n",lig);
    	printf("colonnes = %d\n",col);
    	for (i=0;i<lig;i++){
    		for (j=0;j<col;j++){
    			k=0;
    			char str[10] = "";
    			do {
        			c = fgetc(fp);
        			if (c != ';' && c != '\n') {
            			str[k] = c;
            			k++;
        			}
    			} while (c != ';' && c != '\n');
    			tab[i][j] = atoi(str);
    		}
    	}
    }
    constructMat(m,tab,lig,col);
    fclose(fp);
}


void afficherMat(matrice_creuse m){
    int i=0;
    //if (m==NULL) exit(1);
    while (i< m.Nlignes){
        printf("ligne %d \n",i);
        Element *l_aux = m.ligne[i];
        while (l_aux != NULL){
            printf("Val: %d\n",l_aux->val);
            printf("Col: %d\n",l_aux->ind);
            l_aux = l_aux->next;
            printf("\n");
        }
        i++;
    }
}

int getValue(matrice_creuse m, int i, int j){
	int k=0;
	Element *l_aux = m.ligne[i];
    while (l_aux != NULL && l_aux->ind<=j){
        if (l_aux->ind ==j)
            k = l_aux->val;
        l_aux = l_aux->next;
    }
	return k;
}

void delete(liste_ligne *ligne, int col) {
    liste_ligne p = *ligne, prev;
    if (p != NULL && p->ind == col) {
        *ligne = p->next;
        free(p);
        return;
    }
    int k = 0;
    while (p != NULL && k < col) {
        if (k == p->ind) {
            prev = p;
            p = p->next;
        }
        k++;
    }
    if (p == NULL || p->ind > col) return;
    if (p->ind == col)
        prev->next = p->next;
    free(p);
}

void remplace(liste_ligne* ligne, int col, int val) {
    liste_ligne p = *ligne, prev;
    if (p->ind > col) {
        Element *e = creeEle(col, val);
        e->next = (*ligne);
        (*ligne) = e;
    } else if (p->ind == 0 && col == 0)
        p->val = val;
    else {
        int k = 0;
        while (p != NULL && k < col) {
            if (k == p->ind) {
                prev = p;
                p = p->next;
            }
            k++;
        }
        if (p != NULL) {
            if (p->ind == col)
                p->val = val;
            else if (col < p->ind) {
                Element *e = creeEle(col, val);
                e->next = p;
                prev->next = e;
            }
        } else {
            Element *e = creeEle(col, val);
            prev->next = e;
        }
    }
}

void putValue(matrice_creuse *m, int i, int j, int val) {
    if (m->ligne[i] == NULL) {
        if (val != 0) {
            Element *e = creeEle(j, val);
            m->ligne[i] = e;
        }
    } else {
        if (val == 0)
            delete(&m->ligne[i], j);
        else
            remplace(&m->ligne[i], j, val);
    }
}


void addMat(matrice_creuse m1, matrice_creuse m2) {
    if (m1.Ncolonnes == m2.Ncolonnes && m1.Nlignes == m2.Nlignes)
        for (int i = 0; i < m1.Nlignes; i++) {
            for (int j = 0; j < m1.Ncolonnes; j++) {
                putValue(&m1, i, j, getValue(m1, i, j) + getValue(m2, i, j));
            }
        }
    else
        printf("Les 2 matrices n'ont pas de même dimentions");
}

int nombreOctetsGagnes(matrice_creuse m1){
	int ind =0, count=0, octet;
	while (ind< m1.Nlignes){
		Element *l_aux = m1.ligne[ind];
        while (l_aux != NULL){
        	count++;
            l_aux = l_aux->next;
        }
        ind++;
	}
	octet = (m1.Nlignes*m1.Ncolonnes*sizeof(int) + (m1.Nlignes +1)*sizeof(int*)) - (sizeof(matrice_creuse) + m1.Nlignes*sizeof(liste_ligne) + count*sizeof(Element));
	return octet;
}
void deleteMat(matrice_creuse *m) {
    for (int i = 0; i < m->Nlignes; i++){
        for (int j = 0; j < m->Ncolonnes; ++j)
            putValue(m, i, j, 0);
        free(m->ligne[i]);
    }
    m->Ncolonnes = 0;
    m->Nlignes = 0;
    free(m);
}




