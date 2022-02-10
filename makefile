# ############################################
# ##    demande generale de compilation     ##
# ############################################

all : main clean

# ================== compile =================
#
# ------ definitions -------------------------
CC = gcc
SRC = main.c color.c TabDirectory.c DirectoryFile.c
OBJS = $(SRC:.c=.o)

# ------ regle implicite ---------------------
.SUFFIXES:.o.c
.c.o:
	$(CC) -c $<

# ------ regle explicite ---------------------
main : $(OBJS)
	$(CC) -o $@ $(OBJS) 

main.o      	: color.h structure.h DirectoryFile.h TabDirectory.h
color.o    		: color.h
TabDirectory.o 	: structure.h DirectoryFile.h TabDirectory.h
DirectoryFile.o : structure.h DirectoryFile.h TabDirectory.h color.h
# ================== nettoie =================
clean :
	rm *.o 

