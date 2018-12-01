IDIR =../include
CC=gcc
CFLAGI=-I$(IDIR)
CFLAGL=-L/usr/local/lib
CFLAGCUI=-I../include
GDB=-g
LIBS= -fprofile-arcs -ftest-coverage -lcunit -lncurses -lmenu

ODIR=../obj

SPLINT = splint
SPLINTFLAGS = -weak -type +sysdirerrors +compdef +trytorecover +posixlib  -preproc -retvalother\
               +line-len 80 -warnposix +infloops -fixedformalarray \
	      -annotationerror \

SPLINT_SOURCE = GameLogic.c WinManager.c PlayerFunc.c EnemyFunc.c MapFunc.c main.c

_DEPS = GameLogic.h WinManager.h PlayerFunc.h EnemyFunc.h MapFunc.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ1 = GameLogic.o WinManager.o PlayerFunc.o EnemyFunc.o MapFunc.o main.o
OBJ1 = $(patsubst %,$(ODIR)/%,$(_OBJ1))

_OBJ2 = GameLogic.o WinManager.o PlayerFunc.o EnemyFunc.o MapFunc.o CUnit.o
OBJ2 = $(patsubst %,$(ODIR)/%,$(_OBJ2))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGI) $(LIBS) $(GDB)

main: $(OBJ1)
	$(CC) -Wall $(CFLAGCUI) $^ $(CFLAGL) $(LIBS) -o $@ $(CFLAGI) $(GDB)

CUnit: $(OBJ2)
	$(CC) -Wall $(CFLAGCUI) $^ $(CFLAGL) $(LIBS) -o $@ $(CFLAGI) $(GDB)

splint:
	$(SPLINT) $(SPLINTFLAGS) -I $(IDIR) $(SPLINT_SOURCE)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

