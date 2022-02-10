#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include "TabDirectory.h"
#include "DirectoryFile.h"
#include "structure.h"

ModeFiltrage numFiltre(char const * str);
void extract(char* chemin,char *ext,char const *arg);
int noSlash(char const *arg);


int main(int argc, char const *argv[])
{
    if(argc == 1)
    {
        DirectoryFile* df = R_ajout_df(".\\","", "", SansFiltrage);
        afficher_df(df,"",0);
    }
    else if(argc == 2)
    {
        char chemin[500], ext[500];
        extract(chemin,ext,argv[1]);
        DirectoryFile * df = NULL;

        switch(numFiltre(ext))
        {
        case SansFiltrage:
            break;
        case EPE :
        {
            df = R_ajout_df(chemin, ext,"", EPE);
        }
        break;
        case NSE:
        {
            df = R_ajout_df(chemin, ext,"", NSE);
        }
        break;
        case TEPE:
        {
            df = R_ajout_df(chemin, ext,"", TEPE);
        }
        break;
        case NPE:
        {
            df = R_ajout_df(chemin, ext,"", NPE);
        }
        break;
        }
        if(df != NULL)
            afficher_df(df,"",0);

    }
    else
    {

        char chemin[500], ext[500],search[500];
        extract(chemin,ext,argv[1]);
        DirectoryFile * df = NULL;
        strcpy(search,"");
        int i = 2;
        for (; i < argc; ++i)
        {
            strcat(search,argv[i]);
            strcat(search," ");
        }
        search[strlen(search)-1] = '\0';

        switch(numFiltre(ext))
        {
        case SansFiltrage:
            break;
        case EPE:
        {
            df = R_ajout_df(chemin, ext,search, EPE);
        }
        break;
        case NSE:
        {
            df = R_ajout_df(chemin, ext,search, NSE);
        }
        break;
        case TEPE:
        {
            df = R_ajout_df(chemin, ext,search, TEPE);
        }
        break;
        case NPE:
        {
            df = R_ajout_df(chemin, ext,search, NPE);
        }
        break;
        }
        if(df != NULL)
            afficher_df(df,"",0);

    }
    return 0;
}
/*
 * choisir la methode du filtrage
 */

ModeFiltrage numFiltre(char const * str)
{
    // si votre commande est sous la forme " *.extension "
    if(str[0] == '*' && str[1] == '.')
        return EPE;

    int i,containPoint = 0,containEtoile = 0;
    for (i = 0; i < strlen(str); ++i)
    {
        if(str[i] == '.')
            containPoint = 1;
        if(str[i] == '*')
            containEtoile = 1;
    }
    // si votre commande est sous la forme " nom_de_fichier "
    if(!containPoint)
        return NSE;
    // si votre commande est sous la forme " truc*.extension "
    if(containPoint && containEtoile)
        return TEPE;
    // si votre commande est sous la forme " nom_de_fichier.extension "
    return NPE;
}

/**
  * retourne 0 s'il existe le caractere '/' dans arg
  * sinon 1
  */
int noSlash(char const *arg)
{
    int i = 0;
    for (; i < strlen(arg); ++i)
    {
        if(arg[i] == '/')
            return 0;
    }
    return 1;
}

/**
  * suivant arg separé le chemin et la methode du filtrage
  */
void extract(char* chemin,char *ext,char const *arg)
{
    if(noSlash(arg))
    {
        strcpy(chemin,".\\");
        strcpy(ext,arg);
    }
    else
    {
        if(arg[0] == '/')
        {
            int i = 1;
            strcpy(chemin,"C:\\");
            for (; i < strlen(arg); ++i)
            {
                ext[i-1] = arg[i];
            }
            ext[i-1] = '\0';
        }
        else
        {
            int i = 2,l;
            strcpy(chemin,".\\");
            for (; arg[i-2] != '/'; ++i)
            {
                chemin[i] = arg[i-2];
            }
            chemin[i++] = '\0';
            l = i-2;
            for (; l < strlen(arg); ++l)
            {
                ext[l-i+2] = arg[l];
            }
            ext[l-i+2] = '\0';
        }
    }
}
