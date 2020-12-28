#
#	Máster Universitario en Investigación en Inteligencia Artificial
#	Resolución de problemas con metaheurísticos
#
#  Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
#

SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c --std=c++11 -O2

all: $(BIN)/VNS_Knapsack

# ************ Compilación de módulos ************

$(OBJ)/instance_data.o: $(SRC)/instance_data.cpp $(INC)/instance_data.h
	$(CXX) $(CPPFLAGS) $(SRC)/instance_data.cpp -o $(OBJ)/instance_data.o

$(OBJ)/VNS_functions.o: $(SRC)/VNS_functions.cpp $(INC)/VNS_functions.h
	$(CXX) $(CPPFLAGS) $(SRC)/VNS_functions.cpp -o $(OBJ)/VNS_functions.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/instance_data.h $(INC)/VNS_functions.h
	$(CXX) $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

$(BIN)/VNS_Knapsack: $(OBJ)/main.o $(OBJ)/instance_data.o $(OBJ)/VNS_functions.o
	$(CXX) -o $(BIN)/VNS_Knapsack $(OBJ)/main.o $(OBJ)/instance_data.o $(OBJ)/VNS_functions.o

	@echo "\n ************************************"
	@echo "\n"  Programa compilado. Para ejecutar: "\n\n\t"VNS_Knapsack \<semilla\>
	@echo "\n"  Valores por defecto: "\n   "-\> semilla = 22
	@echo "\n ************************************ \n"

# ************ Limpieza de ficheros ************

clean:
	-rm $(OBJ)/* $(BIN)/*

	@echo "\n" Se han borrado los ficheros de las carpetas obj y bin "\n"
