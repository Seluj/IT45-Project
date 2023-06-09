#include <iostream>
#include "dataCollection.hpp"
#include "data.hpp"
#include "dataAnalysis.hpp"
#include "kMedoids.hpp"
#include "solution.hpp"

int main(int argc, char *argv[]) {

  std::string path = "../instances/30Missions-2centres/";;

  if (argc == 1) {
    printf("Take default path : ./instance/30Missions-2centres/\n");
  } else if (argc == 2){
    printf("Take path : %s\n", argv[1]);
    path = argv[1];
  } else {
    printf("To many arguments\n");
    printf("Take default path : ./instance/30Missions-2centres/\n");
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
