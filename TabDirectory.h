#include "structure.h"
#ifndef TABDIRECTORY_H
#define TABDIRECTORY_H

TabDirectory* New_TabDirectory();
void td_afficher(TabDirectory* td);
void td_ajoutElmt(TabDirectory* td, DirectoryFile* df);
void td_agrandir(TabDirectory* td);
void td_affect_df(TabDirectory* td, DirectoryFile* df);
void afficher_td(TabDirectory* td,char *str);

TabDirectory* R_ajout_td(DirectoryFile* df, char* chemin, char const * ext,char* search, ModeFiltrage mode);
#endif // TABDIRECTORY_H
