#define TAILLE_MAX 10000
#include "header.h"





char **ChargerText(int *n)
{
    char NameTexte[20];
    printf("ENTRER LE NOM DU FICHIER TEXTE (Example: test4.txt) : ");
    scanf("%s", NameTexte);

    char fileName = strcat("files\\", NameTexte);
    FILE *fichier = fopen(fileName, "r+");

    char **T = (char**)malloc(sizeof(char*));
    char chaine[TAILLE_MAX];
//  SI LE FICHIER N'EST PAS NUL ON LE CHARGE DANS UNE CHAINE DE CARACTERE
    if(fichier != NULL)
    {
        while(fgets(chaine, TAILLE_MAX, fichier))
        {
        }
        fclose(fichier);
    }
//  ON MET TOUS LES MOTS EN MAJUSCULE
    Majuscule(chaine);
    printf("\n");
    printf(chaine);
    printf("\n");
//  ON TRANSFORME LA CHAINE DE CARACTERE EN TABLEAU
    T = chaine_vers_tab(chaine, n);
    return T;
}
char **chaine_vers_tab(char chaine[], int *n)
{
    char **tab;
    int i;
//  ON CALCULE LE NOMBRE DE MOTS
    *n=nombre_espaces(chaine)+2;
//  ON FAIT L'ALLOCATION DYNAMIQUE DU TABLEAU
    tab=(char**)malloc((*n)*sizeof(char*));
    if(tab!=NULL){
        for(i=0; i<*n; i++){
            tab[i]=(char*)malloc(20*sizeof(char));
            if(tab[i]==NULL){
                exit(-1);
            }
        }
    }
    else{
        exit(-1);
    }
//  ON SEPARE LES MOTS
    int k;
    i=0;
    for(int j=0; j<*n-1; j++){
        k=0;
        while((chaine[i]!='\0') && (chaine[i]!='_')){
            tab[j][k]=chaine[i];
            k++;
            i++;
        }
        tab[j][k]='\0';
        i++;
    }
    tab[*n-1]="NULL";
    return tab;
}
int nombre_espaces(char chaine[])
{
//  CETTE FONCTION CALCULE LE NOMBRE D'ESPACE ET SUPPRIME EN MEME TEMPS TOUTE LA PONCTUATION
    int i=0;
    char *CH=NULL, a[]=" ,.:?!;";
    for(int j=0; j<7; j++){
        while(CH=strchr(chaine, a[j]) ){
            *CH='_';
            i++;
        }
    }
    return i;
}
void Trier_TAB_TERME(terme *TERME, int n)
{
// CETTE FONCTION TRIE LE TABLEAU DE TERME PAR ORDRE DECROISSANT EN FONCTION DES NOMBRES D'OCCURENCE
   int i, j, imin;
   terme aide;
   for(i=0; i <n; i++)
   {
       for(j=i; j<n; j++)
       {
           if(TERME[j].nb > TERME[i].nb){
                strcpy(aide.mot , TERME[j].mot);
                aide.nb = TERME[j].nb;
                strcpy(TERME[j].mot , TERME[i].mot);
                TERME[j].nb = TERME[i].nb;
                strcpy(TERME[i].mot , aide.mot);
                TERME[i].nb = aide.nb;
           }
       }

    }
}
void Suppresion_Article(terme *TERME, char *chaine)
{
//  CETTE FONCTION SUPPRIME UN TERME DONT LE MOT EST DONNER (CA PERMET DE SUPPRIMER LES ARTICLES)
    int i;
    for( i=0; TERME[i].nb; i++){
        while(strcmp(TERME[i].mot,chaine) == 0){
            for(int j=i; TERME[j-1].nb; j++){
                strcpy(TERME[j].mot, TERME[j+1].mot);
                TERME[j].nb = TERME[j+1].nb;
            }
        }
    }
}
void suppression(terme *TERME, int n)
{
//  CETTE FONCTION PERMET DE SUPPRIMER L'ENSEMBLE DES MOTS DE MOINS DE "N" CARACTERES
    int i;
    for( i=0; TERME[i].nb; i++){
        while(strlen(TERME[i].mot) < n){
            for(int j=i; TERME[j-1].nb; j++){
                strcpy(TERME[j].mot, TERME[j+1].mot);
                TERME[j].nb = TERME[j+1].nb;
            }
        }
    }
}
terme *comptage(char *TAB[], int n)
{
//  FONCTION POUR METTRE DANS UN NOUVEAU TABLEAU CHAQUE MOTS ET SON OCCURENCE
      terme *liste = (terme*)malloc(n*sizeof(terme));
      int i = 0;
      while(n)
      {
          strcpy(liste[i].mot, TAB[0]);
          liste[i].nb = Supprime_Occurence(TAB, &n, TAB[0]);
          i++;
      }
      return liste;
}
int Supprime_Occurence(char *TAB[], int *n, char *chaine)
{
//  FONCTION POUR SUPPRIMER UN MOT DANS UN TABLEAU ET CALCULE LE NOMBRE DE FOIS QU'IL EST SUPPRIMER
//  CE QUI SERA SON OCCURENCE
     int occ = 0;
     for(int i=0; i<*n; i++)
     {
         if(strcmp(TAB[i], chaine) == 0)
         {
              for(int j=i; j<*n-1; j++)
              {
                  TAB[j]=(char*)malloc((strlen(TAB[j+1])+1)*sizeof(char));
                  strcpy(TAB[j], TAB[j+1]);
              }
              (*n)--;
              occ++;
              i--;
         }
     }
     return occ;
}
void Ecrire_dans_le_fichier(terme *term, int n, FILE *fichier)
{
//  FONCTION POUR ECRIRE LES ELEMENTS DU TABLEAU DE TERME DANS DANS UN FICHIER
    fputs("MOT_______Nbr de Carac_______Frequence\n", fichier);
    for(int i=0; i<n; i++ )
    {
        fputs(term[i].mot , fichier);
        fputs("\t\t", fichier);
        fprintf(fichier, "%d", strlen(term[i].mot));
        fputs("\t\t", fichier);
        fprintf(fichier, "%d", term[i].nb);
        fputc('\n', fichier);
    }
    fclose(fichier);
}
//void Suppresion_Les_Articles(terme *TERME, char *A_Sup[])
//{
//    for(int i=0; i<(sizeof(A_Sup)/sizeof(A_Sup[1])); i++){
//        Suppresion_Article(TERME, A_Sup[i]);
//    }
//}
void Majuscule(char *chaine)
{
    for(int i=0; chaine[i] != '\0'; i++)
    {
        char b=chaine[i];
        chaine[i]=toupper(b);
    }
}
void afficher_Tab_TERME(terme *TERME, int n)
{
    printf("LES %d MOTS LES PLUS FREQUENTS DU TEXTE \n", n);
    printf("MOT____________NBR DE CARACT________FREQUENCE\n");
    for(int i=0; i <n ; i++)
    {
        printf("%s \t\t %d \t\t %d \n", TERME[i].mot, strlen(TERME[i].mot), TERME[i].nb);
    }
}
void Suppresion_Les_Articles(terme *TERME)
{
    char *ASup[] = {"LEUR","POUR","LES","DES","MAIS"
                    "PAR","QUI","AUX","","LES","PAS","DANS","DANS","à","UNE","SUR"};

    for(int i=0; i<(sizeof(ASup)/sizeof(ASup[1])); i++){
        Suppresion_Article(TERME, ASup[i]);
    }
}

