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
  std::vector<int> medoids; // Vector of the medoids
  std::vector<std::vector<int>> assignments; // Matrix of the assignments

public:
  /* --------------------------------- Constructor --------------------------------- */

  kMedoids();
  kMedoids(std::vector<int> medoids, std::vector<std::vector<int>> assignments);

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
    
  void calculateCost();

  };


#endif //IT45_PROJECT_KMEANS_HPP
