/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <vector>

#include "VNS_functions.h"

using namespace std;

VNS::VNS (const float &new_knapsack_weight, const vector<float> &new_items_value,
          const vector<float> &new_items_weight, const vector<bool> &new_solution,
          const vector<void (*)(vector<bool>)> &new_neighborhood,
          float (*new_improve_solution)(vector<bool>)) {

   this->items_value = new_items_value;
   this->items_weight = new_items_weight;
   this->knapsack_weight = new_knapsack_weight;
   this->improve_solution = new_improve_solution;

   setSolution(new_solution);
   setIndexNeighborhood(0);
   setNeighborhood(new_neighborhood);

   RefreshSolutionValue();
};

VNS::~VNS () {

   solution.clear();
   neighborhood.clear();
};

float VNS::getKnapsackWeight () {

   return knapsack_weight;
};

vector<float> VNS::getItemsValue () {

   return items_value;
};

vector<float> VNS::getItemsWeight () {

   return items_weight;
};

int VNS::getIndexNeighborhood () {

   return index;
};

float VNS::getSolutionValue () {

   return solution_value;
};

vector<bool> VNS::getSolution () {

   return solution;
};

vector<void (*)(vector<bool>)> VNS::getNeighborhood () {

   return neighborhood;
};

FunctionPointer VNS::getNeighborhood (const int &k) {

   return neighborhood[k];
};

FunctionPointerFloat VNS::getImproveSolution () {

   return improve_solution;
};
/*
FunctionPointerInt VNS::getNeighborhoodChange () {

   return neighborhood_change;
};
*/

void VNS::setIndexNeighborhood (const int &new_index) {

   this->index = new_index;
};

void VNS::setSolution (const vector<bool> &new_solution) {

   this->solution = new_solution;

   RefreshSolutionValue();
};

void VNS::setSolution (const vector<bool> &new_solution, const float &new_value) {

   this->solution = new_solution;
   this->solution_value = new_value;
};

void VNS::setNeighborhood (const vector<void (*)(vector<bool>)> &new_neighborhood) {

   this->neighborhood = new_neighborhood;
};

void VNS::addNeighborhood (void (*new_neighborhood)(vector<bool>)) {

   this->neighborhood.push_back(new_neighborhood);
};

// PRE: k -> [0, neighborhood.size()[
bool VNS::removeNeighborhood (const int &k) {

   if (k < neighborhood.size()) {

      // Erase the k element (begin -> position 0)
      neighborhood.erase(neighborhood.begin() + k);
      return true;
   }

   return false;
};

bool VNS::RefreshSolutionValue () {

   solution_value = SolutionValue();

   return true;
};

// Checks if the class' solution is correct
bool VNS::SolutionIsCorrect () {

   float total_weight = 0;

   for(int i = 0; i < items_weight.size(); ++i){

      total_weight += items_weight[i] * solution[i];
   }

   return (total_weight <= knapsack_weight);
};

// Checks if the new solution is correct
bool VNS::SolutionIsCorrect (const vector<bool> &new_solution) {

   float total_weight = 0;

   for(int i = 0; i < items_weight.size(); ++i){

      total_weight += items_weight[i] * new_solution[i];
   }

   return (total_weight <= knapsack_weight);
};

// Creates a new feasible solution
void VNS::CreateNewSolution (vector<bool> &new_solution) {

   do {

      new_solution = solution;

      neighborhood[index](new_solution);

   } while (!SolutionIsCorrect(new_solution));
};

// Calculates the value of the items in the knapsack (class' solution)
float VNS::SolutionValue () {

   float total_value = 0;

   for (int i = 0; i < solution.size(); ++i) {

      total_value += items_value[i] * solution[i];
   }

   return total_value;
};

// Calculates the value of the items in the knapsack (new solution)
float VNS::SolutionValue (const vector<bool> &new_solution) {

   float total_value = 0;

   for (int i = 0; i < solution.size(); ++i) {

      total_value += items_value[i] * new_solution[i];
   }

   return total_value;
};

// Shaking procedure: resolve local minimal traps
float VNS::ShakingSolution (vector<bool> &new_solution) {

   CreateNewSolution(new_solution);

   return SolutionValue(new_solution);
};

// Improvement procedure: improve the given solution
// Return: value of the new solution
float VNS::SolutionImprovement (vector<bool> &new_solution) {

   return (*improve_solution)(new_solution);
};

// Neighborhood change step: wich neighborhood will be explore next
// Using Sequential Neighborhood change step
void VNS::SelectNeighborhood (vector<bool> &new_solution, float &new_solution_value) {

   if (new_solution_value > solution_value) {

      solution = new_solution;
      solution_value = new_solution_value;
      setIndexNeighborhood (0);

   } else {

      setIndexNeighborhood (index + 1);
   }
};

float VNS::LocalSearch (vector<bool> &new_solution, float new_solution_value, bool first_better) {

   return neighborhood_improve[index](new_solution, new_solution_value, first_better);
};

// Neighborhood: puts in or takes out 1 random item
void VNS::ModifyRandomOne (vector<bool> &solution) {

   int item = rand() % solution.size();

   solution[item] = !solution[item];
};

// Neighborhood: puts in or takes out 1 random item
// To improve the solution
float VNS::ModifyRandomOne (vector<bool> &solution, float solution_value, bool first_better) {

   int new_value = -1;
   int best_value = solution_value;
   int solution_size = solution.size();

   vector<bool> new_solution;
   vector<bool> best_solution = solution; // Comprobar si esto hace lo que quiero que haga

   if (first_better) {

      for (int i = 0; i < solution_size && new_value <= solution_value; ++i) {

         new_solution = solution;
         new_solution[i] = !new_solution[i];

         new_value = SolutionValue(new_solution);
      }

      if (new_value > solution_value) {

         best_value = new_value;
         best_solution = new_solution;
      }

   } else {

      for (int i = 0; i < solution_size; ++i) {

         new_solution = solution;
         new_solution[i] = !new_solution[i];

         new_value = SolutionValue(new_solution);

         if (new_value > best_value) {

            best_value = new_value;
            best_solution = new_solution;
         }
      }
   }

   if (solution != best_solution) {    // Comprobar como se hace esto

      solution = best_solution;
   }

   return best_value;
};

// Neighborhood: puts in or takes out 2 random items
void VNS::ModifyRandomTwo (vector<bool> &solution) {

   int first_item = rand() % solution.size();

   int second_item;

   do {
      second_item = rand() % solution.size();

   } while (first_item == second_item);

    solution[first_item] = !solution[first_item];
    solution[second_item] = !solution[second_item];
};

// Neighborhood: puts in or takes out 2 random items
// To improve the solution
float VNS::ModifyRandomTwo (vector<bool> &solution, float solution_value, bool first_better) {

   int new_value = -1;
   int best_value = solution_value;
   int solution_size = solution.size();

   vector<bool> new_solution;
   vector<bool> best_solution = solution; // Comprobar si esto hace lo que quiero que haga

   if (first_better) {

      for (int i = 0; i < solution_size && new_value <= solution_value; ++i) {
         for (int j = i + 1; j < solution_size && new_value <= solution_value; ++j) {

            new_solution = solution;
            new_solution[i] = !new_solution[i];
            new_solution[j] = !new_solution[j];

            new_value = SolutionValue(new_solution);
         }
      }

      if (new_value > solution_value) {

         best_value = new_value;
         best_solution = new_solution;
      }

   } else {

      for (int i = 0; i < solution_size; ++i) {
         for (int j = i + 1; j < i; ++j) {

            new_solution = solution;
            new_solution[i] = !new_solution[i];
            new_solution[j] = !new_solution[j];

            new_value = SolutionValue(new_solution);

            if (new_value > best_value) {

               best_value = new_value;
               best_solution = new_solution;
            }
         }
      }
   }

   if (solution != best_solution) {    // Comprobar como se hace esto

      solution = best_solution;
   }

   return best_value;
};

// Neighborhood: puts in 1 random item and takes out another random item
void VNS::SwapRandomOne (vector<bool> &solution) {

   int first_item = rand() % solution.size();

   int second_item;

   do {
      second_item = rand() % solution.size();

   } while (first_item == second_item || solution[first_item] == solution[second_item]);

   solution[first_item] = !solution[first_item];
   solution[second_item] = !solution[second_item];
};

// Neighborhood: puts in 1 random item and takes out another random item
// To improve the solution
float VNS::SwapRandomOne (vector<bool> &solution, float solution_value, bool first_better) {

   int new_value = -1;
   int best_value;
   int solution_size = solution.size();

   vector<bool> new_solution = solution;
   vector<bool> best_solution = solution; // Comprobar si esto hace lo que quiero que haga

   if (first_better) {

      for (int i = 0; i < solution_size && new_value <= solution_value; ++i) {
         for (int j = i + 1; j < i && new_value <= solution_value; ++j) {

            new_solution = solution;

            if (new_solution[i] xor new_solution[j]) {   // Comprobar como se hace esto
               new_solution[i] = !new_solution[i];
               new_solution[j] = !new_solution[j];

               new_value = SolutionValue(new_solution);
            }
         }
      }

      if (new_value > solution_value) {

         best_value = new_value;
         best_solution = new_solution;
      }

   } else {

      for (int i = 0; i < solution_size; ++i) {
         for (int j = i + 1; j < i; ++j) {

            new_solution = solution;

            if (new_solution[i] xor new_solution[j]) {   // Comprobar como se hace esto
               new_solution[i] = !new_solution[i];
               new_solution[j] = !new_solution[j];

               new_value = SolutionValue(new_solution);

               if (new_value > best_value) {

                  best_value = new_value;
                  best_solution = new_solution;
               }
            }
         }
      }
   }

   if (solution != best_solution) {    // Comprobar como se hace esto

      solution = best_solution;
   }

   return best_value;
};

// Neighborhood: puts in 2 random items and takes out other two random items
void VNS::SwapRandomTwo (vector<bool> &solution) {

   int first_item = rand() % solution.size();

   int second_item;
   int third_item;
   int fourth_item;

   do {
      second_item = rand() % solution.size();

   } while (first_item == second_item || solution[first_item] == solution[second_item]);

   do {
      third_item = rand() % solution.size();

   } while (first_item == third_item || second_item == third_item);

   do {
      fourth_item = rand() % solution.size();

   } while (third_item == fourth_item || solution[third_item] == solution[fourth_item]);


   solution[first_item] = !solution[first_item];
   solution[second_item] = !solution[second_item];

   solution[third_item] = !solution[third_item];
   solution[fourth_item] = !solution[fourth_item];
};

// Neighborhood: puts in 2 random items and takes out other two random items
// To improve the solution
float VNS::SwapRandomTwo (vector<bool> &solution, float solution_value, bool first_better) {

   int new_value = -1;
   int best_value;
   int solution_size = solution.size();

   vector<bool> new_solution = solution;
   vector<bool> best_solution = solution; // Comprobar si esto hace lo que quiero que haga

   if (first_better) {

      for (int i = 0; i < solution_size && new_value <= solution_value; ++i) {
         for (int j = i + 1; j < solution_size && new_value <= solution_value; ++j) {
            for (int k = i + 1; k < j && new_value <= solution_value; ++k) {
               for (int l = k + 1; l < j && new_value <= solution_value; ++l) {

                  new_solution = solution;

                  if ((new_solution[i] xor new_solution[j]) &&
                      (new_solution[k] xor new_solution[l])) {   // Comprobar como se hace esto

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     new_value = SolutionValue(new_solution);
                  }
               }

               for (int l = j + 1; l < solution_size && new_value <= solution_value; ++l) {

                  new_solution = solution;

                  if ((new_solution[i] xor new_solution[j]) &&
                      (new_solution[k] xor new_solution[l])) {   // Comprobar como se hace esto

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     new_value = SolutionValue(new_solution);
                  }
               }
            }

            for (int k = j + 1; k < solution_size && new_value <= solution_value; ++k) {
               for (int l = k + 1; l < solution_size && new_value <= solution_value; ++l) {

                  new_solution = solution;

                  if ((new_solution[i] xor new_solution[j]) &&
                      (new_solution[k] xor new_solution[l])) {   // Comprobar como se hace esto

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     new_value = SolutionValue(new_solution);
                  }
               }
            }
         }
      }

      if (new_value > solution_value) {

         best_value = new_value;
         best_solution = new_solution;
      }

   } else {

      for (int i = 0; i < solution_size; ++i) {
         for (int j = i + 1; j < solution_size; ++j) {
            for (int k = i + 1; k < j; ++k) {
               for (int l = k + 1; l < j; ++l) {

                  new_solution = solution;

                  if ((new_solution[i] xor new_solution[j]) &&
                      (new_solution[k] xor new_solution[l])) {   // Comprobar como se hace esto

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     new_value = SolutionValue(new_solution);

                     if (new_value > best_value) {

                        best_value = new_value;
                        best_solution = new_solution;
                     }
                  }
               }

               for (int l = j + 1; l < solution_size; ++l) {

                  new_solution = solution;

                  if ((new_solution[i] xor new_solution[j]) &&
                      (new_solution[k] xor new_solution[l])) {   // Comprobar como se hace esto

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     new_value = SolutionValue(new_solution);

                     if (new_value > best_value) {

                        best_value = new_value;
                        best_solution = new_solution;
                     }
                  }
               }
            }

            for (int k = j + 1; k < solution_size; ++k) {
               for (int l = k + 1; l < solution_size; ++l) {

                  new_solution = solution;

                  if ((new_solution[i] xor new_solution[j]) &&
                      (new_solution[k] xor new_solution[l])) {   // Comprobar como se hace esto

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     new_value = SolutionValue(new_solution);

                     if (new_value > best_value) {

                        best_value = new_value;
                        best_solution = new_solution;
                     }
                  }
               }
            }
         }
      }
   }

   if (solution != best_solution) {    // Comprobar como se hace esto

      solution = best_solution;
   }

   return best_value;
};
