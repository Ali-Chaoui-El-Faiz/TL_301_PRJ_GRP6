#ifndef __UTILS_H__
#define __UTILS_H__

// partie 1
typedef  struct s_cell {
    int arr; // sommet d'arrive
    float prob; // probabilite
    struct s_cell *next; // prochaine cell
} t_cell;

typedef struct s_list {
    t_cell *head;
} t_list;
typedef struct s_list_adj {
    int n;
    t_list *tab;
} t_list_adj;

// Partie 2
void verifierGrapheMarkov(t_list_adj *graphe);



t_cell *createcell(int som, float prob);
t_list createemptylist();
void addcell(t_list *list, int som, float prob);
void displaylistadj (t_list_adj list);
void displaylist(t_list list);
t_list_adj createlistadj(int n);
t_list_adj readGraph(const char *filename);
void exportToMermaid(t_list_adj *graphe, const char *filename);

#endif