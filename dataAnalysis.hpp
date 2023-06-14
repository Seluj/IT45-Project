/**
 * @file dataAnalysis.hpp
 * @brief Header file for class dataAnalysis
 * @date 01/06/2023
 *
 * Header file containing the definition of the class dataAnalysis
 */

#ifndef IT45_PROJECT_DATAANALYSIS_HPP
#define IT45_PROJECT_DATAANALYSIS_HPP

#include "dataCollection.hpp"
#include "data.hpp"

/**
 * @class dataAnalysis
 * @brief Class used to analyze the data of the problem
 *
 * This class is used to analyze the data of the problem by taking a dataCollection object as input and and a data object as output
 */
class dataAnalysis {

public:

  /* --------------------------------- Constructor --------------------------------- */

  /**
   * @brief Constructor of the dataAnalysis class
   * @param d Collection of data to analyze
   * @param data1 Data object to store the analyzed data
   */
  dataAnalysis(dataCollection *dataInput, data *dataOutput);

  /* --------------------------------- Print Method --------------------------------- */

  /**
   * @brief Print the data of the problem
   * @param data1 Data object to print
   */
  void dataAnalysisPrint(data *data1);
};


#endif //IT45_PROJECT_DATAANALYSIS_HPP
