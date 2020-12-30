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
            float (*select_neighborhood)(vector<bool>, vector<bool>, float, float, int)) {

   int ind = 1;
   float value = 0, //ObjectiveFunction(solution),
         new_value = 0;

   vector<bool> new_solution;

   while (ind < num_neighborhood) {

      //new_value = ShakingSolution(solution, new_solution, ind);

      //new_value = ImprovementSolution(new_solution, new_value, ind);

      //value = SelectNeighborhood(solution, new_solution, value, new_value, ind);
   }

   return value;
};

// General Variable Neighborhood Search algorithm
float GVNS (vector<bool> &solution, int num_neighborhood,
            float (*shaking_solution)(vector<bool>, vector<bool>, int),
            float (*improvement_solution)(vector<bool>, float, int),
            float (*select_neighborhood)(vector<bool>, vector<bool>, float, float, int)) {

   int ind = 1;
   float value = 0, //ObjectiveFunction(solution),
         new_value = 0;

   vector<bool> new_solution;

   while (ind < num_neighborhood) {

      //new_value = ShakingSolution(solution, new_solution, ind);

      //new_value = ImprovementSolution(new_solution, new_value, ind);

      //value = SelectNeighborhood(solution, new_solution, value, new_value, ind);
   }

   return value;
};
