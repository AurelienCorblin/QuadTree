#include "quadtree.h"
#include <MLV/MLV_all.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


Quadtree* alloue_quadtree(int taille, int x, int y) {
    Quadtree *tmp = (Quadtree*) malloc(sizeof(Quadtree));
    if (tmp == NULL)
        return NULL;
    tmp->bas_d = NULL;
    tmp->bas_g = NULL;
    tmp->haut_d = NULL;
    tmp->haut_g = NULL;
    tmp->nbp = 0;
    tmp->points = NULL;
    tmp->sup_g.x = x;
    tmp->sup_g.y = y;
    tmp->taille_carre = taille;
    return tmp;
}


void init_quadtree(int hauteur, Quadtree *Q, int x, int y, int taille) {
    if (hauteur == 0)
        return;
    taille = taille / 2;

    /* allocation des quatres fils */
    Q->haut_g = alloue_quadtree(taille, x, y);
    Q->bas_g = alloue_quadtree(taille, x, y + taille);
    Q->haut_d = alloue_quadtree(taille, x + taille, y);
    Q->bas_d = alloue_quadtree(taille, x + taille, y + taille);

    /* appelle recursive pour allouer les noeuds jusqu'au plus petit */
    init_quadtree(hauteur - 1, Q->haut_g, x, y, taille);
    init_quadtree(hauteur - 1, Q->bas_g, x, y + taille, taille);
    init_quadtree(hauteur - 1, Q->haut_d, x + taille, y, taille);
    init_quadtree(hauteur - 1, Q->bas_d, x + taille, y + taille, taille);
}


void insert_qt(Quadtree *Q, int Kp, int wmin, plist *p) {
    if (Q->nbp <= Kp || Q->taille_carre == wmin) {
        (*p)->next = Q->points;
        Q->points = *p;
        Q->nbp++;
        if (Q->nbp > Kp) // purge si on depasse le nb de points min dans un noeud
            purge(Q, Kp, wmin);
    }
    else if (Q->nbp > Kp && Q->points == NULL) {
        // ajoute dans le bon fils
        if ((*p)->p->x <= Q->sup_g.x + Q->taille_carre / 2) {
            if ((*p)->p->y <= Q->sup_g.y + Q->taille_carre / 2) {
                insert_qt(Q->haut_g, Kp, wmin, p);
            }
            else {
                insert_qt(Q->bas_g, Kp, wmin, p);
            }
        }
        else {
            if ((*p)->p->y <= Q->sup_g.y + Q->taille_carre / 2) {
                insert_qt(Q->haut_d, Kp, wmin, p);
            }
            else {
                insert_qt(Q->bas_d, Kp, wmin, p);
            }
        }
        Q->nbp++;
    }
}

void purge(Quadtree *Q, int Kp, int wmin) {
    if (Q->nbp <= Kp || Q->taille_carre <= wmin)
        return;
    plist current = Q->points;
    Q->points = NULL;
    Q->nbp = 0;
    // redistribue les points dans les fils
    while (current != NULL) {
        plist next = current->next;
        Point *p = current->p;
        // definit le fils ou ajouter le point
        if (p->x <= Q->sup_g.x + Q->taille_carre / 2) {
            if (p->y <= Q->sup_g.y + Q->taille_carre / 2) {
                insert_qt(Q->haut_g, Kp, wmin, &current);
            } else {
                insert_qt(Q->bas_g, Kp, wmin, &current);
            }
        } else {
            if (p->y <= Q->sup_g.y + Q->taille_carre / 2) {
                insert_qt(Q->haut_d, Kp, wmin, &current);
            } else {
                insert_qt(Q->bas_d, Kp, wmin, &current);
            }
        }
        current = next;
        Q->nbp++;
    }
}


plist* init_cel_tab(Point* tab, int Np) {
    plist* lst = (plist*) malloc(sizeof(plist) * Np);
    if (lst == NULL) {
        fprintf(stderr, "erreur d'allocation de l'interface\n");
        return NULL;
    }
    for (int i = 0; i < Np; ++i) {
        lst[i] = (plist) malloc(sizeof(struct plist));
        lst[i]->next = NULL;
        lst[i]->p = &tab[i];
    }
    return lst;
}

void ajout_point_clic(int x, int y, Point* tab, int taille, int idx){
    if (idx >= taille)
        return;
    tab[idx].x = x;
    tab[idx].y = y;
}

void init_ptab(int Np, int taille, Point* tab) {
    for (int i = 0; i < Np; ++i) {
        tab[i].x = rand() % taille;
        tab[i].y = rand() % taille;
    }
}

void affiche_points(Point* tab, int Np) {
    for (int i = 0; i < Np; ++i) {
        MLV_draw_filled_circle(tab[i].x, tab[i].y, 2, MLV_COLOR_RED);
    }
}

void affiche_quadtree(Quadtree *Q, int kp) {
    if (Q == NULL || Q->nbp == 0)
        return;

    if (Q->points) {
        if (Q->nbp == kp) { // couleur diff si le noeud est plein
            MLV_draw_filled_rectangle(Q->sup_g.x, Q->sup_g.y, Q->taille_carre, Q->taille_carre, MLV_COLOR_PINK);
            MLV_draw_rectangle(Q->sup_g.x, Q->sup_g.y, Q->taille_carre, Q->taille_carre, MLV_COLOR_BLACK);
        }
        else {
            MLV_draw_filled_rectangle(Q->sup_g.x, Q->sup_g.y, Q->taille_carre, Q->taille_carre, MLV_COLOR_GREY);
            MLV_draw_rectangle(Q->sup_g.x, Q->sup_g.y, Q->taille_carre, Q->taille_carre, MLV_COLOR_BLACK);
        }
    }   
    affiche_quadtree(Q->haut_g, kp);
    affiche_quadtree(Q->haut_d, kp);
    affiche_quadtree(Q->bas_g, kp);
    affiche_quadtree(Q->bas_d, kp);
}

void libere_quadtree(Quadtree* Q) {
    if (Q == NULL)
        return;
    
    libere_quadtree(Q->bas_d);
    libere_quadtree(Q->bas_g);
    libere_quadtree(Q->haut_d);
    libere_quadtree(Q->haut_g);

    free(Q);
    Q = NULL;
}