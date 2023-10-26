COURSE = cs375
SEMESTER = fall2022
LASTNAME = perezleonemillar
FIRSTINITIAL = jjm
PNUMBER = project
EXE = quicksort

DIRECTORY = ../perezleonemillar_jjm_project
TARFILE = $(LASTNAME)_$(FIRSTINITIAL)_$(PNUMBER).tar

FLAGS = -Wall -Wextra -g -ggdb
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

input: $(BIN)/makeInput

$(BIN)/makeInput : $(OBJ)/inputmaker.o
	$(CC) $(FLAGS) $(OBJ)/inputmaker.o -o $@

$(OBJ)/inputmaker.o: inputmaker.cpp
	$(CC) $(FLAGS) -c inputmaker.cpp -o $@


all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/quicksort.o
	$(CC) $(FLAGS) $(OBJ)/quicksort.o -o $@

$(OBJ)/quicksort.o: quicksort.cpp
	$(CC) $(FLAGS) -c quicksort.cpp -o $@


tar:	clean
	tar cvvf $(TARFILE) $(DIRECTORY)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz $(BIN)/makeInput