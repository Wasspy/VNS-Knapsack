/*
   Máster Universitario en Investigación en Inteligencia Artificial
   Resolución de problemas con metaheurísticos

   Laura Rabadán Ortega      79088745W      100000298@alumnos.uimp.es
*/

#include <iostream>
#include <vector>
#include <random>

#include "instance_data.h"
//#include "VNS_functions.h"

using namespace std;

int main (int argc, char *argv[]) {

//   srand (22);

//   string name = "data/mknap1.txt";

//   DataProblem data(name);

   vector<int> orden;

   orden.push_back(3); orden.push_back(-1); orden.push_back(1); orden.push_back(2);

   cout << endl;

   for (int i = 1; i < 5; ++i) {
      for (int j = 0; j < 4; ++j) {

         if (orden[j] == i) {

            cout << " " << j;
         }
      }
   }

   orden.clear();
   orden.push_back(1); orden.push_back(1); orden.push_back(1); orden.push_back(1);
   cout << endl;

   for (int i = 1; i < 5; ++i) {
      for (int j = 0; j < 4; ++j) {

         if (orden[j] == i) {

            cout << " " << j;
         }
      }
   }

   orden.clear();
   orden.push_back(2); orden.push_back(2); orden.push_back(5); orden.push_back(2);
   cout << endl;

   for (int i = 1; i < 5; ++i) {
      for (int j = 0; j < 4; ++j) {

         if (orden[j] == i) {

            cout << " " << j;
         }
      }
   }

   return 0;
}
