/* ---------------------------------------------------------------
   Log Mollo: compresseur de journaux en ligne
   Gestion des codes de huffman
   S. Rubini, UBO
   ---------------------------------------------------------------
*/

#ifndef _TREE_H
#define _TREE_H

typedef unsigned char t_byte;

// codage des valeurs d'octet
struct byteCoding {
     int occurrence;  // a conserver au debut  //nbr d'occurence de l'octet/lettre
     unsigned int huffmanCode;
     unsigned int nbBits;  //nbr de bits utilisé pac code Huffman
     t_byte    byte; //valeur de l'octet à encoder / de la lettre
};

// arbre de huffman
struct tree_node {
	int *occ; //pointeur vers nbr occurence (somme si enfants) / pointeur vers byteCoding -> table encodage si noeud feuille
	struct tree_node *feuilleDroite; //pointeur vers noeud enfant droit 
	struct tree_node *feuilleGauche; //pointeur vers noeud enfant gauche
	struct tree_node *pere; //pointeur vers noeud pere
};

// gestion du tableau de codage des octets
void tree_resetByteOccurrence( struct byteCoding indexedCodeTable[256] );
   	// remet a zero le nombre d'occurrences des octets
void tree_resetByteCoding( struct byteCoding indexedCodeTable[256] ) ;
   	// remet a zero les codes octet
void tree_countByteOccurrence( const t_byte * buffer, int size,
			       struct byteCoding indexedCodeTable[256] );
	// compte de nombre d'occurrence des octets dans un tampon

void tree_displayByteCoding(struct byteCoding indexedCodeTable[256]);
	// affiche la table de codage des valeurs d'octet pour debug

/* gestion de l'arbre de Huffman */
struct tree_node * tree_createNode (struct tree_node * father, int * value ) ;
	// creation d'un noeud
struct tree_node * tree_createCodingNode ( struct tree_node * left, 
					   struct tree_node * right );
   	// creation d'un noeud de codage et liaison avec ses fils
struct tree_node * tree_create ( struct byteCoding * indexedCodeTable );
	// creation de l'arbre
void tree_destroy( struct tree_node * root );
   	// destruction d'un arbre et liberation des donnees 
	// (sauf au niveau des feuilles)
void tree_buildHuffmanCode(struct tree_node * root, int level, int code) ;
	// construit les codes de huffman en parcourant l'arbre
void tree_display( struct tree_node * root, int level ) ;
	// affichage de l'arbre

#endif

