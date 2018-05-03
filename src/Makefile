IDIR=../include
ODIR=obj
LDIR=lib
OLDIR=$(ODIR)/lib
ODDIR=$(ODIR)/lib

GITGUD= -march=native -O3  -pipe -D_GNU_SOURCE -fomit-frame-pointer
DEBUG=-O0 -Wextra -g
MEMLEAK=-ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined
# -fomit-frame-pointer -ftree-loop-linear -ftree-vectorize

CC=gcc
CFLAGS = $(GITGUD) -Wall -std=c11 `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` -I$(IDIR)

DEPS=$(IDIR)/$(wildcard *.h)

SOURCES=$(wildcard *.c)
MY_LIBS=$(wildcard $(LDIR)/*.c)

SOURCES_OBJ=$(patsubst %.c,$(ODIR)/%.o,$(SOURCES))
MY_LIBS_OBJ=$(foreach o, $(patsubst %.c,%.o,$(MY_LIBS)), $(ODIR)/$o)

LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`


print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(CFLAGS) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o program $(LIBS)

debug: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(CFLAGS) $(DEBUG) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o program $(LIBS)

memleak: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(MEMLEAK) $(CFLAGS) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o program $(LIBS)

clean:
	rm obj/*.o
	rm obj/lib/*.o
	rm program
