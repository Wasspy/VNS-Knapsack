/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <vector>

#include "VNS_functions.h"

using namespace std;

VNS::VNS (const double &new_knapsack_weight, const vector<double> &new_items_value,
          const vector<double> &new_items_weight, const vector<bool> &new_solution,
          const vector<int> &new_neighborhood) {

   this->items_value = new_items_value;
   this->items_weight = new_items_weight;
   this->knapsack_weight = new_knapsack_weight;

   setSolution(new_solution);
   setIndexNeighborhood(0);
   setNeighborhood(new_neighborhood);

   RefreshSolutionValue();
};

VNS::~VNS () {

   solution.clear();
   neighborhood.clear();
};

double VNS::getKnapsackWeight () {

   return knapsack_weight;
};

vector<double> VNS::getItemsValue () {

   return items_value;
};

vector<double> VNS::getItemsWeight () {

   return items_weight;
};

int VNS::getIndexNeighborhood () {

   return index;
};

int VNS::getMaxNumNeighborhood () {

   return MAX_NUM_NEIGHBORHOOD;
}

int VNS::getNumNeighborhood () {

   return num_neighborhood;
};

double VNS::getSolutionValue () {

   return solution_value;
};

vector<bool> VNS::getSolution () {

   return solution;
};

vector<int> VNS::getNeighborhood () {

   return neighborhood;
};

int VNS::getNeighborhood (const int &k) {

   return neighborhood[k];
};

void VNS::setIndexNeighborhood (const int &new_index) {

   this->index = new_index;
};

void VNS::setSolution (const vector<bool> &new_solution) {

   this->solution = new_solution;

   RefreshSolutionValue();
};

void VNS::setSolution (const vector<bool> &new_solution, const double &new_value) {

   this->solution = new_solution;
   this->solution_value = new_value;
};

// PRE:
//    -> new_neighborhood: vector with the order of the neighborhoods
//       if new_neighborhood[i] == -1 => not add
//       if new_neighborhood[i] > MAX_NUM_NEIGHBORHOOD => not add
//       if new_neighborhood[i] == new_neighborhood[j] && i != j, new_neighborhood[i] -> first, new_neighborhood[j] -> second
//       if new_neighborhood := [1, 1, 1, 1] => neighborhood := [0, 1, 2, 3]
//       if new_neighborhood := [3, -1, 1, 2] => neighborhood := [2, 3, 0]
void VNS::setNeighborhood (const vector<int> &new_neighborhood) {

   int size = new_neighborhood.size();

   if (size > MAX_NUM_NEIGHBORHOOD) {

      size = MAX_NUM_NEIGHBORHOOD;
   }

   neighborhood.clear();

   for (int i = 0; i <= MAX_NUM_NEIGHBORHOOD; ++i) {
      for (int j = 0; j < size; ++j) {

         if (new_neighborhood[j] == i) {

            neighborhood.push_back(j);
         }
      }
   }

   setNumNeighborhood(size);
};

void VNS::setNumNeighborhood (const int num) {

   num_neighborhood = num;
};

void VNS::addNeighborhood (int id_neighnorhood) {

   this->neighborhood.push_back(id_neighnorhood);
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

   double total_weight = SolutionWeight();

   return (total_weight <= knapsack_weight);
};

// Checks if the new solution is correct
bool VNS::SolutionIsCorrect (const vector<bool> &new_solution) {

   double total_weight = SolutionWeight(new_solution);

   return (total_weight <= knapsack_weight);
};

// Creates a new feasible solution
void VNS::CreateNewSolution (vector<bool> &new_solution) {

   do {

      new_solution = solution;

      switch (neighborhood[index]) {

         case 0:

            ModifyRandomOne(new_solution);
            break;

         case 1:

            ModifyRandomTwo(new_solution);
            break;

         case 2:

            SwapRandomOne(new_solution);
            break;

         case 3:

            SwapRandomTwo(new_solution);
            break;
      }

   } while (!SolutionIsCorrect(new_solution));
};

// Calculates the value of the items in the knapsack (class' solution)
double VNS::SolutionValue () {

   double total_value = 0;

   for (int i = 0; i < solution.size(); ++i) {

      total_value += items_value[i] * solution[i];
   }

   return total_value;
};

// Calculates the value of the items in the knapsack (new solution)
double VNS::SolutionValue (const vector<bool> &new_solution) {

   double total_value = 0;

   for (int i = 0; i < solution.size(); ++i) {

      total_value += items_value[i] * new_solution[i];
   }

   return total_value;
};

// Calculates the weight of the items in the knapsack (class' solution)
double VNS::SolutionWeight () {

   double total_weight = 0;

   for(int i = 0; i < items_weight.size(); ++i){

      total_weight += items_weight[i] * solution[i];
   }

   return total_weight;
};

// Calculates the weight of the items in the knapsack (new solution)
double VNS::SolutionWeight (const vector<bool> &new_solution) {

   double total_weight = 0;

   for(int i = 0; i < items_weight.size(); ++i){

      total_weight += items_weight[i] * new_solution[i];
   }

   return total_weight;

};

// Shaking procedure: resolve local minimal traps
double VNS::ShakingSolution (vector<bool> &new_solution) {

   CreateNewSolution(new_solution);

   return SolutionValue(new_solution);
};

// Improvement procedure: improve the given solution
// Return: value of the new solution
double VNS::SolutionImprovement (vector<bool> &new_solution, double new_value, bool first_better) {

   int improve_value = new_value;

   switch (neighborhood[index]) {

      case 0:

         improve_value = ModifyRandomOne(new_solution, new_value, first_better);

         break;

      case 1:

         improve_value = ModifyRandomTwo(new_solution, new_value, first_better);

         break;

      case 2:

         improve_value = SwapRandomOne(new_solution, new_value, first_better);

         break;

      case 3:

         improve_value = SwapRandomTwo(new_solution, new_value, first_better);

         break;
   }

   return improve_value;
};

// Neighborhood change step: wich neighborhood will be explore next
// Using Sequential Neighborhood change step
void VNS::SelectNeighborhood (vector<bool> &new_solution, double &new_solution_value) {

   if (new_solution_value > solution_value) {

      solution = new_solution;
      solution_value = new_solution_value;
      setIndexNeighborhood (0);

   } else {

      setIndexNeighborhood (index + 1);
   }
};

// Neighborhood: puts in or takes out 1 random item
void VNS::ModifyRandomOne (vector<bool> &new_solution) {

   int item = rand() % new_solution.size();

   new_solution[item] = !new_solution[item];
};

// Neighborhood: puts in or takes out 1 random item
// To improve the solution
double VNS::ModifyRandomOne (vector<bool> &initial_solution, double initial_solution_value, bool first_better) {

   int new_value = -1;
   int best_value = initial_solution_value;
   int solution_size = initial_solution.size();

   vector<bool> new_solution;
   vector<bool> best_solution = initial_solution;

   if (first_better) {

      for (int i = 0; i < solution_size && new_value <= initial_solution_value; ++i) {

         new_solution = initial_solution;
         new_solution[i] = !new_solution[i];

         if (SolutionIsCorrect(new_solution)) {

            new_value = SolutionValue(new_solution);
         }
      }

      if (new_value > initial_solution_value) {

         best_value = new_value;
         best_solution = new_solution;
      }

   } else {

      for (int i = 0; i < solution_size; ++i) {

         new_solution = initial_solution;
         new_solution[i] = !new_solution[i];

         if (SolutionIsCorrect(new_solution)) {

            new_value = SolutionValue(new_solution);

            if (new_value > best_value) {

               best_value = new_value;
               best_solution = new_solution;
            }
         }
      }
   }

   if (initial_solution != best_solution) {    // Comprobar como se hace esto

      initial_solution = best_solution;
   }

   return best_value;
};

// Neighborhood: puts in or takes out 2 random items
void VNS::ModifyRandomTwo (vector<bool> &new_solution) {

   int first_item = rand() % new_solution.size();

   int second_item;


   do {
      second_item = rand() % new_solution.size();

   } while (first_item == second_item);

    new_solution[first_item] = !new_solution[first_item];
    new_solution[second_item] = !new_solution[second_item];
};


// Neighborhood: puts in or takes out 2 random items
// To improve the solution
double VNS::ModifyRandomTwo (vector<bool> &initial_solution, double initial_solution_value, bool first_better) {

   int new_value = -1;
   int best_value = initial_solution_value;
   int solution_size = initial_solution.size();

   vector<bool> new_solution;
   vector<bool> best_solution = initial_solution; // Comprobar si esto hace lo que quiero que haga

   if (first_better) {

      for (int i = 0; i < solution_size && new_value <= initial_solution_value; ++i) {
         for (int j = i + 1; j < solution_size && new_value <= initial_solution_value; ++j) {

            new_solution = initial_solution;
            new_solution[i] = !new_solution[i];
            new_solution[j] = !new_solution[j];

            if (SolutionIsCorrect(new_solution)) {

               new_value = SolutionValue(new_solution);
            }
         }
      }

      if (new_value > initial_solution_value) {

         best_value = new_value;
         best_solution = new_solution;
      }

   } else {

      for (int i = 0; i < solution_size; ++i) {
         for (int j = i + 1; j < i; ++j) {

            new_solution = initial_solution;
            new_solution[i] = !new_solution[i];
            new_solution[j] = !new_solution[j];

            if (SolutionIsCorrect(new_solution)) {

               new_value = SolutionValue(new_solution);

               if (new_value > best_value) {

                  best_value = new_value;
                  best_solution = new_solution;
               }
            }
         }
      }
   }

   if (initial_solution != best_solution) {    // Comprobar como se hace esto

      initial_solution = best_solution;
   }

   return best_value;
};

// Neighborhood: puts in 1 random item and takes out another random item
void VNS::SwapRandomOne (vector<bool> &new_solution) {

   int first_item = 0;
   int second_item = 0;

   double new_weight;
   double available_weight;

   vector<int> in_knapsack;
   vector<int> out_knapsack;
   vector<int> available_items;

   vector<bool> aux_solution = new_solution;


   for (int i = 0; i < aux_solution.size(); ++i) {

      if (aux_solution[i]) {
         in_knapsack.push_back(i);

      } else {

         out_knapsack.push_back(i);
      }
   }

   do {

      first_item = rand() % in_knapsack.size();

      aux_solution[in_knapsack[first_item]] = !aux_solution[in_knapsack[first_item]];

      new_weight = SolutionWeight(aux_solution);

      available_weight = getKnapsackWeight() - new_weight;

      for (int i = 0; i < out_knapsack.size(); ++i) {

         if (getItemsWeight()[out_knapsack[i]] <= available_weight) {

            available_items.push_back(out_knapsack[i]);
         }
      }

      if (available_items.size() < 1) {

         EraseElement(in_knapsack, first_item);

         aux_solution = new_solution;
      }

   } while (available_items.size() < 1 && in_knapsack.size() > 0);

   if (in_knapsack.size() > 0) {

      second_item = rand() % available_items.size();

      aux_solution[available_items[second_item]] = !aux_solution[available_items[second_item]];

      new_solution = aux_solution;
   }

};

// Neighborhood: puts in 1 random item and takes out another random item
// To improve the solution
double VNS::SwapRandomOne (vector<bool> &initial_solution, double initial_solution_value, bool first_better) {

   int new_value = -1;
   int best_value = initial_solution_value;
   int solution_size = initial_solution.size();

   vector<bool> new_solution = initial_solution;
   vector<bool> best_solution = initial_solution; // Comprobar si esto hace lo que quiero que haga

   if (first_better) {

      for (int i = 0; i < solution_size && new_value <= initial_solution_value; ++i) {
         for (int j = i + 1; j < i && new_value <= initial_solution_value; ++j) {

            new_solution = initial_solution;

            if (new_solution[i] != new_solution[j]) {
               new_solution[i] = !new_solution[i];
               new_solution[j] = !new_solution[j];

               if (SolutionIsCorrect(new_solution)) {

                  new_value = SolutionValue(new_solution);
               }
            }
         }
      }

      if (new_value > initial_solution_value) {

         best_value = new_value;
         best_solution = new_solution;
      }

   } else {

      for (int i = 0; i < solution_size; ++i) {
         for (int j = i + 1; j < i; ++j) {

            new_solution = initial_solution;

            if (new_solution[i] != new_solution[j]) {
               new_solution[i] = !new_solution[i];
               new_solution[j] = !new_solution[j];

               if (SolutionIsCorrect(new_solution)) {

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

   if (initial_solution != best_solution) {    // Comprobar como se hace esto

      initial_solution = best_solution;
   }

   return best_value;
};

// Neighborhood: puts in 2 random items and takes out other two random items
void VNS::SwapRandomTwo (vector<bool> &new_solution) {

   int first_item  = 0;
   int second_item = 0;
   int third_item  = 0;
   int fourth_item = 0;

   double new_weight;
   double available_weight;

   vector<int> first_in_knapsack;
   vector<int> second_in_knapsack;
   vector<int> third_out_knapsack;
   vector<int> fourth_out_knapsack;

   vector<int> third_available_items;
   vector<int> fourth_available_items;

   vector<bool> aux_solution = new_solution;


   for (int i = 0; i < aux_solution.size(); ++i) {

      if (aux_solution[i]) {
         first_in_knapsack.push_back(i);

      } else {

         third_out_knapsack.push_back(i);
      }
   }

   do {

      first_item = rand() % first_in_knapsack.size();

      second_in_knapsack = first_in_knapsack;

      EraseElement(second_in_knapsack, first_item);

      while (second_in_knapsack.size() > 0 && third_available_items.size() < 1) {

         second_item = rand() % second_in_knapsack.size();

         aux_solution[first_in_knapsack[first_item]] = !aux_solution[first_in_knapsack[first_item]];
         aux_solution[second_in_knapsack[second_item]] = !aux_solution[second_in_knapsack[second_item]];

         new_weight = SolutionWeight(aux_solution);

         available_weight = getKnapsackWeight() - new_weight;

         for (int i = 0; i < third_out_knapsack.size(); ++i) {

            if (getItemsWeight()[third_out_knapsack[i]] <= available_weight) {

               third_available_items.push_back(third_out_knapsack[i]);
            }
         }

         fourth_out_knapsack = third_available_items;

         EraseElement(fourth_out_knapsack, third_item);

         while (third_available_items.size() > 0 && fourth_available_items.size() < 1) {

            third_item = rand() % third_available_items.size();

            available_weight = available_weight - getItemsWeight()[third_available_items[third_item]];

            for (int i = 0; i < fourth_out_knapsack.size(); ++i) {

               if (getItemsWeight()[fourth_out_knapsack[i]] <= available_weight) {

                  fourth_available_items.push_back(fourth_out_knapsack[i]);
               }
            }

            if (fourth_available_items.size() < 1) {

               EraseElement(third_available_items, third_item);
            }

         }

         if (third_available_items.size() < 1) {

            EraseElement(second_in_knapsack, second_item);

            aux_solution = new_solution;
         }

      }

      if (second_in_knapsack.size() < 1) {

         EraseElement(first_in_knapsack, first_item);

         aux_solution = new_solution;
      }

   } while (first_in_knapsack.size() > 0 && second_in_knapsack.size() < 1);

   if (first_in_knapsack.size() > 0) {

      fourth_item = rand() % fourth_available_items.size();

      aux_solution[third_available_items[third_item]] = !aux_solution[third_available_items[third_item]];
      aux_solution[fourth_available_items[fourth_item]] = !aux_solution[fourth_available_items[fourth_item]];

      new_solution = aux_solution;

   }

};

// Neighborhood: puts in 2 random items and takes out other two random items
// To improve the solution
double VNS::SwapRandomTwo (vector<bool> &initial_solution, double initial_solution_value, bool first_better) {

   int new_value = -1;
   int best_value = initial_solution_value;
   int solution_size = initial_solution.size();

   vector<bool> new_solution = initial_solution;
   vector<bool> best_solution = initial_solution; // Comprobar si esto hace lo que quiero que haga

   if (first_better) {

      for (int i = 0; i < solution_size && new_value <= initial_solution_value; ++i) {
         for (int j = i + 1; j < solution_size && new_value <= initial_solution_value; ++j) {
            for (int k = i + 1; k < j && new_value <= initial_solution_value; ++k) {
               for (int l = k + 1; l < j && new_value <= initial_solution_value; ++l) {

                  new_solution = initial_solution;

                  if ((new_solution[i] != new_solution[j]) &&
                      (new_solution[k] != new_solution[l])) {

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     if (SolutionIsCorrect(new_solution)) {

                        new_value = SolutionValue(new_solution);
                     }
                  }
               }

               for (int l = j + 1; l < solution_size && new_value <= initial_solution_value; ++l) {

                  new_solution = initial_solution;

                  if ((new_solution[i] != new_solution[j]) &&
                      (new_solution[k] != new_solution[l])) {

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     if (SolutionIsCorrect(new_solution)) {

                        new_value = SolutionValue(new_solution);
                     }
                  }
               }
            }

            for (int k = j + 1; k < solution_size && new_value <= initial_solution_value; ++k) {
               for (int l = k + 1; l < solution_size && new_value <= initial_solution_value; ++l) {

                  new_solution = initial_solution;

                  if ((new_solution[i] != new_solution[j]) &&
                      (new_solution[k] != new_solution[l])) {

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     if (SolutionIsCorrect(new_solution)) {

                        new_value = SolutionValue(new_solution);
                     }
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

                  new_solution = initial_solution;

                  if ((new_solution[i] != new_solution[j]) &&
                      (new_solution[k] != new_solution[l])) {

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     if (SolutionIsCorrect(new_solution)) {

                        new_value = SolutionValue(new_solution);

                        if (new_value > best_value) {

                           best_value = new_value;
                           best_solution = new_solution;
                        }
                     }
                  }
               }

               for (int l = j + 1; l < solution_size; ++l) {

                  new_solution = initial_solution;

                  if ((new_solution[i] != new_solution[j]) &&
                      (new_solution[k] != new_solution[l])) {

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     if (SolutionIsCorrect(new_solution)) {

                        new_value = SolutionValue(new_solution);

                        if (new_value > best_value) {

                           best_value = new_value;
                           best_solution = new_solution;
                        }
                     }
                  }
               }
            }

            for (int k = j + 1; k < solution_size; ++k) {
               for (int l = k + 1; l < solution_size; ++l) {

                  new_solution = initial_solution;

                  if ((new_solution[i] != new_solution[j]) &&
                      (new_solution[k] != new_solution[l])) {

                     new_solution[i] = !new_solution[i];
                     new_solution[j] = !new_solution[j];

                     new_solution[k] = !new_solution[k];
                     new_solution[l] = !new_solution[l];

                     if (SolutionIsCorrect(new_solution)) {

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
   }

   if (initial_solution != best_solution) {    // Comprobar como se hace esto

      initial_solution = best_solution;
   }

   return best_value;
};

void VNS::EraseElement (vector<int> &new_solution, int id) {

   if (new_solution.size() > 1) {

      for (int i = id; i < new_solution.size() - 1; ++i) {

         new_solution[i] = new_solution[i+1];
      }

      new_solution.pop_back();

   } else {

      new_solution.clear();
   }
};
