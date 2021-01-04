/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <fstream>
#include <vector>

#include "instance_data.h"

using namespace std;

DataProblem::DataProblem (string file_name) {

   num_problems = 0;
   if (!ReadFile(file_name)) {

      cerr << "ERROR: error al leer el fichero";

      exit (-1);
   }
};

int DataProblem::getNumProblems () {

   return num_problems;
};

vector<int> DataProblem::getNumItems () {

   return num_items;
};

int DataProblem::getNumItems (int i) {

   return num_items[i];
};

int DataProblem::getNumItemsSize () {

   return num_items.size();
};

vector<int> DataProblem::getNumDimensions () {

   return num_dimensions;
};

int DataProblem::getNumDimensions (int i) {

   return num_dimensions[i];
};

int DataProblem::getNumDimensionsSize () {

   return num_dimensions.size();
};

vector<vector<float>> DataProblem::getItemValue () {

   return item_value;
};

vector<float> DataProblem::getItemValue (int i) {

   return item_value[i];
};

float DataProblem::getItemValue (int i, int j) {

   return item_value[i][j];
};

int DataProblem::getItemValueSize () {

   return item_value.size();
};

int DataProblem::getItemValueSize (int i) {

   return item_value[i].size();
};

vector<vector<float>> DataProblem::getItemWeight () {

   return item_weight;
};

vector<float> DataProblem::getItemWeight (int i) {

   return item_weight[i];
};

float DataProblem::getItemWeight (int i, int j) {

   return item_weight[i][j];
};

int DataProblem::getItemWeightSize () {

   return item_weight.size();
};

int DataProblem::getItemWeightSize (int i) {

   return item_weight[i].size();
};

vector<float> DataProblem::getKnapsackWeight () {

   return knapsack_weight;
};

float DataProblem::getKnapsackWeight (int i) {

   return knapsack_weight[i];
};

int DataProblem::getKnapsackWeightSize () {

   return knapsack_weight.size();
};

bool DataProblem::ReadFile (string file_name) {

   ifstream file (file_name, ifstream::in);

   if (file.fail())
      return false;

   string text;

   int problems = -1;

   int items = -1;
   int dimensions = -1;

   getline(file, text);

   problems = stoi(text);

   for (int i = 0; i < problems && !file.eof(); ++i) {      // Revisar

      getline(file, text);       // Discard blank line between problems

      ReadInstanceParameters (file, items, dimensions);

      ReadItemsValue (file, items, dimensions);

      ReadItemsWeight (file, items, dimensions);

      ReadKnapsackWeight (file, dimensions);

      num_dimensions.push_back(dimensions);

      for (int i = 0; i < dimensions; ++i) {

         num_items.push_back(items);
      }

      num_problems += dimensions;
   }

   file.close();

   return true;
};

// PRE: data must be clear
bool DataProblem::ReadColumns (ifstream &file, vector<float> &data, int &max_iterations) {

   string text;

   for (int i = 0; i < (max_iterations - 1); ++i) {

      getline(file, text, ' ');

      data.push_back(stof(text));
   }

   getline(file, text);
   data.push_back(stof(text));


   return !file.eof();
};

bool DataProblem::ReadInstanceParameters (ifstream &file, int &items, int &dimensions) {

   string text = "";

   getline(file, text, ' ');

   items = stoi(text);

   getline(file, text, ' ');


   dimensions = stoi(text);

   getline(file, text);

   return !file.eof();
};

bool DataProblem::ReadItemsValue (ifstream &file, int &items, int &dimensions) {

   bool more_text = true;

   vector<float> values;

   more_text = ReadColumns(file, values, items);

   for (int i = 0; i < dimensions; ++i) {

      item_value.push_back(values);
   }

   return more_text;
};

bool DataProblem::ReadItemsWeight (ifstream &file, int &items, int &dimensions) {

   bool more_text = true;

   vector<float> weights;

   for (int i = 0; i < dimensions && more_text; ++i) {

      weights.clear();

      more_text = ReadColumns(file, weights, items);

      item_weight.push_back(weights);
   }

   return more_text;
};

bool DataProblem::ReadKnapsackWeight (ifstream &file, int &dimensions) {

   return ReadColumns(file, knapsack_weight, dimensions);
}
