/**
 * @file kMedoids.hpp
 * @brief Header file for class kMedoids
 * @date 02/06/2023
 *
 * Header file containing the definition of the class kMedoids
 */

#ifndef IT45_PROJECT_KMEDOIDS_HPP
#define IT45_PROJECT_KMEDOIDS_HPP

#include "data.hpp"
#include "classes/center.hpp"
#include <vector>

/**
 * @class kMedoids
 * @brief Class used to apply the k-medoids algorithm
 */
class kMedoids {
private:
  float cost; // Cost of the solution
  float oldCost; // Cost of the previous solution
  std::vector<int> medoids; // Vector of the medoids
  /**
   * Matrix of the assignments
   * the rows indicate the medoids and in the columns we insert the assignment's position in the distance matrix
    */
  std::vector<std::vector<int>> assignments; 

public:
  /* --------------------------------- Constructor --------------------------------- */

  kMedoids();
  kMedoids(float cost, float oldCost, std::vector<int> medoids, std::vector<std::vector<int>> assignments);

  /* --------------------------------- Destructor --------------------------------- */
  
  /* ----------------------------------- KMedoid ----------------------------------- */
  
  /**
   * @brief Function that applies the k-medoids algorithm
   * @param data1 Data object to use
   */
  void kMedoidsAlgo(data* data1);

  /**
   * @brief Function that assigns each mission to a center
   * @param data1 Data object to use
  */
  void medoidsAssign(data* data1);

  void medoidsUpdate();
    
  float calculateCost(); //Have to add parameters

  void printMedoids();

  };


#endif //IT45_PROJECT_KMEANS_HPP
