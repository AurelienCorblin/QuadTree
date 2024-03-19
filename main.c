#define _DEFAULT_SOURCE
#include "quadtree.h"
#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


/*fonction qui renvoie 0 si la chaine de caractere c n'est pas un entier
  sinon elle renvoie 1*/
int isnumber(char* c){
    int i = 0;
    size_t len = strlen(c); /*recupere la longueur de c*/
    /*verifie pour chaque caractere de la chaine si c'est un entier*/
    for(; i < len; ++i){
        if(!isdigit(c[i]))
            return 0;
    }
    return 1;
}


int main(int argc, char **argv) {
    srand(time(NULL));
    int w = 512;
    int Np = 200;
    int kp = 3;
    int Wmin = 4;
    int mode_souris = 0;

    MLV_Keyboard_button touche;
    
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-s") == 0)
            mode_souris = 1;
        else if (strcmp(argv[i], "-w") == 0 && argc > ++i && isnumber(argv[i])) {
            w = atoi(argv[i]);
            if (w % 2 != 0) {
                printf("la taille de la fenetre n'est pas valide (puissance de 2)");
                return 0;
            }
        }
        else if (strcmp(argv[i], "-n") == 0 && argc > ++i && isnumber(argv[i]))
            Np = atoi(argv[i]);
        else if (strcmp(argv[i], "-k") == 0 && argc > ++i && isnumber(argv[i]))
            kp = atoi(argv[i]);
        else if (strcmp(argv[i], "-m") == 0 && argc > ++i && isnumber(argv[i])) {
            Wmin = atoi(argv[i]);
            if (Wmin % 2 != 0 && Wmin != 1) {
                printf("la taille minimum n'est pas valide (puissance de 2)");
                return 0;
            }
        }
        else {
            printf("les arguments ne sont pas bon \n");
            return 0;
        }
    }

    MLV_create_window("QUADTREE", "QUADTREE", w, w);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_actualise_window();

    // initialisation du quadtree
    Quadtree* Q = alloue_quadtree(w, 0, 0);
    init_quadtree(log2(w), Q, 0, 0, w);

    // initialisation du tableau de point
    Point* tab = (Point*) malloc(sizeof(Point) * Np);
    if (tab == NULL) {
        fprintf(stderr, "erreur d'allocation du tableau de points\n");
        return 0;
    }
    // initialisation du tableau de liste de point
    plist* lst = init_cel_tab(tab, Np);

    // distribution a la souris
    if (mode_souris) {
        int cpt = 0;
        int x, y;
        while (cpt < Np) {
            MLV_wait_mouse(&x, &y);
            ajout_point_clic(x, y, tab, Np, cpt);
            insert_qt(Q, kp, Wmin, &lst[cpt]);
            MLV_clear_window(MLV_COLOR_WHITE);
            affiche_quadtree(Q, kp);
            affiche_points(tab, Np);
            MLV_actualise_window();
            cpt++;
        }
    }

    // distribution aleatoire
    else {
        // avec animation si moins de 500 points
        if (Np < 500) {
            while(MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == MLV_NONE || touche != 13);
            for (int i = 0; i < Np; ++i) {
                tab[i].x = rand() % w;
                tab[i].y = rand() % w;
                insert_qt(Q, kp, Wmin, &lst[i]);
                MLV_clear_window(MLV_COLOR_WHITE);
                affiche_quadtree(Q, kp);
                affiche_points(tab, Np);
                MLV_actualise_window();
                usleep(50000);
            }
        }
        // sans animation 
        else {
            while(MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == MLV_NONE || touche != 13);
            init_ptab(Np, w, tab);
            for (int i = 0; i < Np; ++i) {
                insert_qt(Q, kp, Wmin, &lst[i]);
            }
            
            affiche_quadtree(Q, kp);
            affiche_points(tab, Np);
            MLV_actualise_window();
        }
    }    

    // appuie sur 'q' pour free tout l'espace et quitter l'application
    while(MLV_get_event(&touche, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == MLV_NONE || touche != 'q');
    MLV_free_window();
    free(tab);
    for (int i = 0; i < Np; ++i)
        free(lst[i]);
    free(lst);
    libere_quadtree(Q);
}