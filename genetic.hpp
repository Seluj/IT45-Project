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
   * @brief Mutate the data
   * @param data1 data to mutate
   * @return data1 mutated
   */
  data *mutateData(data *data1);

private:

  /**
   * @brief Switch the missions with the unmarked missions
   * @param data1 data to mutate
   * @return data1 mutated
   */
  data *switchWithUnmarkedMission(data *data1);
};

#endif //IT45_PROJECT_GENETIC_HPP
