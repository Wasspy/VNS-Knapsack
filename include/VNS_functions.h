/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>

using namespace std;

typedef void (*FunctionPointer)(vector<bool>);
typedef int (*FunctionPointerInt)(vector<bool>);
typedef float (*FunctionPointerFloat)(vector<bool>);

class VNS {

   private:

      float knapsack_weight;
      vector<float> items_value;
      vector<float> items_weight;
      float (*improve_solution)(vector<bool>);

      int index;
      float solution_value;
      vector<bool> solution;
      vector<void (*)(vector<bool>)> neighborhood;

   public:

      VNS (const float &new_knapsack_weight, const vector<float> &new_items_value,
           const vector<float> &new_items_weight, const vector<bool> &new_solution,
           const vector<void (*)(vector<bool>)> &new_neighborhood,
           float (*new_improve_solution)(vector<bool>);

      ~VNS ();


      float getKnapsackWeight ();

      vector<float> getItemsValue ();

      vector<float> getItemsWeight ();

      int getIndexNeighborhood ();

      float getSolutionValue ();

      vector<bool> getSolution ();

      vector<void (*)(vector<bool>)> getNeighborhood ();

      FunctionPointer getNeighborhood (const int &k);

      FunctionPointerFloat getImproveSolution ();

      FunctionPointerInt getNeighborhoodChange ();


      void setIndexNeighborhood (const int &index);

      void setSolution (const vector<bool> &solution);

      void setSolution (const vector<bool> &solution, const float &value);

      void setNeighborhood (const vector<void (*)(vector<bool>)> &neighborhood);

      void addNeighborhood (void (*neighborhood)(vector<bool>));

      // PRE: k -> [0, neighborhood.size()[
      bool removeNeighborhood (const int &k);


      bool RefreshSolutionValue ();

   private:

      // Checks if the class' solution is correct
      bool SolutionIsCorrect ();

      // Checks if the new solution is correct
      bool SolutionIsCorrect (const vector<bool> &new_solution);

      // Creates a new feasible solution
      void CreateNewSolution (vector<bool> &new_solution);

      // Calculates the value of the items in the knapsack (class' solution)
      float SolutionValue ();

      // Calculates the value of the items in the knapsack (new solution)
      float SolutionValue (const vector<bool> &new_solution);

      // Shaking procedure: resolve local minimal traps
      float ShakingSolution (vector<bool> &new_solution);

      // Improvement procedure: improve the given solution
      // Return: value of the new solution
      float SolutionImprovement (vector<bool> &new_solution);

      // Neighborhood change step: wich neighborhood will be explore next
      // Using Sequential Neighborhood change step
      void SelectNeighborhood (vector<bool> &new_solution, float &new_solution_value);
};
