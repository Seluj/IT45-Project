/**
 * @file kMedoids.hpp
 * @brief Header file for class kMedoids
 * @date 02/06/2023
 *
 * Header file containing the definition of the class kMedoids
 */

#ifndef IT45_PROJECT_KMEDOIDS_HPP
#define IT45_PROJECT_KMEDOIDS_HPP

#include "inclusion.hpp"
#include "data.hpp"
#include "classes/center.hpp"

/**
 * @class kMedoids
 * @brief Class used to apply the k-medoids algorithm
 */
class kMedoids {

private:
  float cost;               // Cost of the solution
  float oldCost;            // Cost of the previous solution
  std::vector<int> medoids; // Vector of the medoids [their position in the distance matrix]
  /**
   * Matrix of the assignments
   * the rows indicate the medoids and in the columns we insert the assignment's position in the distance matrix
    */
  std::vector<std::vector<int>> assignments; //Matrix of assignments, according to the medoid

public:
  /* --------------------------------- Constructor --------------------------------- */

  kMedoids();

  kMedoids(data *data1);

  /* ----------------------------------- KMedoid ----------------------------------- */

  /**
   * @brief Function that applies the k-medoids algorithm
   * @param data1 Data object to use
   */
  void kMedoidsAlgo(data *data1, int printDetails);

  /**
   * @brief Function that assigns each assignment to the closest medoid
   * @param data1 Data object to use
   */
  void medoidsAssign(data *data1);

  /**
   * @brief Function that updates the medoids, by comparing costs in the cluster
   * @param data1 Data object to use
   * @return True if the medoids have changed, false otherwise
   */
  bool medoidsUpdate(data *data1);

  /**
   * @brief Function that calculates the cost of the solution
   * @param medoid the medoid to use
   * @param assignments the assignments of said medoid
   * @param data1 Data object to use
   * @return The cost of the solution
   */
  float calculateCost(int medoid, std::vector<int> assignments, data *data1); //Have to add parameters

  /**
   * @brief Function that prints the medoids and their assignments
   */
  void printMedoids(data *data1);
};


#endif //IT45_PROJECT_KMEANS_HPP
