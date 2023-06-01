#include <iostream>
#include "dataCollection.hpp"

int main() {

  auto *data = new dataCollection("../instances/30Missions-2centres/");
  data->printDataCollection();

  std::vector<employee> centre1;


  return 0;
}
