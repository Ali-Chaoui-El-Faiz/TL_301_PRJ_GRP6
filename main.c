#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "vertex.h"
#include "hasse.h"

int main() {
    const char *filename = "graphe10.txt";

    printf("=== PROJET GRAPHES DE MARKOV ===\n\n");

    // ETAPE 1 : Chargement du graphe

    printf("--- Chargement du graphe depuis '%s' ---\n", filename);
    t_list_adj graphe = readGraph(filename);
    displaylistadj(graphe);

    // Vérification si c'est bien un graphe de Markov (Partie 1)
    verifierGrapheMarkov(&graphe);

    // Export du graphe initial (Partie 1)
    exportToMermaid(&graphe, "graphe_initial.mmd");


    // ETAPE 2 : Algorithme de Tarjan (Création des classes)

    printf("\n--- Algorithme de Tarjan (Recherche des classes) ---\n");

    t_partition p;
    // Appel de la fonction Tarjan (qui remplit la partition 'p')
    tarjan(&graphe, &p);

    // Affichage des classes trouvées
    afficher_partition(&p);


    // ETAPE 3 : Diagramme de Hasse et Propriétés

    printf("\n--- Construction du Diagramme de Hasse ---\n");

    // 1. Création des liens entre les classes
    t_link_array liens = createLinkArray(&p, &graphe);
    printf("Nombre de liens trouves (brut) : %d\n", liens.log_size);

    // 2. Suppression des liens transitifs
    removeTransitiveLinks(&liens);
    printf("Nombre de liens apres simplification : %d\n", liens.log_size);

    // 3. Export en Mermaid pour visualiser les classes
    exportHasseMermaid(&p, &liens, "diagramme_hasse.mmd");

    // 4. Affichage des propriétés (Transitoire, Persistante, Absorbant, Irréductible)
    printGraphProperties(&p, &liens);


    freeLinkArray(&liens);
    free_partition(&p);

    printf("\n=== Fin du programme ===\n");
    return 0;
}