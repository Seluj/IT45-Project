/**
 * @file solution.hpp
 * @brief Header file containing the solution class
 * @date 08/06/2023
 * 
 * Header file containing the solution class
*/

#ifndef IT45_PROJECT_SOLUTION_HPP
#define IT45_PROJECT_SOLUTION_HPP

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include "data.hpp"
#include "kMedoids.hpp"


class solution {
private:
  /*
   * Affectations is a combination of two tables linked by an unordered_map
   */
  std::unordered_map<std::string, std::map<int, std::vector<std::map<int, bool>>>> affectations;


  float z; // objective function value
public:
  solution();
  solution(data *data);

  /**
   * Initialises a solution by using the smallest cost method
   * @param kMedoids1 Contains the missions affected to each center
   * @param data1 Information about our problem
   * @return the initial solution
   */
  solution initialSolution(kMedoids *kMedoids1, data *data1);
  ~solution();


  solution *compareSolutions(solution *newSolution, data *data);

  int compareNBAffectations(solution *newSolution, data *data);

  int compareDistance(solution *newSolution, data *data);

  int compareNBSpecialists(solution *newSolution, data *data);

  void printSolution(data *data);

};


#endif //IT45_PROJECT_SOLUTION_HPP
