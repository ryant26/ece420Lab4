CC := gcc
CFLAGS := -fopenmp -lm -Wall

VPATH = src:sdk
BUILDDIR = build
BIN = bin

default: checkdirs submission

all: checkdirs datagen serialtester main

$(BUILDDIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

submission: $(BUILDDIR)/main.o $(BUILDDIR)/utilities.o $(BUILDDIR)/Lab3IO.o
	$(CC) -o main $^ $(CFLAGS)

main: $(BUILDDIR)/main.o $(BUILDDIR)/utilities.o  $(BUILDDIR)/Lab3IO.o
	$(CC) -o $(BIN)/main $^ $(CFLAGS)

serialmain: $(BUILDDIR)/serialmain.o $(BUILDDIR)/utilities.o  $(BUILDDIR)/Lab3IO.o
	$(CC) -o $(BIN)/serialmain $^ $(CFLAGS)

datagen: $(BUILDDIR)/Lab3IO.o build/datagen.o
	$(CC) -o $(BIN)/datagen $^

serialtester: build/Lab3IO.o build/serialtester.o 
	$(CC) -o $(BIN)/serialtester $^ $(CFLAGS)

checkdirs: $(BUILDDIR) $(BIN)

$(BUILDDIR):
	@mkdir -p $@

$(BIN):
	@mkdir -p $@	

clean:
	rm -rf $(BUILDDIR) 
	rm -rf $(BIN)
	rm -f data_*
	rm -f main
