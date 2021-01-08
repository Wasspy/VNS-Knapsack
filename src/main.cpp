/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      100000298@alumnos.uimp.es
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

void ReinitializeVector (double value, vector<double> &value_vector) {

   int size = value_vector.size();

   for (int i = 0; i < size; ++i) {

      value_vector[i] = value;
   }
}

int main (int argc, char *argv[]) {

   if (argc < 4) {

      cerr << "\n ERROR: Número de parámetros insuficientes. " << endl
           << "\t " << argv[0] << " <semilla> <ejecuciones> <nombre fichero>" << endl
           << "\t Ejemplo: " << argv[0] << "22 data/knapsack_01.txt "
           << endl << endl;

      exit (-1);
   }

   // Algorithm parameters
   srand(stoi(argv[1]));

   int iterations = stoi(argv[2]);

   string name = argv[3];

   int total_problems = 0;

   double solution_value;

   vector<bool> solution;
   vector<bool> initial_solution;

   vector<int> neighborhood_first_order {3,1,2};
   vector<int> neighborhood_second_order {3,1,9,2};

   // Time calculation
   auto start = system_clock::now();
   auto end = system_clock::now();

   duration<double,micro> duration = end - start;

   // Statistic
   vector<double> best_time(7,9999);
   vector<double> best_value(7,-1);

   vector<double> aux_time;
   vector<double> aux_value;

   vector<double> mean_times(7,0);
   vector<double> mean_values(7,0);

   vector<double> median_times(7,0);
   vector<double> median_values(7,0);

   vector<double> standard_deviation_times(7,0);
   vector<double> standard_deviation_values(7,0);

   vector<double> VND_first_times;
   vector<double> VND_second_times;
   vector<double> BVNS_first_times;
   vector<double> BVNS_second_times;
   vector<double> GVNS_first_times;
   vector<double> GVNS_second_times;
   vector<double> GVNS_third_times;

   vector<double> VND_first_values;
   vector<double> VND_second_values;
   vector<double> BVNS_first_values;
   vector<double> BVNS_second_values;
   vector<double> GVNS_first_values;
   vector<double> GVNS_second_values;
   vector<double> GVNS_third_values;

   DataProblem data(name);

   total_problems = data.getNumProblems();

   cout << "Instances,VND_2s,VND_4s,BVNS_2s,BVNS_4s,GVNS_2s,GVNS_4s,GVNS_4s_2s";

   for (int i = 0; i < total_problems; ++i) {

      ReinitializeVector(0, mean_times);
      ReinitializeVector(0, mean_values);

      ReinitializeVector(-1, best_value);
      ReinitializeVector(9999, best_time);

      VND_first_times.clear();  VND_second_times.clear();
      BVNS_first_times.clear(); BVNS_second_times.clear();
      GVNS_first_times.clear(); GVNS_second_times.clear(); GVNS_third_times.clear();

      VND_first_values.clear();  VND_second_values.clear();
      BVNS_first_values.clear(); BVNS_second_values.clear();
      GVNS_first_values.clear(); GVNS_second_values.clear(); GVNS_third_values.clear();

      for (int j = 0; j < iterations; ++j) {

         initial_solution = Greedy(data, i);

         // Create 2 different classes with 2 different neighborhoods order
         // First order -> change 2 - swap 2 (1 pair) - change 1
         VNS vns_first_order(data.getKnapsackWeight(i), data.getItemValue(i),
                             data.getItemWeight(i), initial_solution,
                             neighborhood_first_order);

         // Second order -> change 2 - swap 4 (2 pairs) - change 1
         VNS vns_second_order(data.getKnapsackWeight(i), data.getItemValue(i),
                             data.getItemWeight(i), initial_solution,
                             neighborhood_second_order);

         // VND with 1st order
         start = system_clock::now();
         solution_value = VND(vns_first_order, solution);
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

         VND_first_values.push_back(solution_value);
         VND_first_times.push_back(duration.count());

         // VND with 2nd order
         start = system_clock::now();
         solution_value = VND(vns_second_order, solution);
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

         VND_second_values.push_back(solution_value);
         VND_second_times.push_back(duration.count());


         vns_first_order.setSolution(initial_solution);
         vns_first_order.setIndexNeighborhood(0);

         vns_second_order.setSolution(initial_solution);
         vns_second_order.setIndexNeighborhood(0);

         // BVNS with 1st order
         start = system_clock::now();
         solution_value = BVNS(vns_first_order, solution);
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

         BVNS_first_values.push_back(solution_value);
         BVNS_first_times.push_back(duration.count());

         // BVNS with 2nd order
         start = system_clock::now();
         solution_value = BVNS(vns_second_order, solution);
         end = system_clock::now();

         duration = end - start;

         if (solution_value > best_value[3]) {

            best_value[3] = solution_value;
         }

         if (duration.count() < best_time[3]) {

            best_time[3] = duration.count();
         }

         mean_values[3] += solution_value;
         mean_times[3] += duration.count();

         BVNS_second_values.push_back(solution_value);
         BVNS_second_times.push_back(duration.count());


         vns_first_order.setSolution(initial_solution);
         vns_first_order.setIndexNeighborhood(0);

         vns_second_order.setSolution(initial_solution);
         vns_second_order.setIndexNeighborhood(0);

         // GVNS with 1st order - VND with 1st order
         start = system_clock::now();
         solution_value = GVNS(vns_first_order, solution);
         end = system_clock::now();

         duration = end - start;

         if (solution_value > best_value[4]) {

            best_value[4] = solution_value;
         }

         if (duration.count() < best_time[4]) {

            best_time[4] = duration.count();
         }

         mean_values[4] += solution_value;
         mean_times[4] += duration.count();

         GVNS_first_values.push_back(solution_value);
         GVNS_first_times.push_back(duration.count());

         // GVNS with 2nd order - VND with 2nd order
         start = system_clock::now();
         solution_value = GVNS(vns_second_order, solution);
         end = system_clock::now();

         duration = end - start;

         if (solution_value > best_value[5]) {

            best_value[5] = solution_value;
         }

         if (duration.count() < best_time[5]) {

            best_time[5] = duration.count();
         }

         mean_values[5] += solution_value;
         mean_times[5] += duration.count();

         GVNS_second_values.push_back(solution_value);
         GVNS_second_times.push_back(duration.count());

         // GVNS with 2nd order - VND with 1st order
         start = system_clock::now();
         solution_value = GVNS(vns_second_order, solution, neighborhood_first_order);
         end = system_clock::now();

         duration = end - start;

         if (solution_value > best_value[6]) {

            best_value[6] = solution_value;
         }

         if (duration.count() < best_time[6]) {

            best_time[6] = duration.count();
         }

         mean_values[6] += solution_value;
         mean_times[6] += duration.count();

         GVNS_third_values.push_back(solution_value);
         GVNS_third_times.push_back(duration.count());

      }

      cout << "\n(mean_values) P" << i + 1;

      for (int k = 0; k < mean_values.size(); ++k) {

         mean_values[k] /= iterations;

         cout << "," << mean_values[k];
      }

      cout << "\n(value_median) P" << i + 1;

      ReinitializeVector(0, median_values);

      sort(VND_first_values.begin(),   VND_first_values.end());
      sort(VND_second_values.begin(),  VND_second_values.end());
      sort(BVNS_first_values.begin(),  BVNS_first_values.end());
      sort(BVNS_second_values.begin(), BVNS_second_values.end());
      sort(GVNS_first_values.begin(),  GVNS_first_values.end());
      sort(GVNS_second_values.begin(), GVNS_second_values.end());
      sort(GVNS_third_values.begin(),  GVNS_third_values.end());

      median_values[0] = (VND_first_values[iterations/2]  + VND_first_values[iterations/2 - 1]) / 2;
      median_values[1] = (VND_second_values[iterations/2]  + VND_second_values[iterations/2 - 1]) / 2;
      median_values[2] = (BVNS_first_values[iterations/2] + BVNS_first_values[iterations/2 - 1]) / 2;
      median_values[3] = (BVNS_second_values[iterations/2] + BVNS_second_values[iterations/2 - 1]) / 2;
      median_values[4] = (GVNS_first_values[iterations/2] + GVNS_first_values[iterations/2 - 1]) / 2;
      median_values[5] = (GVNS_second_values[iterations/2] + GVNS_second_values[iterations/2 - 1]) / 2;
      median_values[6] = (GVNS_third_values[iterations/2] + GVNS_third_values[iterations/2 - 1]) / 2;

      cout << "," << median_values[0] << "," << median_values[1] << "," << median_values[2]
           << "," << median_values[3] << "," << median_values[4] << "," << median_values[5]
           << "," << median_values[6];

      cout << "\n(value_sd) P" << i + 1;

      ReinitializeVector(0, standard_deviation_values);

      for (int k = 0; k < VND_first_values.size(); ++k) {

         standard_deviation_values[0] += (VND_first_values[k] - mean_values[0])   * (VND_first_values[k] - mean_values[0]);
         standard_deviation_values[1] += (VND_second_values[k] - mean_values[1])  * (VND_second_values[k] - mean_values[1]);
         standard_deviation_values[2] += (BVNS_first_values[k] - mean_values[2])  * (BVNS_first_values[k] - mean_values[2]);
         standard_deviation_values[3] += (BVNS_second_values[k] - mean_values[3]) * (BVNS_second_values[k] - mean_values[3]);
         standard_deviation_values[4] += (GVNS_first_values[k] - mean_values[4])  * (GVNS_first_values[k] - mean_values[4]);
         standard_deviation_values[5] += (GVNS_second_values[k] - mean_values[5]) * (GVNS_second_values[k] - mean_values[5]);
         standard_deviation_values[6] += (GVNS_third_values[k] - mean_values[6])  * (GVNS_third_values[k] - mean_values[6]);
      }

      standard_deviation_values[0] = sqrt(standard_deviation_values[0] / iterations);
      standard_deviation_values[1] = sqrt(standard_deviation_values[1] / iterations);
      standard_deviation_values[2] = sqrt(standard_deviation_values[2] / iterations);
      standard_deviation_values[3] = sqrt(standard_deviation_values[3] / iterations);
      standard_deviation_values[4] = sqrt(standard_deviation_values[4] / iterations);
      standard_deviation_values[5] = sqrt(standard_deviation_values[5] / iterations);
      standard_deviation_values[6] = sqrt(standard_deviation_values[6] / iterations);

      cout << "," << standard_deviation_values[0] << "," << standard_deviation_values[1]
           << "," << standard_deviation_values[2] << "," << standard_deviation_values[3]
           << "," << standard_deviation_values[4] << "," << standard_deviation_values[5]
           << "," << standard_deviation_values[6];

      cout << "\n(best_value) P" << i + 1 << "," << best_value[0] << "," << best_value[1]
           << "," << best_value[2] << "," << best_value[3] << "," << best_value[4]
           << "," << best_value[5] << "," << best_value[6];

      cout << "\n(mean_times) P" << i + 1;

      for (int k = 0; k < mean_times.size(); ++k) {

       mean_times[k] /= iterations;

       cout << "," << mean_times[k];
      }

      cout << "\n(value_median) P" << i + 1;

      ReinitializeVector(0, median_times);

      sort(VND_first_times.begin(),   VND_first_times.end());
      sort(VND_second_times.begin(),  VND_second_times.end());
      sort(BVNS_first_times.begin(),  BVNS_first_times.end());
      sort(BVNS_second_times.begin(), BVNS_second_times.end());
      sort(GVNS_first_times.begin(),  GVNS_first_times.end());
      sort(GVNS_second_times.begin(), GVNS_second_times.end());
      sort(GVNS_third_times.begin(),  GVNS_third_times.end());

      median_times[0] = (VND_first_times[iterations/2]  + VND_first_times[iterations/2 - 1]) / 2;
      median_times[1] = (VND_second_times[iterations/2]  + VND_second_times[iterations/2 - 1]) / 2;
      median_times[2] = (BVNS_first_times[iterations/2] + BVNS_first_times[iterations/2 - 1]) / 2;
      median_times[3] = (BVNS_second_times[iterations/2] + BVNS_second_times[iterations/2 - 1]) / 2;
      median_times[4] = (GVNS_first_times[iterations/2] + GVNS_first_times[iterations/2 - 1]) / 2;
      median_times[5] = (GVNS_second_times[iterations/2] + GVNS_second_times[iterations/2 - 1]) / 2;
      median_times[6] = (GVNS_third_times[iterations/2] + GVNS_third_times[iterations/2 - 1]) / 2;

      cout << "," << median_times[0] << "," << median_times[1] << "," << median_times[2]
           << "," << median_times[3] << "," << median_times[4] << "," << median_times[5]
           << "," << median_times[6];

      cout << "\n(time_sd) P" << i + 1;

      ReinitializeVector(0, standard_deviation_times);

      for (int k = 0; k < VND_first_times.size(); ++k) {

       standard_deviation_times[0] += (VND_first_times[k] - mean_times[0])   * (VND_first_times[k] - mean_times[0]);
       standard_deviation_times[1] += (VND_second_times[k] - mean_times[1])  * (VND_second_times[k] - mean_times[1]);
       standard_deviation_times[2] += (BVNS_first_times[k] - mean_times[2])  * (BVNS_first_times[k] - mean_times[2]);
       standard_deviation_times[3] += (BVNS_second_times[k] - mean_times[3]) * (BVNS_second_times[k] - mean_times[3]);
       standard_deviation_times[4] += (GVNS_first_times[k] - mean_times[4])  * (GVNS_first_times[k] - mean_times[4]);
       standard_deviation_times[5] += (GVNS_second_times[k] - mean_times[5]) * (GVNS_second_times[k] - mean_times[5]);
       standard_deviation_times[6] += (GVNS_third_times[k] - mean_times[6])  * (GVNS_third_times[k] - mean_times[6]);
      }

      standard_deviation_times[0] = sqrt(standard_deviation_times[0] / iterations);
      standard_deviation_times[1] = sqrt(standard_deviation_times[1] / iterations);
      standard_deviation_times[2] = sqrt(standard_deviation_times[2] / iterations);
      standard_deviation_times[3] = sqrt(standard_deviation_times[3] / iterations);
      standard_deviation_times[4] = sqrt(standard_deviation_times[4] / iterations);
      standard_deviation_times[5] = sqrt(standard_deviation_times[5] / iterations);
      standard_deviation_times[6] = sqrt(standard_deviation_times[6] / iterations);

      cout << "," << standard_deviation_times[0] << "," << standard_deviation_times[1]
         << "," << standard_deviation_times[2] << "," << standard_deviation_times[3]
         << "," << standard_deviation_times[4] << "," << standard_deviation_times[5]
         << "," << standard_deviation_times[6];

      cout << "\n(best_time) P" << i + 1 << "," << best_time[0] << "," << best_time[1]
         << "," << best_time[2] << "," << best_time[3] << "," << best_time[4]
         << "," << best_time[5] << "," << best_time[6];
   }


   return 0;
}
