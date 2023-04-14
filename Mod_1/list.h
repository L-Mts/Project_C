/* -----------------------------------------------------------
   module list 
   -----------------------------------------------------------
   08/11/08	SR	creation
   -----------------------------------------------------------
*/

#ifndef _LIST_H_
#define _LIST_H_
struct _list_node {
	void * data;
	struct _list_node * next;
};
typedef struct _list_node s_node;

s_node * list_create(void); //creation d'une nouvelle liste vide
s_node * list_insert(s_node * head, void * data); //creation+insertion noeud en tete de liste -> return tete
s_node * list_append(s_node * head, void * data); //creation+ajout noeud en queue de liste -> return queue
s_node * list_append2(s_node ** head, s_node * queue, void * data); //optimisation de list_append
s_node * list_remove(s_node * head, void * data); //suppression 1e instance donnee dans liste -> return tete
s_node * list_headRemove(s_node * head); //suppression tete de liste -> return nouvelle tete
s_node * list_destroy(s_node * head); //destruction liste (!! libération des données pas prise en charge)
int list_process(s_node * head, int (*fct)(s_node * node, 
			void * param), void * param, s_node ** last); //applique action sur chaque noeud de liste -> inutile
int list_isEmpty(s_node * head); //vérifie si liste est vide
s_node * list_orderedAppend(s_node ** head, int (*compare)(s_node *, void *), 
		void *param); //ajout noeud dans liste ordonnée selon résultat de 'compare' <- si donnée existe déjà : pas ajoutee
s_node * list_next(s_node * node); //noeud suivant de la liste

// type en un type pointeur generique
#define GET_LIST_DATA(node, type) ((type)(node->data))
//lire ou écrire donnee noeud
#define SET_LIST_DATA(node, mydata) (node->data=(void*)(mydata))
#endif
