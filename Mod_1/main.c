#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "tree_etu.h"

void test1(struct byteCoding indexedCodeTable[256]) {
    //lecture buffer + remplissage tableau
    const t_byte test1[20] = "aaa bcd aa 4,ii";
    printf("\nPhrase de test : '%s'\n", test1);
    tree_countByteOccurrence (test1, strlen((char*)test1), indexedCodeTable);
}

void test2(struct byteCoding indexedCodeTable[256]) {
    //lecture buffer + remplissage tableau
    const t_byte test2[20] = "";
    printf("\nPhrase de test : '%s'\n", test2);
    tree_countByteOccurrence (test2, strlen((char*)test2), indexedCodeTable);
}

void test3(struct byteCoding indexedCodeTable[256]) {
    //lecture buffer + remplissage tableau
    const t_byte test3[500] = "Ceci est une longue phrases /zeobzeovcb avec pleins de caractères étranges aoinzeoivzoevb46684ù/;,?'(!@";
    printf("\nPhrase de test : '%s'\n", test3);
    tree_countByteOccurrence (test3, strlen((char*)test3), indexedCodeTable);
}

void test4(struct byteCoding indexedCodeTable[256]) {
    //lecture buffer + remplissage tableau
    const t_byte test4[800] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    printf("\nPhrase de test : '%s'\n", test4);
    tree_countByteOccurrence (test4, strlen((char*)test4), indexedCodeTable);
}


int main() {

    //déclaration du tableau
    struct byteCoding indexedCodeTable[256];

    //mise en place du tableau -> tout à 0
    //automatisation possible : boucle for pour vérifier que les champs sont bien à 0
    tree_resetByteOccurrence (indexedCodeTable);
    tree_resetByteCoding (indexedCodeTable);

    //automatisation possible : tree_resetByteOccurence, tree_resetByteCoding,
        // tree_create, tree_buildHuffmanCode, tree_display, tree_destroy & automatisations de ces tests dans chaque
        // fonction test (test1, test2, test3, test4) --> pour pouvoir les faire à la suite
    test1(indexedCodeTable);  //phrase 'normale'
    //test2(indexedCodeTable); //phrase vide
    //test3(indexedCodeTable); //phrase un peu plus longue que celle du test 1
    //test4(indexedCodeTable); //760 caractères 'a'
    printf("\n");
    
    //test création arbre avec tableau
    struct tree_node *racine = tree_create (indexedCodeTable);


    printf("------ CREATION DES CODES -------\n");
    //test création des codes d'huffman
    tree_buildHuffmanCode (racine, 0, 0);

    printf("\n");
    printf("------ AFFICHAGE -------\n");
    tree_display (racine, 0);
    printf("\n");

    //test destruction de l'arbre
    printf("------ DESTRUCTION -------\n");
    tree_destroy (racine);
    
    return 0;
}