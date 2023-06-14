#include <iostream>
#include "dataCollection.hpp"
#include "data.hpp"
#include "dataAnalysis.hpp"
#include "kMedoids.hpp"
#include "solution.hpp"
#include "genetic.hpp"

int main(int argc, char *argv[]) {

  std::string path = "../instances/200Missions-2centres/";
  int printDetails, nbSolutions;

  if (argc == 1) {
    std::cout << "No arguments given." << std::endl;
    std::cout << "Take default path: " << path << std::endl;
  } else if (argc == 2) {
    std::cout << "Take path: " << argv[1] << std::endl;
    path = argv[1];
  } else {
    std::cout << "To many arguments" << std::endl;
    std::cout << "Take default path: " << path << std::endl;
  }


  std::cout << "Would you like the details for the kMedoid operations? [enter 1 for yes and 0 for no]";
  std::cin >> printDetails;
  while (printDetails != 0 && printDetails != 1) {
    std::cout << "Please enter either 1 or 0 [enter 1 for yes and 0 for no]";
    std::cin >> printDetails;
  }

  std::cout << "How many solutions would you like to generate? (Between 1 and 50)" << std::endl
            << "(The more solutions, the longer the program will take and the greater the risk of a stack overflow will occur)"
            << std::endl << "(If you see \"Best solution\", the program is still running)";
  std::cin >> nbSolutions;
  while (nbSolutions < 1 || nbSolutions > 50) {
    std::cout << "Please enter a number greater than 0 or less than 50" << std::endl;
    std::cin >> nbSolutions;
  }

  if (printDetails == 1) {
    std::cout << "You have chosen to print the details of the kMedoid operations" << std::endl;
  } else {
    std::cout << "You have chosen not to print the details of the kMedoid operations" << std::endl;
  }
  std::cout << "You have chosen to generate " << nbSolutions << " solutions" << std::endl;

  std::cout << "Press enter to continue";
  fflush(stdin);
  getchar();

  auto *dataColl = new dataCollection(path);

  auto *data1 = new data();
  auto *dataAnalysis1 = new dataAnalysis(dataColl, data1);

  dataAnalysis1->dataAnalysisPrint(data1);

  auto *kMedoids1 = new kMedoids(data1);
  kMedoids1->kMedoidsAlgo(data1, printDetails);

  auto *genetic1 = new genetic();

  solution *bestSolution;
  std::vector<solution *> solutions;

  solutions.resize(nbSolutions);

  for (int i = 0; i < nbSolutions; i++) {
    solutions[i] = new solution(data1, "Solution " + std::to_string(i));
    solutions[i]->initialSolution(data1);
    data1 = genetic1->mutateData(data1);
  }

  std::cout << "============================================================" << std::endl;
  std::cout << "Best solution" << std::endl;


  bestSolution = bestSolution->compareSolutions(solutions, data1);

  bestSolution->printSolution(data1);
  std::cout << "Number of affectations :" << bestSolution->getNBAffectations(data1) << std::endl
            << "Cost : " << bestSolution->getDistance(data1) * 0.2 << std::endl
            << "Number of specialities : " << bestSolution->getNBSpeciality(data1) << std::endl << std::endl
            << "Press enter to continue";
  getchar();
  return 0;
}
