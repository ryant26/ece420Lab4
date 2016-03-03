CC := mpicc
CFLAGS := -lm -Wall

VPATH = src:sdk
BUILDDIR = build
BIN = bin

default: checkdirs submission

all: checkdirs datatrim main

$(BUILDDIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

submission: $(BUILDDIR)/main.o $(BUILDDIR)/utilities.o $(BUILDDIR)/Lab3IO.o
	$(CC) -o main $^ $(CFLAGS)

main: $(BUILDDIR)/main.o $(BUILDDIR)/Lab4_IO.o
	$(CC) -o $(BIN)/main $^ $(CFLAGS)

datatrim: build/datatrim.o Lab4_IO.o
	$(CC) -o $(BIN)/datatrim $^

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
