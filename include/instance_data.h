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
      vector<float> optimal_solution;  // Optimal solution for real problem

      vector<vector<float>> item_value;
      vector<vector<float>> item_weight;
      vector<float> knapsack_weight;

   public:

      DataProblem (string file_name);

      int getNumProblems ();

      vector<int> getNumItems ();

      int getNumItems (int i);

      int getNumItemsSize ();

      vector<int> getNumDimensions ();

      int getNumDimensions (int i);

      int getNumDimensionsSize ();

      vector<vector<float>> getItemValue ();

      vector<float> getItemValue (int i);

      float getItemValue (int i, int j);

      int getItemValueSize ();

      int getItemValueSize (int i);

      vector<vector<float>> getItemWeight ();

      vector<float> getItemWeight (int i);

      float getItemWeight (int i, int j);

      int getItemWeightSize ();

      int getItemWeightSize (int i);

      vector<float> getKnapsackWeight ();

      float getKnapsackWeight (int i);

      int getKnapsackWeightSize ();

   private:

      bool ReadFile (string file_name);

      // PRE: data must be clear
      bool ReadColumns (ifstream &file, vector<float> &data, int &max_iterations);

      bool ReadInstanceParameters (ifstream &file, int &items, int &dimensions);

      bool ReadItemsValue (ifstream &file, int &items, int &dimensions);

      bool ReadItemsWeight (ifstream &file, int &items, int &dimensions);

      bool ReadKnapsackWeight (ifstream &file, int &dimensions);
};
