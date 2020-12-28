/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <vector>
#include <random>

#include "instance_data.h"
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

   string name = "data/mknap1.txt";

   cout << "\n String: " << name << endl;
   DataProblem data(name);

   cout << "\n Num problems: " << data.getNumProblems();
   cout << "\n Num items: ";

   for (int i = 0; i < data.getNumItemsSize(); ++i) {

      cout << data.getNumItems(i) << " ";
   }

   cout << "\n Num dimensions: ";

   for (int i = 0; i < data.getNumDimensionsSize(); ++i) {

      cout << data.getNumDimensions(i) << " ";
   }

   cout << "\n Values: \n";

   for (int i = 0; i < data.getItemValueSize(); ++i) {
      for (int j = 0; j < data.getItemValueSize(i); ++j) {

         cout << data.getItemValue(i, j) << " ";
      }

      cout << endl << " ";
   }

   cout << "\n Weights: \n";

   for (int i = 0; i < data.getItemWeightSize(); ++i) {
      for (int j = 0; j < data.getItemWeightSize(i); ++j) {

         cout << data.getItemWeight(i, j) << " ";
      }

      cout << endl << " ";
   }

   cout << "\n Knapsack weights: ";

   for (int i = 0; i < data.getKnapsackWeightSize(); ++i) {

      cout << data.getKnapsackWeight(i) << " ";
   }

   cout << endl << endl;

   return 0;
}
