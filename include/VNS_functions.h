/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      100000298@alumnos.uimp.es
*/

#include <iostream>

using namespace std;

class VNS {

   private:

      const int MAX_NUM_NEIGHBORHOOD = 4;

      double knapsack_weight;
      vector<double> items_value;
      vector<double> items_weight;

      int index;
      int num_neighborhood;
      double solution_value;
      double solution_weight;
      vector<bool> solution;
      vector<int> neighborhood;

   public:

      VNS (const double &new_knapsack_weight, const vector<double> &new_items_value,
           const vector<double> &new_items_weight, const vector<bool> &new_solution,
           const vector<int> &new_neighborhood);

      ~VNS ();

      // Shaking procedure: resolve local minimal traps
      double ShakingSolution (vector<bool> &new_solution);

      // Improvement procedure: improve the given solution
      // Return: value of the new solution
      double SolutionImprovement (vector<bool> &new_solution, double new_value, bool first_better = false);

      // Neighborhood change step: wich neighborhood will be explore next
      // Using Sequential Neighborhood change step
      void SelectNeighborhood (vector<bool> &new_solution, double &new_solution_value);

      // Get methods
      double getKnapsackWeight ();

      vector<double> getItemsValue ();

      vector<double> getItemsWeight ();

      int getIndexNeighborhood ();

      int getMaxNumNeighborhood ();

      int getNumNeighborhood ();

      double getSolutionValue ();

      vector<bool> getSolution ();

      vector<int> getNeighborhood ();

      int getNeighborhood (const int &k);

      // Set methods
      void setIndexNeighborhood (const int &index);

      void setSolution (const vector<bool> &solution);

      void setSolution (const vector<bool> &solution, const double &value);

      void setNeighborhood (const vector<int> &new_neighborhood);

      void setNumNeighborhood (const int num);

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
      double SolutionValue ();

      // Calculates the value of the items in the knapsack (new solution)
      double SolutionValue (const vector<bool> &new_solution);

      // Calculates the weight of the items in the knapsack (class' solution)
      double SolutionWeight ();

      // Calculates the weight of the items in the knapsack (new solution)
      double SolutionWeight (const vector<bool> &new_solution);

      // Neighborhood: puts in or takes out 1 random item
      void ModifyRandomOne (vector<bool> &solution);

      // Neighborhood: puts in or takes out 1 random item
      // To improve the solution
      double ModifyRandomOne (vector<bool> &solution, double solution_value, bool first_better);

      // Neighborhood: puts in or takes out 2 random items
      void ModifyRandomTwo (vector<bool> &solution);

      // Neighborhood: puts in or takes out 2 random items
      // To improve the solution
      double ModifyRandomTwo (vector<bool> &solution, double solution_value, bool first_better);

      // Neighborhood: puts in 1 random item and takes out another random item
      void SwapRandomOne (vector<bool> &solution);

      // Neighborhood: puts in 1 random item and takes out another random item
      // To improve the solution
      double SwapRandomOne (vector<bool> &solution, double solution_value, bool first_better);

      // Neighborhood: puts in 2 random items and takes out other two random items
      void SwapRandomTwo (vector<bool> &solution);

      // Neighborhood: puts in 2 random items and takes out other two random items
      // To improve the solution
      double SwapRandomTwo (vector<bool> &solution, double solution_value, bool first_better);

      void EraseElement (vector<int> &new_solution, int id);

};
