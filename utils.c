#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
// partie 1
t_cell createcell(int som,float prob) {
    t_cell cell;
    cell.prob = prob;
    cell.arr = som;
    cell.next = NULL;
    return cell;
}
t_list createemptylist() {
    t_list newlist;
    newlist.head = NULL;
    return newlist;

}
void addcell(t_list *list, t_cell cell) {
    list->head = &cell;
}
t_list_adj createlistadj(const int n) {
    t_list_adj new;
    new.n = n;
    new.tab = (t_list*)malloc(n * sizeof(t_list));
    for (int i = 0; i < n; i++) {
        new.tab[i] = createemptylist();
    }
    return new;
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
    list_adj = createemptylist(nbvert);
    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3)
    {
        // on obtient, pour chaque ligne du fichier les valeurs
        // depart, arrivee, et proba

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
