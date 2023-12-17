#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct terme terme;
struct terme
{
    char mot[255];
    int nb
};

typedef struct LISTE LISTE;
struct LISTE
{
    terme *premier;
};

char **ChargerText(int *n);
void suppression(terme *TERME, int n);
terme *comptage(char *TAB[], int n);
void afficher_Tab_TERME(terme *TERME, int n);
void Trier_TAB_TERME(terme *TERME, int n);
void Suppresion_Article(terme *TERME, char *chaine);
//void Ecrire_dans_le_fichier(terme *term, int n, FILE *fichier);
void Suppresion_Les_Articles(terme *TERME);
void Majuscule(char *chaine);
int Supprime_Occurence(char *TAB[], int *n, char *chaine);
int nombre_espaces(char chaine[]);
char **chaine_vers_tab(char chaine[], int *n);

