#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct DirectoryFile DirectoryFile;

typedef struct TabDirectory TabDirectory;

typedef enum{Directory = 0, File = 1, TextFile = 2} FileOrDirectory;

typedef enum ModeFiltrage ModeFiltrage;
enum ModeFiltrage
{
    SansFiltrage = 0, EPE = 1, NSE = 2, TEPE = 3, NPE = 4
};
// EPE = *.extension
// NSE = nom_de_fichier
// TEPE = truc*.extension
// NPE = nom_de_fichier.extension

struct TabDirectory
{
    int final;
    int size;
    int fin;
    DirectoryFile* df;
    DirectoryFile* pointe;
};

struct DirectoryFile
{
    char nom[500];
    FileOrDirectory type;
    TabDirectory* td;
    int size;
    int fin;
    int *positions;
};


#endif // STRUCTURE_H
