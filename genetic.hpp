/**
 * @file genetic.hpp
 * @brief Header file for genetic.cpp
 * @date 11/06/2023
 *
 * Header file containing the genetic class
 */

#ifndef IT45_PROJECT_GENETIC_HPP
#define IT45_PROJECT_GENETIC_HPP

#include "inclusion.hpp"
#include "solution.hpp"
#include "data.hpp"


class genetic {

public:

  /* ------------------------------ Constructors ----------------------------- */

  genetic();

  /* --------------------------------- Methods --------------------------------- */

  /**
   * @brief Function to create the initial population
   * @param data1 Data object containing the data of the problem
   * @param populationSize Size of the population
   * @return A vector of pointers to solution objects
   */
  data *mutateData(data *data1);

  /**
  * @brief Function to select the parents of the next generation
  * @param population Vector of pointers to solution objects
  * @param data1 Data object containing the data of the problem
  * @return A vector of pointers to solution objects
  */
  std::vector<solution *> selection(std::vector<solution *> population, data *data1);
};

#endif //IT45_PROJECT_GENETIC_HPP
