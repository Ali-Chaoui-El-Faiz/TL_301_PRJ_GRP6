#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    t_list_adj monGraphe;
    printf("Chargement du graphe 'exemple1.txt' :\n");
    monGraphe = readGraph("../exemple1.txt");
    verifierGrapheMarkov(&monGraphe);

    printf("\n-------------------------------------------------------\n");

    printf("\nChargement du graphe 'exemple_erreur.txt'...\n");
    // ici on a créee un fichier exemple_erreur.txt qui contient les meme valeurs que exemple1.txt mais où nous avons changer 0.2 par 0.1
    t_list_adj grapheErreur = readGraph("../exemple_erreur.txt");
    verifierGrapheMarkov(&grapheErreur);

    const char *sortieMermaid = "../graphe.mmd";
    exportToMermaid(&monGraphe, sortieMermaid);

    printf("\n--- Fin du programme ---\n");
    return 0;
}

