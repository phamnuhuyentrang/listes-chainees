#include <stdio.h>
#include <stdlib.h>

#include "tp3.h"

int main () {
   int choix;
   int c;
   int tab[5][6] = {{5,0,2,7,4,0},{0,1,1,0,0,0},{0,0,0,0,0,0},{0,3,0,2,0,0},{6,0,0,0,0,2}};
   int tab2[5][6] = {{-5,1,2,0,4,2},{-5,1,2,0,4,2},{0,0,-4,0,0,0},{0,3,0,2,0,0},{6,0,5,0,0,2}};
   matrice_creuse m,m1,m2,m3;


   for (;;) {
      printf("1. Transformer une matrice.\n");
      printf("2. Lire une matrice creuse a partir d'un fichier.\n");
      printf("3. Afficher une matrice creuse.\n");
      printf("4. Addition de 2 matrices creuses. \n");
      printf("5. Calculer le gain en espace en utilisant matrice creuse pour une matrice donnee. \n");
      printf("6. Quitter. \n");
      printf("Votre choix: ");

      scanf("%d", &choix);
      printf("================================================================================\n");
      switch (choix){
            case 1:
                    constructMat(&m,tab,5,6);
                    constructMat(&m3,tab2,5,6);
                    break;
            case 2:
                    lireFichier(&m3,"test.txt");
                    //lireFichier(&m1,"matrice1.csv");
                    //lireFichier(&m2,"matrice2.csv");
                    break;
            case 3:
            		printf("Quelle matrice voulez-vous afficher?");
            		scanf("%d",&c);
            		switch (c){
            			case 0: afficherMat(m);
            					break;
            			case 1: afficherMat(m1);
            					break;
            			case 2: afficherMat(m2);
            					break;
            			case 3: afficherMat(m3);
            					break;
            			default: printf("Veuillez saisir 0,1 ou 2\n");
            					break;
            		}
                    break;
            case 4:
            		addMat(m,m3);
            		//saddMat(m1,m2);
                    break;
            case 5:
            		printf("Octets Gagnes: %d\n", nombreOctetsGagnes(m1));
                    break;
            case 6:
            		deleteMat(&m);
            		//deleteMat(&m1);
            		//deleteMat(&m2);
            		deleteMat(&m3);
                    exit(0);
break;
            default:
                    printf("\nMerci de resaissir le choix valide. \n");
	        break;
      }
   }

   return 0;
}
