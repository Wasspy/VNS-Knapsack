/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <math.h>

#include "VNS_algorithms.h"

using namespace std;
using namespace chrono;

void getOrderNeighborhood (int order, vector<int> &order_vector) {

   int aux_order = order;
   int num_neighborhood = 0;

   order_vector.clear();

   while (aux_order > 0) {

      ++num_neighborhood;

      aux_order = aux_order / 10;

      order_vector.push_back(-1);
   }

   for (int i = num_neighborhood - 1; i > -1; --i) {

      order_vector[i] = order % 10;

      order = order / 10;
   }
}

void ReinitializeVector (double value, vector<double> &value_vector) {

   int size = value_vector.size();

   for (int i = 0; i < size; ++i) {

      value_vector[i] = value;
   }
}

int main (int argc, char *argv[]) {

   if (argc < 6) {

      cerr << "\n ERROR: Número de parámetros insuficientes. " << endl
           << "\t " << argv[0] << " <semilla> <ejecuciones> <nombre fichero> <orden entornos> <orden entornos VND del GVNS>" << endl
           << "\t Ejemplo: " << argv[0] << "22 data/knapsack_01.txt 1324 123"
           << endl << endl;

      exit (-1);
   }

   // Algorithm parameters
   srand(stoi(argv[1]));

   int iterations = stoi(argv[2]);

   string name = argv[3];

   int order = stoi(argv[4]);
   int order_VND = stoi(argv[5]);

   int total_problems = 0;

   double solution_value;

   vector<bool> solution;
   vector<bool> initial_solution;

   vector<int> neighborhood_order;
   vector<int> vnd_neighborhood_order;

   // Time calculation
   auto start = system_clock::now();
   auto end = system_clock::now();

   duration<double,micro> duration = end - start;

   // Statistic
   vector<double> best_time(3,9999);
   vector<double> best_value(3,-1);

   vector<double> aux_time;
   vector<double> aux_value;

   vector<double> mean_times(3,0);
   vector<double> mean_values(3,0);

   vector<double> median_times(3,0);
   vector<double> median_values(3,0);

   vector<double> standard_deviation_times(3,0);
   vector<double> standard_deviation_values(3,0);

   vector<double> VND_times;
   vector<double> BVNS_times;
   vector<double> GVNS_times;

   vector<double> VND_values;
   vector<double> BVNS_values;
   vector<double> GVNS_values;

   DataProblem data(name);

   total_problems = data.getNumProblems();

   getOrderNeighborhood(order, neighborhood_order);
   getOrderNeighborhood(order_VND, vnd_neighborhood_order);

   cout << "Instances,VND,BVNS,GVNS";

   for (int i = 0; i < total_problems; ++i) {

      ReinitializeVector(0, mean_times);
      ReinitializeVector(0, mean_values);

      ReinitializeVector(-1, best_value);
      ReinitializeVector(9999, best_time);

      ReinitializeVector(0, median_times);
      ReinitializeVector(0, median_values);

      ReinitializeVector(0, standard_deviation_times);
      ReinitializeVector(0, standard_deviation_values);

      VND_times.clear();  BVNS_times.clear();  GVNS_times.clear();
      VND_values.clear(); BVNS_values.clear(); GVNS_values.clear();

      for (int j = 0; j < iterations; ++j) {

         initial_solution = Greedy(data, i);

         VNS vns(data.getKnapsackWeight(i), data.getItemValue(i), data.getItemWeight(i),
                 initial_solution, neighborhood_order);

         start = system_clock::now();
         solution_value = VND(vns, solution);
         end = system_clock::now();

         duration = end - start;

         if (solution_value > best_value[0]) {

            best_value[0] = solution_value;
         }

         if (duration.count() < best_time[0]) {

            best_time[0] = duration.count();
         }

         mean_values[0] += solution_value;
         mean_times[0] += duration.count();

         VND_values.push_back(solution_value);
         VND_times.push_back(duration.count());

         vns.setSolution(initial_solution);
         vns.setIndexNeighborhood(0);

         start = system_clock::now();
         solution_value = BVNS(vns, solution);
         end = system_clock::now();

         duration = end - start;

         if (solution_value > best_value[1]) {

            best_value[1] = solution_value;
         }

         if (duration.count() < best_time[1]) {

            best_time[1] = duration.count();
         }

         mean_values[1] += solution_value;
         mean_times[1] += duration.count();

         BVNS_values.push_back(solution_value);
         BVNS_times.push_back(duration.count());

         vns.setSolution(initial_solution);
         vns.setIndexNeighborhood(0);

         start = system_clock::now();
         solution_value = GVNS(vns, solution);
         end = system_clock::now();

         duration = end - start;

         if (solution_value > best_value[2]) {

            best_value[2] = solution_value;
         }

         if (duration.count() < best_time[2]) {

            best_time[2] = duration.count();
         }

         mean_values[2] += solution_value;
         mean_times[2] += duration.count();

         GVNS_values.push_back(solution_value);
         GVNS_times.push_back(duration.count());

      }

      mean_times[0] /= 100; mean_times[1] /= 100; mean_times[2] /= 100; mean_times[3] /= 100;

      cout << "\n(mean_values) P" << i + 1;

      for (int k = 0; k < mean_values.size(); ++k) {

         mean_values[k] /= iterations;

         cout << "," << mean_values[k];
      }

      cout << "\n(value_median) P" << i + 1;

      sort(VND_values.begin(), VND_values.end());
      sort(BVNS_values.begin(), BVNS_values.end());
      sort(GVNS_values.begin(), GVNS_values.end());

      median_values[0] = (VND_values[iterations/2]  + VND_values[iterations/2 - 1]) / 2;
      median_values[1] = (BVNS_values[iterations/2] + BVNS_values[iterations/2 - 1]) / 2;
      median_values[2] = (GVNS_values[iterations/2] + GVNS_values[iterations/2 - 1]) / 2;

      cout << "," << median_values[0] << "," << median_values[1] << "," << median_values[2];

      cout << "\n(value_sd) P" << i + 1;

      ReinitializeVector(0, standard_deviation_values);

      for (int k = 0; k < VND_values.size(); ++k) {

         standard_deviation_values[0] += (VND_values[k] - mean_values[0])  * (VND_values[k] - mean_values[0]);
         standard_deviation_values[1] += (BVNS_values[k] - mean_values[1]) * (BVNS_values[k] - mean_values[1]);
         standard_deviation_values[2] += (GVNS_values[k] - mean_values[2]) * (GVNS_values[k] - mean_values[2]);
      }

      standard_deviation_values[0] = sqrt(standard_deviation_values[0] / iterations);
      standard_deviation_values[1] = sqrt(standard_deviation_values[1] / iterations);
      standard_deviation_values[2] = sqrt(standard_deviation_values[2] / iterations);

      cout << "," << standard_deviation_values[0] << "," << standard_deviation_values[1]
           << "," << standard_deviation_values[1];

      cout << "\n(best_value) P" << i + 1 << "," << best_value[0] << "," << best_value[1]
           << "," << best_value[2];

     cout << "\n(mean_times) P" << i + 1;

     for (int k = 0; k < mean_times.size(); ++k) {

        mean_times[k] /= iterations;

        cout << "," << mean_times[k];
     }

     cout << "\n(time_median) P" << i + 1;

     sort(VND_times.begin(), VND_times.end());
     sort(BVNS_times.begin(), BVNS_times.end());
     sort(GVNS_times.begin(), GVNS_times.end());

     median_times[0] = (VND_times[iterations/2]  + VND_times[iterations/2 - 1]) / 2;
     median_times[1] = (BVNS_times[iterations/2] + BVNS_times[iterations/2 - 1]) / 2;
     median_times[2] = (GVNS_times[iterations/2] + GVNS_times[iterations/2 - 1]) / 2;

     cout << "," << median_times[0] << "," << median_times[1] << "," << median_times[2];

     cout << "\n(time_sd) P" << i + 1;

     ReinitializeVector(0, standard_deviation_times);

     for (int k = 0; k < VND_times.size(); ++k) {

        standard_deviation_times[0] += (VND_times[k] - mean_times[0])  * (VND_times[k] - mean_times[0]);
        standard_deviation_times[1] += (BVNS_times[k] - mean_times[1]) * (BVNS_times[k] - mean_times[1]);
        standard_deviation_times[2] += (GVNS_times[k] - mean_times[2]) * (GVNS_times[k] - mean_times[2]);
     }

     standard_deviation_times[0] = sqrt(standard_deviation_times[0] / iterations);
     standard_deviation_times[1] = sqrt(standard_deviation_times[1] / iterations);
     standard_deviation_times[2] = sqrt(standard_deviation_times[2] / iterations);

     cout << "," << standard_deviation_times[0] << "," << standard_deviation_times[1]
          << "," << standard_deviation_times[1];

     cout << "\n(best_time) P" << i + 1 << "," << best_time[0] << "," << best_time[1]
          << "," << best_time[2];
   }


   return 0;
}
