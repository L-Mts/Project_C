#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Mod_1/tree_etu.h"
#include "../Mod_1/list.h"

#include "bloc.h"

/*---------- FONCTIONS -----------*/

/*
création d'un bloc et du code d'Huffman associé
création de l'arbre d'Huffman selon table de codage (indexedCodeTable) du bloc précédent
création du descripteur de bloc associé
*/
struct descripteur_bloc* bloc_create (struct byteCoding indexedCodeTable[256], t_byte joker){
    // allocation mémoire pour le descripteur
    struct descripteur_bloc* desc_bloc = (struct descripteur_bloc*) malloc (sizeof (struct descripteur_bloc));
    if (desc_bloc == NULL) {
        printf("Fonction bloc_create : erreur d'allocation mémoire pour le descripteur de bloc\n");
        return NULL;
    }

    // allocation mémoire pour le bloc
    t_byte* bloc = (t_byte*) malloc (32*1024); //création d'un bloc de 32K (1K = 1024)
    if (bloc == NULL){
        printf("Fonction bloc_create : erreur d'allocation mémoire pour le bloc\n");
        return NULL;
    }
    
    desc_bloc->p_entete = (struct entete*) bloc; //adresse de bloc = adresse de son premier champ = adresse entete
    desc_bloc->p_entete->tailleBloc = 32*1024;
    
    // création code Huffman JOKER 
    desc_bloc->p_entete->joker = joker;

    desc_bloc->desc_indexedCodeTable = indexedCodeTable;
    desc_bloc->desc_indexedCodeTable[joker].occurrence = 15;

    // remplissage table de codage selon indexedCodeTable[256] de la table précédente
    desc_bloc->table_codage = (struct byteCoding*) (desc_bloc->p_entete + 1);
    int position=0; //position dans la table de codage
    for (int i=0; i<256; i++) { //parcours indexedCodeTable
        if (indexedCodeTable[i].occurrence != 0){
            desc_bloc->table_codage[position] = indexedCodeTable[i];
            position +=1;
        }
    }

    desc_bloc->p_entete->nbCodage = position;

    desc_bloc->donnees_encodees = (t_byte*) (desc_bloc->table_codage + desc_bloc->p_entete->nbCodage);

    desc_bloc->p_entete->nbBits = 0;
    desc_bloc->p_entete->nbMaxBits = (32*1024 - desc_bloc->p_entete->nbCodage*sizeof(struct byteCoding)
                                                - sizeof(struct entete))*8;        //*8 pour passer des octets à des bits
    

    // création du code Huffman associé
    desc_bloc->racine_huffman = tree_create (desc_bloc->desc_indexedCodeTable);  //création de l'arbre d'Huffman
    (void) tree_buildHuffmanCode(desc_bloc->racine_huffman, 0, 0);      //création du code Huffman
    
    // reset nombre occurence indexedCodeTable & récupération dans desc_bloc->indexedCodeTable
    tree_resetByteOccurrence(desc_bloc->desc_indexedCodeTable);

    //retourne l'adresse de desc_bloc
    return desc_bloc;
    
}


/*
écriture dans un fichier dont l'adresse est passée en paramètre
du bloc, en passant par son descripteur.
mode d'accès au fichier : append pour écrire à la fin
*/
void bloc_write (FILE * fic, struct descripteur_bloc* desc_bloc) {
    //ecriture dans le fichier
    fwrite((t_byte*) desc_bloc->p_entete, 32*1024, 1, fic);
}

/*
lecture, depuis un fichier passé en paramètre, d'un bloc de numéro connu et passé en paramètre
renvoit un bloc écrit en dur (compressé)
mode d'accès au fichier : read, pour éviter tout risque d'écrire dans le fichier et écraser les données par erreur
*/
t_byte* bloc_read (FILE * fic, int num_bloc) {
    // recherche du bloc à lire selon nom numéro
    fseek(fic, num_bloc*(32*1024), SEEK_SET);

    // lecture d'un bloc dans le fichier
    t_byte *bloc = (t_byte*) malloc (sizeof(t_byte)*32*1024);
    if (bloc == NULL) {
        printf("Fonction bloc_read : erreur lors de l'allocation mémoire pour le bloc, arrêt de la lecture.\n");
        return NULL;
    }
    fread (bloc, 32*1024, 1, fic);

    return bloc;
}



/* calcul de la place disponible dans le bloc en nombre de bits */
unsigned int bloc_dispo (struct entete* entete){
    unsigned int res;
    res = (entete->nbMaxBits) - (entete->nbBits);
    return res;
}

/*
ouverture d'un bloc : création du descripteur associé, de l'arbre d'Huffman, de la table de codage
*/
struct descripteur_bloc* bloc_open (t_byte* bloc_brut, struct byteCoding indexedCodeTable[256]){
    //malloc pour allouer la mémoire pour le descripteur de bloc
    struct descripteur_bloc* desc_bloc = (struct descripteur_bloc*) malloc (sizeof (struct descripteur_bloc));

    //vérification sur le malloc
    if (desc_bloc == NULL){
        printf("Fonction bloc_open : erreur lors de l'allocation de la mémoire pour le descripteur de bloc, arrêt de la fonction.\n");
        return NULL;
    }

    // remplir descripteur à l'aide des valeurs dans l'entete & de l'indexedCodeTable récupéré en paramètre de la fonction
    desc_bloc->p_entete = (struct entete*) bloc_brut;
    desc_bloc->table_codage = (struct byteCoding*) (desc_bloc->p_entete + 1);
    desc_bloc->donnees_encodees = (t_byte*) (desc_bloc->table_codage + desc_bloc->p_entete->nbCodage);
    desc_bloc->desc_indexedCodeTable = indexedCodeTable;

    // remplir indexedCodeTable grâce à table de codage
    tree_resetByteCoding(desc_bloc->desc_indexedCodeTable);
    tree_resetByteOccurrence(desc_bloc->desc_indexedCodeTable);
    for (unsigned int i=0; i<desc_bloc->p_entete->nbCodage; i++){
        int j = desc_bloc->table_codage[i].byte;
        desc_bloc->desc_indexedCodeTable[j] = desc_bloc->table_codage[i];
    }

    // création abre d'Huffman
    desc_bloc->racine_huffman = tree_create(desc_bloc->desc_indexedCodeTable);
    (void)tree_buildHuffmanCode(desc_bloc->racine_huffman,0,0);

    // retour adresse descripteur_tableau
    return desc_bloc;
}

/*
fermeture d'un bloc : libération des zones mémoires utilisées par le bloc,
l'arbre d'huffman associé, et le descripteur
*/
void bloc_close (struct descripteur_bloc* desc_bloc){
    // libération de la mémoire allouée pour l'arbre de Huffman
    tree_destroy(desc_bloc->racine_huffman);

    // libération de la mémoire allouée pour le bloc
    free (desc_bloc->p_entete);

    // libération de la mémoire allouée pour le descripteur de bloc
    free(desc_bloc);
}

/*
affichage des méta-données d'un bloc
*/
void bloc_display (struct entete* entete){
    printf ("--- Méta-données du bloc ---\n");

    // affichage des données dans l'entete
    printf ("Taille du bloc (en octets) : %d\n", entete->tailleBloc);
    printf ("Nombre maximum de bits pour coder les données : %d\n", entete->nbMaxBits);
    printf ("Nombre de bits encodés : %d\n", entete->nbBits);
    printf ("Nombre de bits de la table d'encodage : %d\n", entete->nbCodage);

    // calcul de l'adresse de la table de codage à l'aide des valeurs de l'entete
    struct byteCoding* table_codage = (struct byteCoding*) entete + 1;

    // affichage de la table d'encodage
    for (int i=0; i < (int)entete->nbCodage; i++) {
        printf("Valeur : %c -- occurrences : %d -- code Huffman : %d -- nbr bytes : %d\n",
            table_codage[i].byte, table_codage[i].occurrence, table_codage[i].huffmanCode, table_codage[i].nbBits);
    }

}