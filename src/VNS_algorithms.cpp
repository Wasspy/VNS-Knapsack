/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <vector>

#include "VNS_algorithms.h"

using namespace std;

// Greedy: best option in each step
vector<bool> Greedy (DataProblem &data, int id_problem) {

   int size = data.getNumItems(id_problem);

   int id_max = 0;
   float value_max = data.getItemWeight(id_problem, 0);

   float weight = 0;
   float total_weight = 0;
   float max_weight = data.getKnapsackWeight(id_problem);

   bool end_greedy = false;

   vector<bool> solution(size, 0);

   while (!end_greedy) {

      id_max = -1;
      value_max = -1;

      for (int i = 0; i < size; ++i) {

         if (!solution[i] && data.getItemValue(id_problem, i) > value_max &&
             (total_weight + data.getItemWeight(id_problem, i) <= max_weight)) {

            id_max = i;
            value_max = data.getItemValue(id_problem, i);
         }
      }

      if (id_max > -1) {

         weight = data.getItemWeight(id_problem, id_max);

         solution[id_max] = !solution[id_max];
         total_weight += weight;

      } else {

         end_greedy = true;
      }
   }

   return solution;
};

vector<bool> RandomSolution (DataProblem &data, int id_problem) {

   int size = data.getNumItems(id_problem);

   int rand_id = -1;

   float weight = 0;
   float total_weight = 0;
   float max_weight = data.getKnapsackWeight(id_problem);

   bool end_greedy = false;
   bool end_for = false;

   vector<bool> solution(size, 0);

   while (!end_greedy) {

      end_for = false;

      for (int i = 0; i < size && !end_for; ++i) {

         rand_id = rand() % solution.size();

         if (!solution[rand_id] &&
             (total_weight + data.getItemWeight(id_problem, rand_id) <= max_weight)) {

            end_for = true;
         }
      }

      if (end_for) {

         weight = data.getItemWeight(id_problem, rand_id);

         solution[rand_id] = !solution[rand_id];
         total_weight += weight;

      } else {

         end_greedy = true;
      }
   }

   return solution;
};

// Variable Neighborhood Descent algorithm
float VND (VNS &vns, vector<bool> &final_solution) {

   float new_value = 0;
   vector<bool> new_solution;

   do {

      new_solution = vns.getSolution();

      new_value = vns.getSolutionValue();


      new_value = vns.SolutionImprovement(new_solution, new_value);

      vns.SelectNeighborhood(new_solution, new_value);

   } while (vns.getIndexNeighborhood() < vns.getNumNeighborhood());

   final_solution = vns.getSolution();

   return vns.getSolutionValue();

};


// Basic Variable Neighborhood Search algorithm
float BVNS (VNS &vns, vector<bool> &final_solution, bool first_better) {

   float new_value = 0;
   vector<bool> new_solution;

   do {

      new_value = vns.ShakingSolution(new_solution);

      new_value = vns.SolutionImprovement(new_solution, new_value, first_better);

      vns.SelectNeighborhood(new_solution, new_value);

   } while (vns.getIndexNeighborhood() < vns.getNumNeighborhood());

   final_solution = vns.getSolution();

   return vns.getSolutionValue();

};

// General Variable Neighborhood Search algorithm (VND with similar neighborhoods)
float GVNS (VNS &vns, vector<bool> &final_solution) {

   float new_value = 0;

   vector<bool> new_solution;

   VNS vns_vnd(vns.getKnapsackWeight(), vns.getItemsValue(), vns.getItemsWeight(),
           vns.getSolution(), vns.getNeighborhood());

   do {

      new_value = vns.ShakingSolution(new_solution);

      vns_vnd.setSolution(new_solution);
      vns_vnd.setIndexNeighborhood(0);

      new_value = VND (vns_vnd, new_solution);

      vns.SelectNeighborhood(new_solution, new_value);

   } while (vns.getIndexNeighborhood() < vns.getNumNeighborhood());

   final_solution = vns.getSolution();

   return vns.getSolutionValue();

};

// General Variable Neighborhood Search algorithm (VND with different neighborhoods)
float GVNS (VNS &vns, vector<bool> &final_solution, vector<int> &neighborhood_order) {

   float new_value = 0;

   vector<bool> new_solution;

   VNS vns_vnd(vns.getKnapsackWeight(), vns.getItemsValue(), vns.getItemsWeight(),
           vns.getSolution(), neighborhood_order);

   do {

      new_value = vns.ShakingSolution(new_solution);

      vns_vnd.setSolution(new_solution);
      vns_vnd.setIndexNeighborhood(0);

      new_value = VND (vns_vnd, new_solution);

      vns.SelectNeighborhood(new_solution, new_value);

   } while (vns.getIndexNeighborhood() < vns.getNumNeighborhood());

   final_solution = vns.getSolution();

   return vns.getSolutionValue();

   };
