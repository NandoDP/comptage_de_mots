#define TAILLE_MAX 15000
#include "modules.c"

int main()
{

    int repet = 1;
//  # ON CREE UN TABLEAU POUR Y METTRE TOUS LES MOTS
    while(repet == 1)
    {
        char **TAB = (char**)malloc(sizeof(char*));
        int x;
        TAB = ChargerText(&x);

//  # ON CREE UN TABLEAU DE TERME POUR Y METTRE CHAQUE MOTS AVEC SON OCCURANCE ENSUITE ON LE TRIE
        int a=x;
        terme *TERME;
        TERME = comptage(TAB, a);
        Trier_TAB_TERME(TERME, a);
//  # ON SUPPRIME TOUTES LES ARTICLES ET TOUS LES TERMES AVEC DES MOTS DE MOINS DE 3 CARACTERES

        Suppresion_Les_Articles(TERME);
        suppression(TERME, 4);

//  # ON ECRIT LES 20 MOTS LES PLUS RECCURENTS DANS UN NOUVEAU FICHIER

        afficher_Tab_TERME(TERME, 20);
        repet = 0;
        printf("POUR RECOMMENCER APPUYER SUR 1 : ");
        scanf("%d", &repet);
    }
    printf("MERCI !\n\n");
    return 0;
}

