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

int main (int argc, char *argv[]) {

   if (argc < 5) {

      cerr << "\n ERROR: Número de parámetros insuficientes. " << endl
           << "\t " << argv[0] << " <semilla> <nombre fichero> <orden entornos> <orden entornos VND del GVNS>" << endl
           << "\t Ejemplo: " << argv[0] << "22 data/knapsack_01.txt 1324 123"
           << endl << endl;

      exit (-1);
   }

   // Algorithm parameters
   srand(stoi(argv[1]));

   string name = argv[2];

   int order = stoi(argv[3]);
   int order_VND = stoi(argv[4]);
   int total_problems = 0;

   int num_neighborhood = 0;
   int vnd_num_neighborhood = 0;

   bool equal_vnd_order = (order == order_VND);

   float solution_value;

   vector<bool> solution;
   vector<bool> initial_solution;

   vector<int> neighborhood_order;
   vector<int> vnd_neighborhood_order;

   // Time calculation
   auto start = system_clock::now();
   auto end = system_clock::now();

   duration<float,micro> duration = end - start;

   // Statistic
   int iterations = 100;

   vector<float> best_time(4,-1);
   vector<float> best_value(4,-1);

   vector<float> VND_times;
   vector<float> BVNS_times;
   vector<float> GVNS_e_times;
   vector<float> GVNS_d_times;

   vector<float> VND_values;
   vector<float> BVNS_values;
   vector<float> GVNS_e_values;
   vector<float> GVNS_d_values;

   vector<float> time_mean(4,0);
   vector<float> value_mean(4,0);

   float median;
   float standard_deviation;

   DataProblem data(name);

   total_problems = (data.getNumProblems() <= 10) ? data.getNumProblems() : 10;

   int aux = order;

   num_neighborhood = 0;

   while (aux > 0) {

      ++num_neighborhood;

      aux = aux / 10;


      neighborhood_order.push_back(-1);
   }



   for (int i = num_neighborhood - 1; i > -1; --i) {

      neighborhood_order[i] = order % 10;

      order = order / 10;
   }

   if (equal_vnd_order) {

      vnd_neighborhood_order = neighborhood_order;

   } else {

      aux = order_VND;

      vnd_num_neighborhood = 0;

      while (aux > 0) {

         ++vnd_num_neighborhood;

         aux = aux / 10;

         vnd_neighborhood_order.push_back(-1);
      }

      for (int i = vnd_num_neighborhood - 1; i > -1; --i) {

         vnd_neighborhood_order[i] = order_VND % 10;

         order_VND = order_VND / 10;
      }
   }
   
   cout << "\n Semilla: " << stoi(argv[1])
        << "\n Fichero: " << argv[2]
        << "\n Problemas: " << total_problems
        << "\n Numero ejecuciones: " << iterations
        << "\n Orden de vecindario: " << stoi(argv[3])
        << "\n Orden de vecindario VND: " << stoi(argv[4])
        << endl;

   for (int i = 0; i < total_problems; ++i) {

      time_mean[0] = 0; time_mean[1] = 0; time_mean[2] = 0; time_mean[3] = 0;

      value_mean[0] = 0; value_mean[1] = 0; value_mean[2] = 0; value_mean[3] = 0;

      for (int j = 0; j < iterations; ++j) {

         start = system_clock::now();
         initial_solution = Greedy(data, i);
         //initial_solution = RandomSolution(data, i);
         end = system_clock::now();

         duration = end - start;


         VNS vns(data.getKnapsackWeight(i), data.getItemValue(i), data.getItemWeight(i),
                 initial_solution, neighborhood_order);

         solution_value = vns.getSolutionValue();

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

         value_mean[0] += solution_value;
         time_mean[0] += duration.count();

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

         value_mean[1] += solution_value;
         time_mean[1] += duration.count();

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

         value_mean[2] += solution_value;
         time_mean[2] += duration.count();

         GVNS_e_values.push_back(solution_value);
         GVNS_e_times.push_back(duration.count());

         if (!equal_vnd_order) {

            vns.setSolution(initial_solution);
            vns.setIndexNeighborhood(0);

            start = system_clock::now();
            solution_value = GVNS(vns, solution, vnd_neighborhood_order);
            end = system_clock::now();

            duration = end - start;

            if (solution_value > best_value[3]) {

               best_value[3] = solution_value;
            }

            if (duration.count() < best_time[3]) {

               best_time[3] = duration.count();
            }

            value_mean[3] += solution_value;
            time_mean[3] += duration.count();

            GVNS_d_values.push_back(solution_value);
            GVNS_d_times.push_back(duration.count());
         }
      }

      value_mean[0] /= 100; value_mean[1] /= 100; value_mean[2] /= 100; value_mean[3] /= 100;

      time_mean[0] /= 100; time_mean[1] /= 100; time_mean[2] /= 100; time_mean[3] /= 100;

      cout << "\n Problema " << i + 1 << ": "
           << "\n   VND: "
           << "\n\t Valor media: " << value_mean[0];

      sort(VND_values.begin(), VND_values.end());

      median = (VND_values[iterations/2] + VND_values[iterations/2 - 1]) / 2;

      cout << "\n\t Valor mediana: " << median;

      standard_deviation = 0;

      for (int j = 0; j < VND_values.size(); ++j) {

         standard_deviation += (VND_values[j] - value_mean[0]) * (VND_values[j] - value_mean[0]);
      }

      standard_deviation /= iterations;

      standard_deviation = sqrt(standard_deviation);

      cout << "\n\t Valor dt: " << standard_deviation
           << "\n\t Valor mejor: " << best_value[0]
           << "\n\n\t Tiempo media: " << time_mean[0];

      sort(VND_times.begin(), VND_times.end());

      median = (VND_times[iterations/2] + VND_times[iterations/2 - 1]) / 2;

      cout << "\n\t Tiempo mediana: " << median;

      standard_deviation = 0;

      for (int j = 0; j < VND_times.size(); ++j) {

         standard_deviation += (VND_times[j] - time_mean[0]) * (VND_times[j] - time_mean[0]);
      }

      standard_deviation /= iterations;

      standard_deviation = sqrt(standard_deviation);

      cout << "\n\t Tiempo dt: " << standard_deviation
           << "\n\t Tiempo mejor: " << best_time[0];


      cout << "\n   BVNS: "
           << "\n\t Valor media: " << value_mean[1];

      sort(BVNS_values.begin(), BVNS_values.end());

      median = (BVNS_values[iterations/2] + BVNS_values[iterations/2 - 1]) / 2;

      cout << "\n\t Valor mediana: " << median;

      standard_deviation = 0;

      for (int j = 0; j < BVNS_values.size(); ++j) {

      standard_deviation += (BVNS_values[j] - value_mean[1]) * (BVNS_values[j] - value_mean[1]);
      }

      standard_deviation /= iterations;

      standard_deviation = sqrt(standard_deviation);

      cout << "\n\t Valor dt: " << standard_deviation
           << "\n\t Valor mejor: " << best_value[1]
           << "\n\n\t Tiempo media: " << time_mean[1];

      sort(BVNS_times.begin(), BVNS_times.end());

      median = (BVNS_times[iterations/2] + BVNS_times[iterations/2 - 1]) / 2;

      cout << "\n\t Tiempo mediana: " << median;

      standard_deviation = 0;

      for (int j = 0; j < BVNS_times.size(); ++j) {

      standard_deviation += (BVNS_times[j] - time_mean[1]) * (BVNS_times[j] - time_mean[1]);
      }

      standard_deviation /= iterations;

      standard_deviation = sqrt(standard_deviation);

      cout << "\n\t Tiempo dt: " << standard_deviation
           << "\n\t Tiempo mejor: " << best_time[1];


      cout << "\n   GVNS: (VND igual)"
           << "\n\t Valor media: " << value_mean[2];

      sort(GVNS_e_values.begin(), GVNS_e_values.end());

      median = (GVNS_e_values[iterations/2] + GVNS_e_values[iterations/2 - 1]) / 2;

      cout << "\n\t Valor mediana: " << median;

      standard_deviation = 0;

      for (int j = 0; j < GVNS_e_values.size(); ++j) {

      standard_deviation += (GVNS_e_values[j] - value_mean[2]) * (GVNS_e_values[j] - value_mean[2]);
      }

      standard_deviation /= iterations;

      standard_deviation = sqrt(standard_deviation);

      cout << "\n\t Valor dt: " << standard_deviation
           << "\n\t Valor mejor: " << best_value[2]
           << "\n\n\t Tiempo media: " << time_mean[2];

      sort(GVNS_e_times.begin(), GVNS_e_times.end());

      median = (GVNS_e_times[iterations/2] + GVNS_e_times[iterations/2 - 1]) / 2;

      cout << "\n\t Tiempo mediana: " << median;

      standard_deviation = 0;

      for (int j = 0; j < GVNS_e_times.size(); ++j) {

      standard_deviation += (GVNS_e_times[j] - time_mean[2]) * (GVNS_e_times[j] - time_mean[2]);
      }

      standard_deviation /= iterations;

      standard_deviation = sqrt(standard_deviation);

      cout << "\n\t Tiempo dt: " << standard_deviation
           << "\n\t Tiempo mejor: " << best_time[2];


      if (!equal_vnd_order) {

          cout << "\n   GVNS: (VND distinto)"
               << "\n\t Valor media: " << value_mean[3];

          sort(GVNS_d_values.begin(), GVNS_d_values.end());

          median = (GVNS_d_values[iterations/2] + GVNS_d_values[iterations/2 - 1]) / 2;

          cout << "\n\t Valor mediana: " << median;

          standard_deviation = 0;

          for (int j = 0; j < GVNS_d_values.size(); ++j) {

             standard_deviation += (GVNS_d_values[j] - value_mean[3]) * (GVNS_d_values[j] - value_mean[3]);
          }

          standard_deviation /= iterations;

          standard_deviation = sqrt(standard_deviation);

          cout << "\n\t Valor dt: " << standard_deviation
               << "\n\t Valor mejor: " << best_value[3]
               << "\n\n\t Tiempo media: " << time_mean[3];

          sort(GVNS_d_times.begin(), GVNS_d_times.end());

          median = (GVNS_d_times[iterations/2] + GVNS_d_times[iterations/2 - 1]) / 2;

          cout << "\n\t Tiempo mediana: " << median;

          standard_deviation = 0;

          for (int j = 0; j < GVNS_d_times.size(); ++j) {

             standard_deviation += (GVNS_d_times[j] - time_mean[3]) * (GVNS_d_times[j] - time_mean[3]);
          }

          standard_deviation /= iterations;

          standard_deviation = sqrt(standard_deviation);

          cout << "\n\t Tiempo dt: " << standard_deviation
               << "\n\t Tiempo mejor: " << best_time[3] << endl;
      }

   }


   return 0;
}
