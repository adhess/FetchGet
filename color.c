/*                            color.c                                */

#include    <stdio.h>   /* pour printf    */
#include    "color.h"      // pour color

#if  WIN32	// ------------ sous windows -------------------
  #include   <windows.h>
  char * nomColor[] = {
	"NOIR", "DARKBLEU",  "VERT",      "BLEUGRIS", "MARRON", "POURPRE", "KAKI",  "GRISCLAIR",
    "GRIS", "BLEUCLAIR", "VERTCLAIR", "CYAN",     "ROUGE",  "ROSE",    "JAUNE", "BLANC" };
  void Color(ColAvant t,int f) {
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,f*16+t);
  }
  void normalColor() { Color( GRISCLAIR , 0) ; }
  void clrScr()      { system("cls"); }
#else  // ------------ sous unix ----------------------------
  char * nomColor[] = {
 "RESET",   "NOIR",      "ROUGE",      "VERT",      "JAUNE",      "BLEU",      "MAGENTA",      "CYAN",      "BLANC",
 "RESET",   "NOIRCLAIR", "ROUGECLAIR", "VERTCLAIR", "JAUNECLAIR", "BLEUCLAIR", "MAGENTACLAIR", "CYANCLAIR", "BLANCCLAIR"  } ;
  char * valColor[] = { "0", "30",  "31", "32", "33", "34", "35", "36", "37" } ;
  void Color(ColAvant param, int f) {
      if (param > 8) { printf("\033[1m") ; param = param%9 ; } // set brillance
      printf("\033[%sm",valColor[param%9]) ;
  }
  void normalColor() { Color( RESET , 0) ; }
  void clrScr()      { printf("\033[H\033[2J"); }
#endif	// --------------------------------------------------

char * getNomColor(int i) { return nomColor[i] ;}
int    getNbColor()       { return sizeof(nomColor)/sizeof(char*) ; }

/* ================ fonction publique ======================================= */
// ###########################################################################

