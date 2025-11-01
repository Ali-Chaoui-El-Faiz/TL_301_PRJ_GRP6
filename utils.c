#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
// partie 1
t_cell *createcell(int som, float prob) {
    t_cell *cell = (t_cell*)malloc(sizeof(t_cell));
    cell->prob = prob;
    cell->arr  = som;
    cell->next = NULL;
    return cell;
}
t_list createemptylist() {
    t_list newlist;
    newlist.head = NULL;
    return newlist;

}
void addcell(t_list *list, int som, float prob) {
    t_cell *c = createcell(som, prob);   // alloue dynamiquement
    c->next = list->head;
    list->head = c;
}
t_list_adj createlistadj(int n) {
    t_list_adj new_adj;
    new_adj.n = n;
    new_adj.tab = (t_list*)malloc(n * sizeof(t_list));
    for (int i = 0; i < n; i++) new_adj.tab[i] = createemptylist();
    return new_adj;
}
void displaylist(t_list list) {
    t_cell *cell;
    cell = list.head;
    printf("[head @] ->\n");
    while (cell != NULL) {
        printf(" (%d,%.2f) @->",cell->arr,cell->prob);
        cell = cell->next;
    }
    printf("\n");
}
void displaylistadj (t_list_adj list) {
    for (int i = 0; i < list.n; i++) {
        printf("Liste pour le sommet %d:",i+1);
        displaylist(list.tab[i]);
    }
}

t_list_adj readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt"); // read-only, text
    int nbvert, depart, arrivee;
    float proba;
    t_list_adj list_adj;

    if (file==NULL)
    {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    // first line contains number of vertices
    if (fscanf(file, "%d", &nbvert) != 1)
    {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    list_adj = createlistadj(nbvert);
    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3)
    {
        // on obtient, pour chaque ligne du fichier les valeurs
        // depart, arrivee, et proba
        addcell(&list_adj.tab[depart - 1], arrivee, proba);

    }
    fclose(file);
    return list_adj;
}


static char *getID(int i)
{
    // translate from 1,2,3, .. ,500+ to A,B,C,..,Z,AA,AB,...
    static char buffer[10];
    char temp[10];
    int index = 0;

    i--; // Adjust to 0-based index
    while (i >= 0)
    {
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }

    // Reverse the string to get the correct order
    for (int j = 0; j < index; j++)
    {
        buffer[j] = temp[index - j - 1];
    }
    buffer[index] = '\0';

    return buffer;
}


// Partie 2 ; Vérification du graphe de Markov
// Ici on cherche à voir si la somme des probas sortantes de chaque sommet est compris entre 0.99 et 1

void verifierGrapheMarkov(t_list_adj *graphe) {

    int erreurTrouvee = 0;

    printf("\n--- Verification du graphe de Markov... ---\n");

    // On parcourt chaque sommet
    for (int i = 0; i < graphe->n; i++) {

        float somme = 0.0;
        t_cell *courant = graphe->tab[i].head; // ptr pour parcourir la liste

        // On parcourt la liste chainee de ce sommet en additionnant la proba à chaque fois
        while (courant != NULL) {
            somme += courant->prob;
            courant = courant->next;
        }

        // On vérifie la somme pour le sommet i
        if (somme < 0.99 || somme > 1.0) {
            printf(" Erreur : la somme des probabilites du sommet %d est %.2f\n", i + 1, somme);
            erreurTrouvee = 1;
        }
    }

    if (erreurTrouvee) {
        printf("--- Le graphe n'est pas un graphe de Markov ---\n");
    } else {
        printf("OK...\n");
        printf("--- Le graphe est un graphe de Markov ---\n");
    }
}