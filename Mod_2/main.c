#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Mod_1/tree_etu.h"
#include "../Mod_1/list.h"

#include "bloc.h"

struct byteCoding indexedCodeTable[256];

void init_indexedCodeTable(struct byteCoding indexedCodeTable[256]) {
    tree_resetByteCoding(indexedCodeTable);
    tree_resetByteOccurrence(indexedCodeTable);
}

void test_phrase_courte (struct byteCoding indexedCodeTable[256], FILE* fic) {
    printf("\n------- TEST PHRASE COURTE ----------\n");
    //variables utiles dans le test
    unsigned int taille_dispo;
    t_byte test_1[20] = "aaa bcd aa 4,ii"; //phrase à encoder dans le bloc 1

    //création du bloc 1 & de son descripteur
    struct descripteur_bloc* desc_1 = bloc_create(indexedCodeTable, 1);

    //remplissage d'indexedCodeTable selon la phrase à encoder
    tree_countByteOccurrence(test_1, strlen((char*)test_1), indexedCodeTable);

    //affichage des méta-données du bloc
    printf("\n>>> Avant encodage de la phrase courte <<<\n\n");
    bloc_display (desc_1->p_entete);

    taille_dispo = bloc_dispo(desc_1->p_entete);
    printf("\nPlace disponible pour encoder des données dans le bloc1 : %d\n", taille_dispo);

    printf("\n>>> Après encodage de la phrase courte <<<\n\n");
    memcpy(desc_1->donnees_encodees, test_1, strlen((char*)test_1)+1);
    desc_1->p_entete->nbBits = strlen((char*)test_1);

    printf("Phrase encodée : %s\n\n", desc_1->donnees_encodees);
    
    bloc_display(desc_1->p_entete);
    taille_dispo = bloc_dispo(desc_1->p_entete);
    printf("\nPlace disponible pour encoder des données dans le bloc1 : %d\n", taille_dispo);

    // écriture dans le fichier
    bloc_write (fic, desc_1);

    // fermeture bloc
    bloc_close (desc_1);
 
    printf("-------------------------------------\n\n");
}


void test_phrase_longue (struct byteCoding indexedCodeTable[256], FILE* fic) {
    printf("\n------- TEST PHRASE LONGUE ----------\n");
    //variables utiles dans le test
    unsigned int taille_dispo;
    //phrase à encoder dans le bloc 2
    const t_byte test_2[500] = "Ceci est une longue phrases /zeobzeovcb avec pleins de caractères étranges aoinzeoivzoevb46684ù/;,?'(!@";

    //création du bloc 2 & de son descripteur
    struct descripteur_bloc* desc_2 = bloc_create(indexedCodeTable, 1);

    //remplissage d'indexedCodeTable selon la phrase à encoder
    tree_countByteOccurrence(test_2, strlen((char*)test_2), indexedCodeTable);

    //affichage des méta-données du bloc
    printf("\n>>> Avant encodage de la phrase longue <<<\n\n");
    bloc_display (desc_2->p_entete);

    taille_dispo = bloc_dispo(desc_2->p_entete);
    printf("\nPlace disponible pour encoder des données dans le bloc2 : %d\n", taille_dispo);

    printf("\n>>> Après encodage de la phrase longue <<<\n\n");
    memcpy(desc_2->donnees_encodees, test_2, strlen((char*)test_2)+1);
    desc_2->p_entete->nbBits = strlen((char*)test_2);

    printf("Phrase encodée : %s\n\n", desc_2->donnees_encodees);
    
    bloc_display(desc_2->p_entete);
    taille_dispo = bloc_dispo(desc_2->p_entete);
    printf("\nPlace disponible pour encoder des données dans le bloc2 : %d\n", taille_dispo);

    // écriture dans le fichier
    bloc_write (fic, desc_2);

    // fermeture bloc
    bloc_close (desc_2);
 
    printf("-------------------------------------\n\n");
}


void test_phrase_null (struct byteCoding indexedCodeTable[256], FILE* fic) {
    printf("\n------- TEST PHRASE VIDE/NULL ----------\n");
    //variables utiles dans le test
    unsigned int taille_dispo;
    //phrase à encoder dans le bloc 3
    const t_byte test_3[2] = "";
    
    //création du bloc 3 & de son descripteur
    struct descripteur_bloc* desc_3 = bloc_create(indexedCodeTable, 1);

    //remplissage d'indexedCodeTable selon la phrase à encoder
    tree_countByteOccurrence(test_3, strlen((char*)test_3), indexedCodeTable);

    //affichage des méta-données du bloc
    printf("\n>>> Avant encodage de la phrase vide <<<\n\n");
    bloc_display (desc_3->p_entete);

    taille_dispo = bloc_dispo(desc_3->p_entete);
    printf("\nPlace disponible pour encoder des données dans le bloc3 : %d\n", taille_dispo);

    printf("\n>>> Après encodage de la phrase vide <<<\n\n");
    memcpy(desc_3->donnees_encodees, test_3, strlen((char*)test_3)+1);
    desc_3->p_entete->nbBits = strlen((char*)test_3);

    printf("Phrase encodée : %s\n\n", desc_3->donnees_encodees);
    
    bloc_display(desc_3->p_entete);
    taille_dispo = bloc_dispo(desc_3->p_entete);
    printf("\nPlace disponible pour encoder des données dans le bloc3 : %d\n", taille_dispo);

    // écriture dans le fichier
    bloc_write (fic, desc_3);

    // fermeture bloc
    bloc_close (desc_3);
 
    printf("-------------------------------------\n\n");

}


void test_phrase_780_a (struct byteCoding indexedCodeTable[256], FILE* fic) {
    printf("\n------- TEST PHRASE 780 'a' ----------\n");
    //variables utiles dans le test
    unsigned int taille_dispo;
    //phrase à encoder dans le bloc 4
    const t_byte test_4[800] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    
    //création du bloc 4 & de son descripteur
    struct descripteur_bloc* desc_4 = bloc_create(indexedCodeTable, 1);

    //remplissage d'indexedCodeTable selon la phrase à encoder
    tree_countByteOccurrence(test_4, strlen((char*)test_4), indexedCodeTable);

    //affichage des méta-données du bloc
    printf("\n>>> Avant encodage de la phrase de 780 'a' <<<\n\n");
    bloc_display (desc_4->p_entete);

    taille_dispo = bloc_dispo(desc_4->p_entete);
    printf("\nPlace disponible pour encoder des données dans le bloc4 : %d\n", taille_dispo);

    printf("\n>>> Après encodage de la phrase de 780 'a' <<<\n\n");
    memcpy(desc_4->donnees_encodees, test_4, strlen((char*)test_4)+1);
    desc_4->p_entete->nbBits = strlen((char*)test_4);

    printf("Phrase encodée : %s\n\n", desc_4->donnees_encodees);
    
    bloc_display(desc_4->p_entete);
    taille_dispo = bloc_dispo(desc_4->p_entete);
    printf("\nPlace disponible pour encoder des données dans le bloc4 : %d\n", taille_dispo);

    // écriture dans le fichier
    bloc_write (fic, desc_4);

    // fermeture bloc
    bloc_close (desc_4);
 
    printf("-------------------------------------\n\n");

}

void test_lecture (struct byteCoding indexedCodeTable[256], FILE* fic) {
    printf("\n----- LECTURE DANS LE FICHIER -------\n\n");

    //lecture du bloc 1
    printf(">>> BLOC 1\n\n");
    t_byte* bloc_1 = bloc_read(fic, 0);
    struct descripteur_bloc* desc_1 = bloc_open(bloc_1, indexedCodeTable);
    //affichage des méta-données du bloc1
    bloc_display (desc_1->p_entete);
    //affichage de la phrase récupérée à la lecture du fichier
    printf("\nPhrase encodée dans le bloc 1 : %s\n\n", desc_1->donnees_encodees);
    // fermeture du bloc1
    bloc_close (desc_1);

    //lecture du bloc 2
    printf(">>> BLOC 2\n\n");
    t_byte* bloc_2 = bloc_read(fic, 1);
    struct descripteur_bloc* desc_2 = bloc_open(bloc_2, indexedCodeTable);
    //affichage des méta-données du bloc2
    bloc_display (desc_2->p_entete);
    //affichage de la phrase récupérée à la lecture du fichier
    printf("\nPhrase encodée dans le bloc 2 : %s\n\n", desc_2->donnees_encodees);
    // fermeture du bloc2
    bloc_close (desc_2);

    //lecture du bloc 3
    printf(">>> BLOC 3\n\n");
    t_byte* bloc_3 = bloc_read(fic, 2);
    struct descripteur_bloc* desc_3 = bloc_open(bloc_3, indexedCodeTable);
    //affichage des méta-données du bloc3
    bloc_display (desc_3->p_entete);
    //affichage de la phrase récupérée à la lecture du fichier
    printf("\nPhrase encodée dans le bloc 3 : %s\n\n", desc_3->donnees_encodees);
    // fermeture du bloc3
    bloc_close (desc_3);

    //lecture du bloc 4
    printf(">>> BLOC 4\n\n");
    t_byte* bloc_4 = bloc_read(fic, 3);
    struct descripteur_bloc* desc_4 = bloc_open(bloc_4, indexedCodeTable);
    //affichage des méta-données du bloc3
    bloc_display (desc_4->p_entete);
    //affichage de la phrase récupérée à la lecture du fichier
    printf("\nPhrase encodée dans le bloc 4 : %s\n\n", desc_4->donnees_encodees);
    // fermeture du bloc4
    bloc_close (desc_4);

    printf("-------------------------------------\n\n");
}

int main () {

    init_indexedCodeTable(indexedCodeTable);

    //ouverture du fichier
    //mode append : "a+" --> reading & append
    FILE* fic = fopen("log.txt", "a+");
    if (fic == NULL) {
        //si le fichier ne s'est pas ouvert correctement
        printf("Main : erreur lors de l'ouverture du fichier, arrêt de la fonction.\n");
        return -1;
    }

    test_phrase_courte(indexedCodeTable, fic);
    test_phrase_longue(indexedCodeTable, fic);
    test_phrase_null(indexedCodeTable, fic);
    test_phrase_780_a(indexedCodeTable, fic);
    test_lecture(indexedCodeTable, fic);

    //fermeture du fichier
    int error;
    error = fclose(fic);
    if (error == EOF) {
        printf("Fonction bloc_write : erreur lors de la fermeture du fichier, arrêt de la fonction.\n");
        exit (-1);
    }

    return 0;
}