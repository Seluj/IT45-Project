#include <iostream>
#include "distanceMatrix.h"

int main() {
  /*
  readCSVFile file("../instances/94Missions-3centres/centers.csv");
  file.printTable();
  */

  distanceMatrix matrix("../instances/30Missions-2centres/");
  matrix.printMatrix();

  return 0;
}
