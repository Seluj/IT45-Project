#include <iostream>
#include "dataCollection.hpp"
#include "data.hpp"
#include "dataAnalysis.hpp"
#include "kMedoids.hpp"
#include "solution.hpp"
#include "genetic.hpp"

int main(int argc, char *argv[]) {

  std::string path = "../instances/66Missions-2centres/";;

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

  printf("Press enter to continue");
  getchar();


  auto *dataColl = new dataCollection(path);
  dataColl->printDataCollection();

  auto *data1 = new data();
  auto *dataAnalysis1 = new dataAnalysis(dataColl, data1);
  dataAnalysis1->dataAnalysisPrint(data1);
  kMedoids *kMedoids1 = new kMedoids(data1);
  kMedoids1->kMedoidsAlgo(data1);

  return 0;
}
