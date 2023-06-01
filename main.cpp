#include <iostream>
#include "dataCollection.hpp"
#include "data.h"
#include "dataAnalysis.h"

int main() {

  auto *dataColl = new dataCollection("../instances/30Missions-2centres/");
  dataColl->printDataCollection();

  auto *data1 = new data();
  auto *dataAnalysis1 = new dataAnalysis(dataColl, data1);
  dataAnalysis1->dataAnalysisPrint(data1);



  return 0;
}
