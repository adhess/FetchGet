#include "structure.h"
#ifndef DIRECTORYFILE_H
#define DIRECTORYFILE_H

DirectoryFile* New_DirectoryFile();
void df_setNom(DirectoryFile* df, char* s);
void df_setType(DirectoryFile* df, FileOrDirectory type);
void df_affect_td(DirectoryFile* df, TabDirectory* td);
char* lastSlash(char *src);
int isUTF8(char c);
int isText(FILE* fichier);
int isFile(FILE* fichier);
void afficher_df(DirectoryFile* df,char* tabulation,int bl);
int isNotEPE(char* nom, char const * ext);
int isNotTEPE(char* nom, char const * ext);
int isNotNPE(char* nom, char const * ext);
int isNotNSP(char* nom, char const * ext);
int parcourir(FILE *fichier, DirectoryFile *df, char* search);
void df_agrandir(DirectoryFile* df);
void df_ajoutElmt(DirectoryFile* df, int a);

DirectoryFile* R_ajout_df(char* chemin,char const * ext, char* search, ModeFiltrage mode);

#endif // DIRECTORYFILE_H
