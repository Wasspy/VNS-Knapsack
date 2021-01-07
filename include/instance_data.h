/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class DataProblem {

   private:

      int num_problems;

      vector<int> num_items;
      vector<int> num_dimensions;
      vector<double> optimal_solution;  // Optimal solution for real problem

      vector<vector<double>> item_value;
      vector<vector<double>> item_weight;
      vector<double> knapsack_weight;

   public:

      DataProblem (string file_name);

      int getNumProblems ();

      vector<int> getNumItems ();

      int getNumItems (int i);

      int getNumItemsSize ();

      vector<int> getNumDimensions ();

      int getNumDimensions (int i);

      int getNumDimensionsSize ();

      vector<vector<double>> getItemValue ();

      vector<double> getItemValue (int i);

      double getItemValue (int i, int j);

      int getItemValueSize ();

      int getItemValueSize (int i);

      vector<vector<double>> getItemWeight ();

      vector<double> getItemWeight (int i);

      double getItemWeight (int i, int j);

      int getItemWeightSize ();

      int getItemWeightSize (int i);

      vector<double> getKnapsackWeight ();

      double getKnapsackWeight (int i);

      int getKnapsackWeightSize ();

      double getOptimalSolution (int i); 

   private:

      bool ReadFile (string file_name);

      // PRE: data must be clear
      bool ReadColumns (ifstream &file, vector<double> &data, int &max_iterations);

      bool ReadInstanceParameters (ifstream &file, int &items, int &dimensions);

      bool ReadItemsValue (ifstream &file, int &items, int &dimensions);

      bool ReadItemsWeight (ifstream &file, int &items, int &dimensions);

      bool ReadKnapsackWeight (ifstream &file, int &dimensions);
};
