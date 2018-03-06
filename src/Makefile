IDIR=../include
ODIR=obj
LDIR=lib
OLDIR=$(ODIR)/lib

CC=gcc
CFLAGS=-Wall -std=c11 `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` -I$(IDIR)

DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(wildcard *.c)
MY_LIBS=$(wildcard $(LDIR)/*.c)
SOURCES_OBJ=$(foreach o, $(patsubst %.c,%.o,$(SOURCES)), $(ODIR)/$o)
MY_LIBS_OBJ=$(foreach o, $(patsubst %.c,%.o,$(MY_LIBS)), $(ODIR)/$o)
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

DEBUG=-O0 -g -Wextra -pedantic
MEMLEAK=-ggdb -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined
GITGUD=-march=native -O3 -pipe -D_GNU_SOURCE -pedantic

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(GITUG) $(CFLAGS) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o program $(LIBS)

debug: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(DEBUG) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o programD $(LIBS)

memleak: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(GITGUD) $(MEMLEAK) $(wildcard $(ODIR)/*.o)  $(wildcard $(OLDIR)/*.o) -o programM $(LIBS)

clean:
	rm obj/*.o
	rm obj/lib/*.o
	rm program*
