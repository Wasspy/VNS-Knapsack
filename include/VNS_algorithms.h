/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#inlcude <iostream>

using namespace std;

// Basic Variable Neighborhood Search algorithm
float BVNS (vector<bool> &solution, int num_neighborhood,
            float (*shaking_solution)(vector<bool>, vector<bool>, int),
            float (*improvement_solution)(vector<bool>, float, int),
            float (*select_neighborhood)(vector<bool>, vector<bool>, float, float, int));

// General Variable Neighborhood Search algorithm
float GVNS (vector<bool> &solution, int num_neighborhood,
            float (*shaking_solution)(vector<bool>, vector<bool>, int),
            float (*improvement_solution)(vector<bool>, float, int),
            float (*select_neighborhood)(vector<bool>, vector<bool>, float, float, int));
