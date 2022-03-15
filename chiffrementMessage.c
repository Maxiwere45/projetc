#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAILLE_TABLEAU_ASCII 52

int verifierAlphanumerique(char* texte){
    int sizeTEXTE = strlen(texte);
    // Tableau contenant les correspondance en décimal des
    // caractères alphanumérique
    int* tableauASCII = (int*) malloc(4 * (TAILLE_TABLEAU_ASCII));
    char* tableauCARACTERES = (char*) malloc(sizeof(char) * strlen(texte));

    //========= VERIFICATION DE L'ALLOCATION =================//
    if (tableauASCII == NULL) {
        perror("Echec de l'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    if (tableauCARACTERES == NULL) {
        perror("Echec de l'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    //=========================================================//

    // Remplissage du tableau ASCII alphanumérique [+ SPACE]
    //>> [OMPTIMISATION SEMI-POSSIBLE]
    int count = 0;
    while (count < TAILLE_TABLEAU_ASCII) {
        for (int i = 65; i <= 90; i++) {
            tableauASCII[count] = i;
            count++;
        }
        for (int i = 97; i <= 122; i++) {
            tableauASCII[count] = i;
            count++;
        }
        tableauASCII[count] = 32;
        count++;
    }

    for (int i = 0; i < sizeTEXTE; i++) {
        tableauCARACTERES[i] = (int) texte[i];
    }

    int corresTROUVE = 0;
    //>> [OMPTIMISATION SEMI-POSSIBLE] 
    for (int i = 0; i < sizeTEXTE; i++) {
        for (int j = 0; j < TAILLE_TABLEAU_ASCII; j++){
            if (tableauCARACTERES[i] == tableauASCII[j]) {
                corresTROUVE++;
            }
        }
    }

    free(tableauASCII);
    free(tableauCARACTERES);

    if (corresTROUVE == sizeTEXTE) {
        return (EXIT_SUCCESS);
    } else{
        return (EXIT_FAILURE);
    }
}

void convertirAccents(char texte){

}

void chiffrer(char texte){

}

void dechiffrer(char texte){

}

void affichage(char texte){

}