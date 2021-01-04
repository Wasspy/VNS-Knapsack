/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>

using namespace std;

class VNS {

   private:

      const int MAX_NUM_NEIGHBORHOOD = 4;

      float knapsack_weight;
      vector<float> items_value;
      vector<float> items_weight;

      int index;
      float solution_value;
      float solution_weight;
      vector<bool> solution;
      vector<int> neighborhood;

   public:

      VNS (const float &new_knapsack_weight, const vector<float> &new_items_value,
           const vector<float> &new_items_weight, const vector<bool> &new_solution,
           const vector<int> &new_neighborhood);

      ~VNS ();

      // Shaking procedure: resolve local minimal traps
      float ShakingSolution (vector<bool> &new_solution);

      // Improvement procedure: improve the given solution
      // Return: value of the new solution
      float SolutionImprovement (vector<bool> &new_solution, float new_value, bool first_better = false);

      // Neighborhood change step: wich neighborhood will be explore next
      // Using Sequential Neighborhood change step
      void SelectNeighborhood (vector<bool> &new_solution, float &new_solution_value);

      // Get methods
      float getKnapsackWeight ();

      vector<float> getItemsValue ();

      vector<float> getItemsWeight ();

      int getIndexNeighborhood ();

      int getMaxNumNeighborhood ();

      float getSolutionValue ();

      vector<bool> getSolution ();

      vector<int> getNeighborhood ();

      int getNeighborhood (const int &k);

      // Set methods
      void setIndexNeighborhood (const int &index);

      void setSolution (const vector<bool> &solution);

      void setSolution (const vector<bool> &solution, const float &value);

      void setNeighborhood (const vector<int> &new_neighborhood);

      // Modification methods
      void addNeighborhood (int id_neighnorhood);

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

      // Neighborhood: puts in or takes out 1 random item
      void ModifyRandomOne (vector<bool> &solution);

      // Neighborhood: puts in or takes out 1 random item
      // To improve the solution
      float ModifyRandomOne (vector<bool> &solution, float solution_value, bool first_better);

      // Neighborhood: puts in or takes out 2 random items
      void ModifyRandomTwo (vector<bool> &solution);

      // Neighborhood: puts in or takes out 2 random items
      // To improve the solution
      float ModifyRandomTwo (vector<bool> &solution, float solution_value, bool first_better);

      // Neighborhood: puts in 1 random item and takes out another random item
      void SwapRandomOne (vector<bool> &solution);

      // Neighborhood: puts in 1 random item and takes out another random item
      // To improve the solution
      float SwapRandomOne (vector<bool> &solution, float solution_value, bool first_better);

      // Neighborhood: puts in 2 random items and takes out other two random items
      void SwapRandomTwo (vector<bool> &solution);

      // Neighborhood: puts in 2 random items and takes out other two random items
      // To improve the solution
      float SwapRandomTwo (vector<bool> &solution, float solution_value, bool first_better);

};
