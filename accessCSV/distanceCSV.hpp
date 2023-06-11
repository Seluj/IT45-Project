/**
 * @file distanceCSV.hpp
 * @brief Header file for class distanceCSV
 * @date 01/06/2023
 *
 * Header file containing the definition of the class distanceCSV
 * This class is used to read the distance.csv file and store the data in a 2D vector of floats
 */


#ifndef IT45_PROJECT_DISTANCECSV_HPP
#define IT45_PROJECT_DISTANCECSV_HPP

#include "../classes/distances.hpp"
#include "../csv.hpp"

/**
 * @class distanceCSV
 * @brief Class used to read the distance.csv file and store the data in a 2D vector of floats
 */
class distanceCSV {

private:
  distances *distancesMatrix; // Pointer to the distances class

public:

  /* --------------------------------- Constructor --------------------------------- */

  distanceCSV(const std::string &path);

  /* --------------------------------- Destructor --------------------------------- */

  ~distanceCSV();

  /* --------------------------------- Print Method --------------------------------- */

  void printMatrix();

  /* --------------------------------- Getters --------------------------------- */

  distances *getDistancesMatrix();
};


#endif //IT45_PROJECT_DISTANCECSV_HPP
