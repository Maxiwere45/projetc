#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int verifierAlphanumerique(const char *texte){
    int sizeTEXTE = strlen(texte);
    int count = 0;
    int counter = 0;
    for (int j = 0; j < strlen(texte); j++){
        for (int k = 65; k < 90; k++)
        {
            if ((int) texte[j] == k){counter++;}
        }
        for (int k = 97; k < 122; k++){
            if ((int) texte[j] == k){counter++;}
        }
        // [ESPACE, virgule, apostrophe] inclus
        if ((int) texte[j] == 32 || 
            (int) texte[j] == 39 ||
            (int) texte[j] == 44 || 
            (int) texte[j] == 46){
            counter++;
        }
    }

    if (counter == strlen(texte)) {
        return EXIT_SUCCESS;
    } else{
        return EXIT_FAILURE;
    }
    
}

void convertirAccents(char *texte){

}

int chiffrer(char *texte, int cle){
    // appel de la fonction de vérification
    if (verifierAlphanumerique(texte) == 1){exit(EXIT_FAILURE);}
    if (cle > 25 || cle < 0){exit(EXIT_FAILURE);}
    int sizeTEXTE = strlen(texte);
    int* tableauCARACTERESCHIFFRE = NULL;
    // Allocation dynamique du message chiffré
    tableauCARACTERESCHIFFRE = (int*) malloc(4 * (strlen(texte)));
    if (tableauCARACTERESCHIFFRE == NULL) {
        perror("Echec de l'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    int corr_ascii,over_flow_garbage = 0, over_flow = 0;
    for (int i = 0; i < sizeTEXTE; i++) {
        //<> Code ASCII de chaque caractère
        corr_ascii = (int)texte[i];
        //<> compteurs de dépassement
        over_flow = 0;
        over_flow_garbage = corr_ascii;
        
        //<> Intervalle [65..90] <=> [A..Z] du tableau ASCII
        if (corr_ascii >= 65 && corr_ascii <= 90){
            //<> Si le caractère à chiffrer dépasse l'intervalle
            if ((corr_ascii + cle) > 90) {
                //<> Récupération du nombre de pas dépassant l'intervalle [65..90]
                while (over_flow_garbage <= 90) {over_flow++; over_flow_garbage++;}
                //<> Affectation et chiffrement de chaque caractère
                tableauCARACTERESCHIFFRE[i] = 65 + (cle - over_flow);
                texte[i] = (char) tableauCARACTERESCHIFFRE[i];
            } else{
                tableauCARACTERESCHIFFRE[i] = corr_ascii + cle;
                texte[i] = (char) tableauCARACTERESCHIFFRE[i];
            }
        //<> Intervalle [a..z] du tableau ASCII
        } else if(corr_ascii >= 97 && corr_ascii <= 122){
            if ((corr_ascii + cle) > 122) {
                while (over_flow_garbage <= 122) {over_flow++; over_flow_garbage++;}
                tableauCARACTERESCHIFFRE[i] = 97 + (cle - over_flow);
                texte[i] = (char) tableauCARACTERESCHIFFRE[i];
            } else {
                tableauCARACTERESCHIFFRE[i] = corr_ascii + cle;
                texte[i] = (char) tableauCARACTERESCHIFFRE[i];
            }
        } else{
            //<> Caractère [ESPACE] du tableau ASCII
            if (corr_ascii == 32) {
                tableauCARACTERESCHIFFRE[i] = 35;
                texte[i] = (char) tableauCARACTERESCHIFFRE[i];
            } else{
                tableauCARACTERESCHIFFRE[i] = corr_ascii + cle;
                texte[i] = (char) tableauCARACTERESCHIFFRE[i];
            }
        }
    }
    free(tableauCARACTERESCHIFFRE);
    return EXIT_SUCCESS;
}

int dechiffrer(char *texte, int cle){
    // appel de la fonction de vérification
    if (cle > 25 || cle < 0){exit(EXIT_FAILURE);}
    int sizeTEXTE = strlen(texte);
    int* tableauCARACTERESDECHIFFRE = NULL;
    // Allocation dynamique du message déchiffré
    tableauCARACTERESDECHIFFRE = malloc(4 * (strlen(texte)));
    if (tableauCARACTERESDECHIFFRE == NULL) {
        perror("Echec de l'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    int corr_ascii,over_flow_garbage = 0, over_flow = 0;
    for (int i = 0; i < sizeTEXTE; i++) {
        //<> Code ASCII de chaque caractère
        corr_ascii = (int)texte[i];
        //<> compteurs de dépassement
        over_flow = 0;
        over_flow_garbage = corr_ascii;
        //<> Intervalle [65..90] <=> [A..Z] du tableau ASCII
        if (corr_ascii >= 65 && corr_ascii <= 90){
            //<> Si le caractère à déchiffrer dépasse l'intervalle
            if ((corr_ascii - cle) < 65) {
                //<> Récupération du nombre de pas dépassant l'intervalle [65..90]
                while (over_flow_garbage >= 65) {over_flow++; over_flow_garbage--;}
                //<> Affectation et déchiffrement de chaque caractère
                tableauCARACTERESDECHIFFRE[i] = 90 - (cle - over_flow);
                texte[i] = (char) tableauCARACTERESDECHIFFRE[i];
            } else{
                tableauCARACTERESDECHIFFRE[i] = corr_ascii - cle;
                texte[i] = (char) tableauCARACTERESDECHIFFRE[i];
            }
            //<> Intervalle [a..z] du tableau ASCII
        } else if(corr_ascii >= 97 && corr_ascii <= 122){
            if ((corr_ascii - cle) < 97) {
                while (over_flow_garbage >= 97) {over_flow++; over_flow_garbage--;}
                tableauCARACTERESDECHIFFRE[i] = 97 - (cle - over_flow);
                texte[i] = (char) tableauCARACTERESDECHIFFRE[i];
            } else {
                tableauCARACTERESDECHIFFRE[i] = corr_ascii - cle;
                texte[i] = (char) tableauCARACTERESDECHIFFRE[i];
            }
        } else{
            //<> Caractère [ESPACE] du tableau ASCII
            if (corr_ascii == 35) {
                tableauCARACTERESDECHIFFRE[i] = 32;
                texte[i] = (char) tableauCARACTERESDECHIFFRE[i];
            } else{
                tableauCARACTERESDECHIFFRE[i] = corr_ascii - cle;
                texte[i] = (char) tableauCARACTERESDECHIFFRE[i];
            }
        }
    }
    free(tableauCARACTERESDECHIFFRE);
    return EXIT_SUCCESS;
}

int affichage(){
    return 0;
}
