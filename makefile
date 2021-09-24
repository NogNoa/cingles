CC = gcc
CFLAGS = -Wall -g
DEPS = tabbin.h
ODIR = obj
_OBJ = 
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
OBJPILE = $(CC) $(CFLAGS) -c -o $@     $<
COMPILE = $(CC) $(CFLAGS)    -o $@.elf $^

$(ODIR)/%.o: %.c
	 $(OBJPILE)

detab: $(ODIR)/entab.o $(ODIR)/tabbin.lb.o
	$(COMPILE)

entab: $(ODIR)/entab.o $(ODIR)/tabbin.lb.o
	$(COMPILE)

dcl: $(ODIR)/declaration_parser.o $(ODIR)/molon.lb.o dcl.h
	$(COMPILE)

undcl:  $(ODIR)/undcl.o $(ODIR)/molon.lb.o dcl.h
	$(COMPILE)

defproc:  $(ODIR)/define_processor.o $(ODIR)/molon.lb.o $(ODIR)/add_remove-string.lb.o $(ODIR)/table_lookup.lb.o
	$(COMPILE)

try: $(ODIR)/try.o $(ODIR)/molon.lb.o $(ODIR)/add_remove-string.lb.o $(ODIR)/speak.lb.o
	$(COMPILE) 

.PHONY: check
.PHONY: check++

check: 
	$(CC) $(CFLAGS) -o out.o *.c

check++: %.c
	g++ $(CFLAGS) -c -o out.o $<
