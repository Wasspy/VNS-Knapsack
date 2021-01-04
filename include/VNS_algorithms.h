/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <vector>

#include "instance_data.h"
#include "VNS_functions.h"

using namespace std;

// Greedy: best option in each step
vector<bool> Greedy (DataProblem &data, int id_problem);

vector<bool> RandomSolution (DataProblem &data, int id_problem);

// Variable Neighborhood Descent algorithm
float VND (VNS &vns, vector<bool> &final_solution);

// Basic Variable Neighborhood Search algorithm
float BVNS (VNS &vns, vector<bool> &final_solution, bool first_better = true);

// General Variable Neighborhood Search algorithm (VND with similar neighborhoods)
float GVNS (VNS &vns, vector<bool> &final_solution);

// General Variable Neighborhood Search algorithm (VND with different neighborhoods)
float GVNS (VNS &vns, vector<bool> &final_solution, vector<int> &neighborhood_order);
