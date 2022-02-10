/*                            color.h                                */

#ifndef  __MY_COLOR__      // afin d'eviter les doubles declarations
#define  __MY_COLOR__

#if  WIN32	
  #include   <windows.h> 
  typedef enum ColAvant {
      NOIR=0, DARKBLEU, VERT, BLEUGRIS, MARRON, POURPRE, KAKI, GRISCLAIR,
      GRIS, BLEUCLAIR, VERTCLAIR, CYAN,  ROUGE, ROSE,  JAUNE, BLANC } ColAvant ;
#else 
  typedef enum ColAvant {
      RESET=0, NOIR,      ROUGE,      VERT,      JAUNE,      BLEU, 
	  reset=9, NOIRCLAIR, ROUGECLAIR, VERTCLAIR, JAUNECLAIR, BLEUCLAIR, 
	           MAGENTA=6,       CYAN,      BLANC,
			   MAGENTACLAIR=15, CYANCLAIR, BLANCCLAIR                   } ColAvant ;
#endif 
void   clrScr() ;
void   Color(ColAvant ,int ) ;
void   normalColor() ;
char * getNomColor(int i) ;
int    getNbColor() ;

// ###########################################################################

#endif




