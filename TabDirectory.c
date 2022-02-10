#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "DirectoryFile.h"

// retourner et initialiser un objet de type TabDirectory
TabDirectory* New_TabDirectory()
{
    TabDirectory* td = malloc(sizeof(TabDirectory));
    td -> size = 10;
    td -> fin = 0;
    td -> df = malloc(td -> size*sizeof(DirectoryFile));
    return td;
}
// afficher le contenue de cette structure TabDirectory
void td_afficher(TabDirectory* td)
{
    int i;
    for(i = 0; i < td -> fin; i++)
    {
        printf("size = %d, fin = %d, df = %p, nom = %s, type = %d\n",
               td -> size, td -> fin, td -> df, td -> df[i].nom, td -> df[i].type );
    }
}
// agrandir le tableau contenant DirectoryFile
void td_agrandir(TabDirectory* td)
{
    if(td -> fin >= td -> size)
    {
        td -> size *= 2;
        td -> df = realloc(td -> df,td -> size*sizeof(DirectoryFile));
    }
}
// ajouter un element a notre tableau
void td_ajoutElmt(TabDirectory* td, DirectoryFile* df)
{
    td -> df[td -> fin] = *df;
    td -> fin++;
    td_agrandir(td);
}
// affecter le lien d'association
void td_affect_df(TabDirectory* td, DirectoryFile* df)
{
    td -> pointe = df;
}

// afficher le contenue de notre structure d'une maniere reccursive
void afficher_td(TabDirectory* td,char *str)
{
    int i;
    for(i = 0; i< td -> fin; i++)
    {

        if(td -> fin - 1 == i )
        {
            afficher_df(&td -> df[i],str,0);
        }
        else
        {
            afficher_df(&td -> df[i],str,1);
        }
    }
}


// remplir notre structure d'une façon reccursive.
TabDirectory* R_ajout_td(DirectoryFile* df, char* chemin, char const * ext,char* search, ModeFiltrage mode)
{
    TabDirectory* td = New_TabDirectory();
    td_affect_df(td, df);

    DIR* rep = opendir(chemin);

    if (rep != NULL)
    {
        struct dirent *fichierLu;
        while ((fichierLu = readdir(rep)) != NULL)
        {
            if( strcmp(fichierLu->d_name, ".") != 0 && strcmp(fichierLu->d_name, "..") != 0)
            {
                char str[500];
                strcpy(str,chemin);
                strcat(str,"\\");
                strcat(str,fichierLu->d_name);

                DirectoryFile* df = R_ajout_df(str,ext,search,mode);

                if(df != NULL)
                    td_ajoutElmt(td, df);
            }
        }
    }

    return td;
}

