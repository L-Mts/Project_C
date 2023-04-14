#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tree_etu.h"


/* --- gestion du tableau de codage des octets ---*/

// remet a zero le nombre d'occurrences des octets
void tree_resetByteOccurrence( struct byteCoding indexedCodeTable[256] ){
    for (int i=0; i<256; i++) {
        indexedCodeTable[i].occurrence = 0;
    }
}

// initialise les champs byte, remet à zero les codes octet (code de Huffman) et le nombre de bits nécessaire pour chaque code
void tree_resetByteCoding( struct byteCoding indexedCodeTable[256] ) {
    for (int i=0; i<256; i++) {
        indexedCodeTable[i].byte = i;
        indexedCodeTable[i].huffmanCode = 0;
        indexedCodeTable[i].nbBits = 0;
    }
}
   	
// compte de nombre d'occurrence des octets dans un tampon
void tree_countByteOccurrence( const t_byte * buffer, int size, struct byteCoding indexedCodeTable[256] ) {
    for (int i=0; i<size; i++){ //parcours buffer comme tableau
        indexedCodeTable[buffer[i]].occurrence += 1;  //valeur buffer[i] = valeur octet = indice dans indexedCodeTable
    }
}

// affiche la table de codage des valeurs d'octet pour debug
void tree_displayByteCoding(struct byteCoding indexedCodeTable[256]) {
    for (int i=0; i<256; i++) {
        printf("Valeur : %c -- occurrences : %d -- code Huffman : %d -- nbr bytes : %d\n",
            indexedCodeTable[i].byte, indexedCodeTable[i].occurrence, indexedCodeTable[i].huffmanCode, indexedCodeTable[i].nbBits);
    }
}
	


/* --- gestion de l'arbre de Huffman ---*/

// creation d'un noeud
struct tree_node * tree_createNode (struct tree_node * father, int * value ) {
    //allocation mémoire nouveau noeud
    struct tree_node *nouveau = malloc(sizeof(struct tree_node));
    //initialisation champs nouveau noeud
    nouveau->occ = value;
    nouveau->pere = father;
    nouveau->feuilleDroite = NULL;
    nouveau->feuilleGauche = NULL;
    //retour adresse nouveau noeud
    return nouveau;
}
	

// creation d'un noeud de codage et liaison avec ses fils
struct tree_node * tree_createCodingNode ( struct tree_node * left, struct tree_node * right ) {
    //allocation mémoire nouveau noeud
    struct tree_node *nouveau = malloc(sizeof(struct tree_node));
    //allocation mémoire int somme valeurs occurences enfants
    int *somme = malloc(sizeof(int));
    *somme = *(left->occ) + *(right->occ);
    //initialisation champs nouveau noeud
    nouveau->occ = somme;
    nouveau->feuilleDroite = right;
    nouveau->feuilleGauche = left;
    nouveau->pere=NULL;
    //retour adresse nouveau noeud
    return nouveau;
}

//fonction compare
int compare(s_node *n, void *p){
    struct tree_node *noeud_p = (struct tree_node*) p; //caster p en pointeur sur struct tree_node
    struct tree_node *noeud_n = (struct tree_node*) (n->data); //caster n->data en pointeur sur struct tree_node
    int res = 0;
    if (*(noeud_n->occ)<*(noeud_p->occ)){
        res = -1;
    } else if (*(noeud_n->occ)==*(noeud_p->occ)){
        res = 0;
    } else {
        res = 1;
    }
    return res;
}

// creation de l'arbre
struct tree_node * tree_create ( struct byteCoding * indexedCodeTable ) {
    //creation nouvelle liste vide
    s_node *liste = list_create();
    //initialisation liste ordonnée avec toutes les feuilles créé via les données de indexedCodeTable
    for (int i=0; i<256; i++) {
        if (indexedCodeTable[i].occurrence!=0){ //création feuille seulement s'il y a des occurrences
            struct tree_node *new_noeud = tree_createNode(NULL, &(indexedCodeTable[i].occurrence));
            (void)list_orderedAppend(&liste, &compare, new_noeud);
        }
    }

    //si la liste est pas vide -> retourne NULL
    if (list_isEmpty(liste)) return NULL;
    //sinon
    //tant que la tete a un next -> rassembler les 2 premiers en 1 noeud -> continuer l'arbre
    while(liste->next != NULL){
        //creation noeud (parent) avec 2 premiers chainons de liste
        struct tree_node *gauche = GET_LIST_DATA(liste, struct tree_node*);
        struct tree_node *droite = GET_LIST_DATA(liste->next, struct tree_node*);
        struct tree_node *parent = tree_createCodingNode(gauche, droite);
        //adoption des enfants par le nouveau noeud parent créé : passer adresse de parent dans champ 'pere' des enfants
        parent->feuilleGauche->pere=parent;
        parent->feuilleDroite->pere=parent;
        //suppression 2 premiers chainons de liste utilisés pour créé parent
        liste = list_headRemove(liste);
        liste = list_headRemove(liste);
        //insertion noeud parent dans liste
        (void)list_orderedAppend(&liste, &compare, parent);
    }

    //récupération de l'adresse du parent suprème (racine de l'arbre)
    struct tree_node *racine = GET_LIST_DATA(liste, struct tree_node*);

    //destruction de la liste -> on ne conserve que l'arbre
    liste = list_destroy(liste);

    return racine;
    
}
	

// destruction d'un arbre et liberation des donnees (sauf au niveau des feuilles)
void tree_destroy( struct tree_node * root ) {
    if (root != NULL) {
        if (root->feuilleDroite!=NULL && root->feuilleGauche!=NULL){
            tree_destroy (root->feuilleDroite);
            tree_destroy (root->feuilleGauche);
            free (root->occ);
            root->occ=NULL;
            free (root);
            root=NULL;
        } else {
            free (root);
            root=NULL;
        }
    }

}
   	

// construit les codes de huffman en parcourant l'arbre
//code en base 2
void tree_buildHuffmanCode(struct tree_node * root, int level, int code) { 
    if (root != NULL) {
        if (root->feuilleDroite!=NULL && root->feuilleGauche!=NULL) { //c'est un noeud
            int new_code = code*2;
            tree_buildHuffmanCode(root->feuilleGauche, level+1, (new_code));
            tree_buildHuffmanCode(root->feuilleDroite, level+1, (new_code+1));
        } else {                                                //c'est une feuille
            struct byteCoding* ad = (struct byteCoding*) root->occ;
            ad->huffmanCode = code;
            ad->nbBits = level;
        }
    }
}
	
// affichage de l'arbre
void tree_display( struct tree_node * root, int level ) {
    if(root!=NULL){
        if (root->feuilleDroite!=NULL && root->feuilleGauche!=NULL) { //pas une feuille
            printf("Noeud de niveau %d occurences : %d\n", level, *(root->occ));
            tree_display (root->feuilleGauche, level+1);
            tree_display (root->feuilleDroite, level+1);
        } else if (root->feuilleDroite==NULL && root->feuilleGauche==NULL) { //feuille
            struct byteCoding* ad = (struct byteCoding*) root->occ;
            printf("Feuille de niveau %d -- lettre : %c -- occurences : %d -- code : %d -- nombre bits code : %d\n",
                level, ad->byte, ad->occurrence, ad->huffmanCode, ad->nbBits);
        }
    }
}
	


