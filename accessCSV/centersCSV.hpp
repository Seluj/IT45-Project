/**
 * @file centersCSV.hpp
 * @brief Header file for class centersCSV
 * @date 01/06/2023
 *
 * Header file containing the definition of the class centersCSV
 * This class is used to read the centers.csv file and store the data in a vector of pointers to center objects
 */

#ifndef IT45_PROJECT_CENTERSCSV_HPP
#define IT45_PROJECT_CENTERSCSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"
#include "../classes/center.hpp"

/**
 * @class centersCSV
 * @brief Class used to read the centers.csv file and store the data in a vector of pointers to center objects
 */
class centersCSV {

private:
  std::vector<center *> centers;  // Vector of pointers to center objects
  int nbCenters;                  // Number of centers

public:

  /* --------------------------------- Constructor --------------------------------- */

  centersCSV(const std::string& path);

  /* --------------------------------- Destructor --------------------------------- */

  ~centersCSV();

  /* --------------------------------- Accessors --------------------------------- */

  std::vector<center *> getCenters();
  int getNbCenters();

  /* --------------------------------- Print Method --------------------------------- */

  void printCenters();
};


#endif //IT45_PROJECT_CENTERSCSV_HPP
