#ifndef __quadtree__
#define __quadtree__

/* structure pour stocker les coordonnées d'un point*/
typedef struct  {
    int x ;
    int y ;
}  Point;

/* struct pour stocker une liste de points */
typedef struct plist {
    Point *p;
    struct plist *next;
} *plist;

/* struct pour representer un quadtree */
typedef struct quadtree {
    struct quadtree *haut_g, *haut_d, *bas_g, *bas_d;
    int nbp;
    int taille_carre;
    Point sup_g;
    plist points;
} Quadtree;

/**
 * @brief fonction qui creer un tableau de liste de points avec les 
 *        points presents dans le tableau tab.
 * 
 * @param tab un tableau de struct point
 * @param Np entier decrivant le nombre de point
 * 
 * @return retourne un tableau de liste de points
*/
plist* init_cel_tab(Point* tab, int Np);

/**
 * @brief fonction qui initialise le tableau tab avec Np points
 *        aleatoire entre les coord (0, 0) et (taille, taille).
 * 
 * @param taille un entier qui definit la taille de la fenetre dans laquelle on 
 *               fait apparaitre les points (le max des coord)
 * @param tab un tableau de struct point
 * @param Np entier decrivant le nombre de point
*/
void init_ptab(int Np, int taille, Point* tab);

/**
 * @brief fonction qui alloue un noeud du quadtree en prenant les coords (x,y)
 *        du coin sup-gauche du carre qu'il represente et la taille (taille) de
 *        la fenetre.
 * 
 * @param taille un entier qui definit la taille de la fenetre dans laquelle on 
 *               fait apparaitre les points (le max des coord)
 * @param x un entier qui decrit la coord x du coin sup-gauche du carre que le quadtree represente
 * @param y un entier qui decrit la coord y du coin sup-gauche du carre que le quadtree represente
 * 
 * @return l'adresse d'une struct Quadtree ou null si l'allocation echoue
*/
Quadtree* alloue_quadtree(int taille, int x, int y);

/**
 * @brief fonction qui alloue et initialise tout les noeuds du quadtree sous la racine
 * 
 * @param taille un entier qui definit la taille de la fenetre dans laquelle on 
 *               fait apparaitre les points (le max des coord)
 * @param x un entier qui decrit la coord x du coin sup-gauche du carre que la racine du quadtree represente
 * @param y un entier qui decrit la coord y du coin sup-gauche du carre que la racine du quadtree represente
 * @param Q la racine du quadtree (le premier noeud)
 * @param hauteur un entier qui decrit la hauteur du quadtree
*/
void init_quadtree(int hauteur, Quadtree *Q, int x, int y, int taille);

/**
 * @brief fonction qui ajoute le point dont l'adresse est dans p, dans le quadtree
 * 
 * @param Q la racine du quadtree (le premier noeud)
 * @param p un noeud contenant un point
 * @param kp le nombre min de point autoriser dans un noeud du quadtree
 * @param Wmin la taille min d'un carre representé par un noeud du quadtree
*/
void insert_qt(Quadtree *Q, int kp, int Wmin, plist *p);

/**
 * @brief fonction qui effectue la purge d'un noeud du quadtree (cad qu'il fait descendre
 *        les points pour les conditions kp et Wmin soit respecter)
 * 
 * @param Q la racine du quadtree (le premier noeud)
 * @param kp le nombre min de point autoriser dans un noeud du quadtree
 * @param Wmin la taille min d'un carre representé par un noeud du quadtree
*/
void purge(Quadtree *Q, int Kp, int wmin);

/** 
 * @brief fonction qui affiche dans la fenetre les Np points de tab
 * 
 * @param tab un tableau de struct point
 * @param Np entier decrivant le nombre de point
*/
void affiche_points(Point* tab, int Np);

/**
 * @brief fonction qui affiche les carres ,differement si ils sont plein ou pas, 
 *        qui represente des noeuds du quadtree qui possede des points.
 * 
 * @param Q la racine du quadtree (le premier noeud)
 * @param kp le nombre min de point autoriser dans un noeud du quadtree
*/
void affiche_quadtree(Quadtree *Q, int kp);

/**
 * @brief fonction qui ajoute le point (x,y) a l'indice idx de tab
 * 
 * @param tab un tableau de struct point
 * @param taille un entier qui definit la taille maximum du tableau tab
 * @param x coord x du point a ajouter
 * @param y coord y du point a ajouter
 * @param idx l'indice dans le tableau où il faut ajouter le points
*/
void ajout_point_clic(int x, int y, Point* tab, int taille, int idx);

/**
 * @brief fonction qui libere l'espace alloué pour le quadtree.
 * 
 * @param Q la racine du quadtree (le premier noeud)
*/
void libere_quadtree(Quadtree* Q);

#endif