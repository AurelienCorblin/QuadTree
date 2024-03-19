Corblin Aurelien 
Devillez Adrien 

compilation: 
    il faut ouvrir un terminal dans le fichier contenant le makefile et taper la commande make.

utilisation:
    si vous lancez le programme sans argument le programme se lance avec des valeurs par default ou la taille de 
    la fenetre est 512x512 , avec 200 points ,un minimum de 3 points par noeud et des carres de taille minimum 4x4.

    sinon pour pour les options :
        -s active la distribution des points a la souris
        -w suivi d'un entier (different de 1 car aucun sens) definit la taille de la fenetre (wxw). 
           doit etre une puissance de 2
        -n suivi d'un entier definit le nombre de points que le programme ou l'utilisateur vont devoir distribuer
        -k suivi d'un entier definit le nombre de point minimum dans un carre, doit etre une puissance de 2.
        -m suivi d'un entier definit la taille minimum d'un carre.

    les options peuvent etre mises dans n'importe quelle ordre tant qu'elle sont bien mise (donc sans oublier l'entier 
    apres les options qui en ont besoin)

    une fois tout les points placer vous devez appuyer sur 'q' pour quitter l'appplication

visuel :
    un carre violet veut dire que le carre a atteint sa limite de point. 