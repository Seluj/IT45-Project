/**
 * @file kMedoids.h
 * @brief Header file for class kMedoids
 * @date 02/06/2023
 *
 * Header file containing the definition of the class kMedoids
 */

#ifndef IT45_PROJECT_KMEDOIDS_HPP
#define IT45_PROJECT_KMEDOIDS_HPP

#include "data.hpp"
#include "classes/center.hpp"

/**
 * @class kMedoids
 * @brief Class used to apply the k-medoids algorithm
 */
class kMedoids {
public:
  /* --------------------------------- Constructor --------------------------------- */

  /**
   * @brief Constructor of the kMedoids class
   * @param data1 Data object to use
   */
  kMedoids(data* data1);

  /* --------------------------------- Destructor --------------------------------- */
  
  /* ----------------------------------- KMedoid ----------------------------------- */
  
  /**
   * @brief Function that applies the k-medoids algorithm
   * @param data1 Data object to use
   */
  void kMedoidsAlgo(data* data1);

  /**
   * @brief Function that assigns each mission to a center
  */
  void medoidsAssign();

  //Est ce que l'on update les medoids et on fait plusieurs itérations où est ce que l'on fait une seule itération ?
  //Ou sinon juste à chaque affectation d'une mission on update les medoids ?
  //Sinon retour sur l'utilisation de k-means (qui coute moins chère en compilation) et juste on calcul la position de chaque points
  void medoidsUpdate();
    
  void calculateCost();

  };


#endif //IT45_PROJECT_KMEANS_HPP
