/* ----------------------------------
   Log Mollo: compresseur de journaux en ligne
   Gestion des blocs à encodé
   Loana MOTTAIS
------------------------------------- */

#include "../Mod_1/tree_etu.h"
#include "../Mod_1/list.h"


/*---------- STRUCTURES -----------*/

struct entete {
    unsigned int tailleBloc; //taille bloc invariable (=32Ko)
    unsigned int nbMaxBits; //taille totale en bits disponible pour coder des données
    unsigned int nbBits; //taille en bits des données déjà encodées dans le bloc
    unsigned int nbCodage; //nb de caractères différents encodés = taille table d'encodage sans les caractère d'occurence 0
    t_byte joker; 
};


struct descripteur_bloc { 
    struct entete* p_entete; //pointeur sur l'entete du bloc
    struct byteCoding* table_codage; //pointeur sur la table des codages (indexedCodeTable sans char. d'occurence 0)
    t_byte* donnees_encodees; //pointeur sur les données encodées
    struct byteCoding* desc_indexedCodeTable; //pointeur sur la table d'encodage (indexedCodeTable avec tous les char)
    struct tree_node* racine_huffman; //pointeur sur la racine de l'arbre d'Huffman construit
};


/*---------- FONCTIONS -----------*/


/*
création d'un bloc et du code d'Huffman associé
création de l'arbre d'Huffman selon table de codage (indexedCodeTable) du bloc précédent
création du descripteur de bloc associé
*/
struct descripteur_bloc* bloc_create (struct byteCoding indexedCodeTable[256], t_byte joker);


/*
écriture dans un fichier dont l'adresse est passée en paramètre
du bloc, en passant par son descripteur.
mode d'accès au fichier : append pour écrire à la fin
*/
void bloc_write (FILE * fic, struct descripteur_bloc* desc_bloc);


/*
lecture, depuis un fichier passé en paramètre, d'un bloc de numéro connu et passé en paramètre
renvoit un bloc écrit en dur (compressé)
mode d'accès au fichier : read, pour éviter tout risque d'écrire dans le fichier et écraser les données par erreur
*/
t_byte* bloc_read (FILE * fic, int num_bloc);


/* calcul de la place disponible dans le bloc en nombre de bits */
unsigned int bloc_dispo (struct entete* entete);

/*
ouverture d'un bloc : création du descripteur associé, de l'arbre d'Huffman, de la table de codage
*/
struct descripteur_bloc* bloc_open (t_byte* bloc_brut, struct byteCoding indexedCodeTable[256]);


/*
fermeture d'un bloc : libération des zones mémoires utilisées par le bloc,
l'arbre d'huffman associé, et le descripteur
*/
void bloc_close (struct descripteur_bloc* desc_bloc);

/*
affichage des méta-données d'un bloc
*/
void bloc_display (struct entete* entete);

