#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DirectoryFile.h"
#include "TabDirectory.h"
#include "color.h"
// retourner et initialiser un objet de type DirectoryFile
DirectoryFile* New_DirectoryFile()
{
    DirectoryFile *df = malloc(sizeof(DirectoryFile));
    df -> size = 10;
    df -> fin = 0;
    df -> positions = malloc(df -> size*sizeof(int));
    return df;
}
// agrandir le tableau des positions s'il est plain
void df_agrandir(DirectoryFile* df)
{
    if(df -> fin >= df -> size)
    {
        df -> size *= 2;
        df -> positions = realloc(df -> positions,df -> size*sizeof(int));
    }
}
// ajouter un element a notre tableau de positions
void df_ajoutElmt(DirectoryFile* df, int a)
{
    df -> positions[df -> fin] = a;
    df -> fin++;
    df_agrandir(df);
}
// affecter le nom
void df_setNom(DirectoryFile* df, char* s)
{
    strcpy(df -> nom,s);
}
// affecter le type
void df_setType(DirectoryFile* df, FileOrDirectory type)
{
    df -> type = type;
}
// affecter TabDirectory
void df_affect_td(DirectoryFile* df, TabDirectory* td)
{
    df -> td = td;
}

// retourn 1 si le fichier n'a pas une extension correcte
// sinon  0
int isNotEPE(char* nom, char const * ext)
{
    int ln = strlen(nom)-1;
    int ls = strlen(ext)-1;
    while(ext[ls] != '.' && ext[ls] == nom[ln])
    {
        ls--;
        ln--;
    }
    if(ext[ls] == '.' && ext[ls--] == nom[ln--])
        return 0;
    return 1;
}

// retourn 1 si le fichier n'a pas la forme truc*.extension
// sinon  0
int isNotTEPE(char* nom, char const * ext)
{
    int i = 0;
    int ln = strlen(nom)-1;
    int ls = strlen(ext)-1;
    while(ext[ls] != '.' && ext[ls] == nom[ln])
    {
        ls--;
        ln--;
    }
    if(ext[ls] == '.' && ext[ls--] == nom[ln--])
    {
        for (; ext[i] != '*'; ++i)
        {
            if(ext[i] != nom[i])
                return 1;
        }
        return 0;
    }
    return 1;
}
// retourn 1 si le fichier n'a pas la forme nom.extension
// sinon  0
int isNotNPE(char* nom, char const * ext)
{
    int i = 0;
    int ln = strlen(nom)-1;
    int ls = strlen(ext)-1;
    while(ext[ls] != '.' && ext[ls] == nom[ln])
    {
        ls--;
        ln--;
    }
    if(ext[ls] == '.' && ext[ls--] == nom[ln--])
    {
        for (; ext[i] != '.'; ++i)
        {
            if(ext[i] != nom[i])
                return 1;
        }
        return 0;
    }
    return 1;
}
// retourn 1 si le fichier ne commence pas par nom
// sinon  0
int isNotNSP(char* nom, char const * ext)
{
    int i = 0;
    if(strlen(nom) < strlen(ext))
        return 1;
    for (; i < strlen(ext); ++i)
    {
        if(ext[i] != nom[i])
            return 1;
    }
    return 0;
}
// une sorte d'affichage reccursive a notre structure
void afficher_df(DirectoryFile* df,char* tab,int bl)
{
    printf("%s_____", tab);
    switch(df -> type)
    {
    case Directory:
        Color(6, 0) ;
        break;
    case File:
        Color(4,0);
        break;
    case TextFile:
        Color(3,0);
        break;
    }
    printf("%s",df -> nom);
    normalColor();
    int i = 0;
    char st[500];

    strcpy(st,tab);
    if(!bl)
        st[strlen(st)-1] = ' ';
    strcat(st, "     |");
    if(df -> fin != 0)
    {
        Color(12, 0) ;
        printf("  :\t");
        for (i = 0; i < df -> fin-1; ++i)
        {
            printf("%d, ",df -> positions[i]);
        }
        printf("%d\n",df -> positions[i]);
        normalColor();
    }
    else
        printf("\n");
    if(df -> type ==  Directory)
    {
        //printf("\n");
        afficher_td(df -> td,st);
    }

}

// retourner la chaine de caractere qui suit la derniere '/'
char* lastSlash(char *src)
{
    char* dest = malloc (sizeof (char) * 500);
    int j,i;
    for(i = strlen(src)-1; i >= 0 ; i--)
    {
        if(src[i] == '\\')
            break;

    }
    for(j = 0; j < strlen(src) - i ; j++)
    {
        dest[j] = src[i+j+1];
    }
    dest[j] = '\0';
    return dest;
}
// verifier si une fichier comporte bien et belle des caractere UTF8
int isText(FILE* fichier)
{
    if(fichier != NULL)
    {

        int i = 0,isUtf8 = 1;
        char c;
        for(i = 0; i< 100 && isUtf8; i++)
        {
            c = fgetc(fichier);
            if((int)c != -1)
            {
                isUtf8 = isUTF8(c);
                if(isUtf8 == 0)
                {
                    return 0;
                }
            }
            else
                break;
        }
        return 1;
    }
    return 0;
}
// verifier si un caractere est un UTF8
int isUTF8(char c)
{
    int i,sizet = 98;
    char* t = " \n\t\r!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    for(i = 0; i< sizet; i++)
    {
        if(c == t[i])
            return 1;
    }
    return 0;
}
// verivier si cette fichier represente belle et bien une fichier
int isFile(FILE* fichier)
{
    if(fichier == NULL)
        return 0;
    fclose(fichier);
    return 1;
}


// parcourir une fichier a la recherche des cette chaine de caractere "search"
// et marquer la position de chaque retrouvaille.
int parcourir(FILE *fichier, DirectoryFile *df, char* search)
{
    int bool = 0;
    rewind(fichier);
    char chk[500];
    char c;
    int i = 0;
    int j = 0;
    for (; i < strlen(search); ++i)
    {
        c = fgetc(fichier);
        if((int)c == -1)
            break;
        chk[i] = c;
    }
    chk[i] = '\0';
    i = 0;
    if(strcmp(chk,search) == 0)
    {
        df_ajoutElmt(df,i);
        bool = 1;
    }
    while((c = fgetc(fichier)) != -1)
    {
        i++;
        for (j = 1; j < strlen(chk); ++j)
        {
            chk[j-1] = chk[j];
        }
        chk[j-1] = c;
        if(strcmp(chk,search) == 0)
        {
            df_ajoutElmt(df,i);
            bool = 1;
        }
    }
    fclose(fichier);
    return bool;
}


// remplir notre structure
DirectoryFile* R_ajout_df(char* chemin,char const * ext, char* search, ModeFiltrage mode)
{
    char* nom = lastSlash(chemin);
    switch(mode)
    {
    case SansFiltrage:
        break;
    case EPE:
        if(isFile(fopen(chemin,"r")) && isNotEPE(nom,ext))
            return NULL;
        break;
    case NSE:
        if(isFile(fopen(chemin,"r")) && isNotNSP(nom,ext))
            return NULL;
        break;
    case TEPE:
        if(isFile(fopen(chemin,"r")) && isNotTEPE(nom,ext))
            return NULL;
        break;
    case NPE:
        if(isFile(fopen(chemin,"r")) && isNotNPE(nom,ext))
            return NULL;
        break;
    }

    DirectoryFile* df = New_DirectoryFile();
    df_setNom(df, nom);

    if (isFile(fopen(chemin,"r")))
    {
        FILE *fichier = fopen(chemin,"r");
        isText(fichier)? df_setType(df,TextFile):df_setType(df,File);
        fclose(fichier);

        if(strcmp(search,""))
        {
            FILE *fichier = fopen(chemin,"r");
            if(isText(fichier))
            {
                //df_setType(df,TextFile);
                if(!parcourir(fichier,df,search))
                    return NULL;

            }
            else
                return NULL;

        }

        df_affect_td(df, NULL);
    }
    else
    {
        TabDirectory* td = R_ajout_td(df,chemin,ext,search,mode);
        if(strcmp(ext,"") != 0 && td -> fin == 0)
            return NULL;
        df_setType(df,Directory);
        df_affect_td(df, td);
    }


    return df;
}

