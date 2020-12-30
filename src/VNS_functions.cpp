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

FunctionPointerInt VNS::getNeighborhoodChange () {

   return neighborhood_change;
};


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

float VNS::LocalSearch (vector<bool> &new_solution, float new_solution_value) {


}
