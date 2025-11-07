#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    // Test avec le fichier de validation étape 3
    printf("=== VALIDATION ÉTAPE 3 ===\n");
    printf("Chargement du graphe 'exemple_valid_step3.txt' :\n");
    t_list_adj grapheValidation = readGraph("exemple_valid_step3.txt");

    // Vérification Markov
    verifierGrapheMarkov(&grapheValidation);

    // Génération du fichier Mermaid
    const char *sortieMermaid = "validation_etape3.mmd";
    exportToMermaid(&grapheValidation, sortieMermaid);

    // Affichage du graphe pour vérification
    printf("\nStructure du graphe chargé :\n");
    displaylistadj(grapheValidation);

    printf("\n--- Fichier Mermaid genere : %s ---\n", sortieMermaid);

    return 0;
}

