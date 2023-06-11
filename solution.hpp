/**
 * @file solution.hpp
 * @brief Header file containing the solution class
 * @date 10/06/2023
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
   * 1st key : skill [LSF, LPC]
   * 2nd key : id of the employee
   * 3rd key : day [0 - 4] 0 = Monday, 1 = Tuesday, 2 = Wednesday, 3 = Thursday, 4 = Friday
   * 4th key : id of the mission
   *
   * Example : affectations["LSF"][1][2][5] = true means that the employee 1 is affected to the mission 5 on the day 2
   * Example : affectations["LPC"][2][3][1] = false means that the employee 2 is not affected to the mission 1 on the day 3
   */
  std::unordered_map<std::string, std::map<int, std::vector<std::map<int, bool>>>> affectations;


  /*
   * 1st key : id of the employee
   * 2nd key : day [0 - 4] 0 = Monday, 1 = Tuesday, 2 = Wednesday, 3 = Thursday, 4 = Friday
   * 3rd key : type : 0 = Number of hours and 1 = time range
   *
   * Example : horaires[1][2][0] = 3 means that the employee 1 has 3 hours of work on the day 2
   * Example : horaires[1][3][1] = 12 means that the employee 1 was at work 12 hours on the day 3
   */
  std::map<int , std::vector<std::vector<int>>> hours;

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

  int countAffectations(data *data, int i, int k);
};


#endif //IT45_PROJECT_SOLUTION_HPP
