/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <vector>
#include <random>

//#include "VNS_functions.h"

using namespace std;

// Neighborhood: puts in or takes out 1 random item
void ModifyRandomOne (vector<bool> &solution) {

   int item = rand() % solution.size();

   solution[item] = !solution[item];
}

// Neighborhood: puts in or takes out 2 random items
void ModifyRandomTwo (vector<bool> &solution) {

   int first_item = rand() % solution.size();

   int second_item;

   do {
      second_item = rand() % solution.size();

   } while (first_item == second_item);

    solution[first_item] = !solution[first_item];
    solution[second_item] = !solution[second_item];
}

// Neighborhood: puts in 1 random item and takes out another random item
void SwapRandomTwo (vector<bool> &solution) {

   int first_item = rand() % solution.size();

   int second_item;

   do {
      second_item = rand() % solution.size();

   } while (first_item == second_item || solution[first_item] == solution[second_item]);

   solution[first_item] = !solution[first_item];
   solution[second_item] = !solution[second_item];
}





int main (int argc, char *argv[]) {

   srand (22);

   vector<bool> prueba (20, 0);

   cout << "Valores: ";

   for (int i=0; i < prueba.size(); ++i) cout << prueba[i] << " ";

   cout << endl;

   prueba[0] = 1;
   prueba[5] = 1;
   prueba[10] = 1;
   prueba[15] = 1;

   for (int i = 0; i < 10; ++i) {
   SwapRandomTwo(prueba);

   cout << "\nValores: ";

   for (int i=0; i < prueba.size(); ++i) cout << prueba[i] << " ";

   cout << endl;
}
   return 0;
}
