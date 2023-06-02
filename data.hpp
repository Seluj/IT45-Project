/**
 * @file data.hpp
 * @brief Header file for the data class
 * @date 01/06/2023
 *
 * Header file containing the definition of the data class
 * This class is used to store the data of the problem and will be modified by the different algorithms
 */

#ifndef IT45_PROJECT_DATA_HPP
#define IT45_PROJECT_DATA_HPP

#include <iostream>
#include <vector>
#include "classes/center.hpp"

/**
 * @class data
 * @brief Class used to store the data of the problem and will be modified by the different algorithms
 */
class data {

private:
  /*
   * Data about the centers
   * A center stores his id, his coordinates, his capacity and his employees
   */
  std::vector<center *> centers;    // Vector of pointers to center objects
  int nbCenters;                    // Number of centers

  /*
   * Data about the missions
   */
  std::vector<mission *> missions;  // Vector of pointers to mission objects
  int nbMissions;                   // Number of missions

  /*
   * Data about the matrix of distances
   */
  std::vector<std::vector<float>> matrix; // 2D vector of floats to store the matrix
  int nbRows;                             // Number of rows of the matrix
  int nbColumns;                          // Number of columns of the matrix

  friend class dataAnalysis;
};


#endif //IT45_PROJECT_DATA_HPP
