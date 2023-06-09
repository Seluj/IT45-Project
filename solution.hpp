//
// Created by jules on 08/06/2023.
//

#ifndef IT45_PROJECT_SOLUTION_HPP
#define IT45_PROJECT_SOLUTION_HPP

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include "data.hpp"


class solution {
private:
  /*
   * Affectations is a combination of two tables linked by an unordered_map
   */
  std::unordered_map<std::string, std::map<int, std::map<int, int>>> affectations;

  std::unordered_map<std::string, std::vector<int>> correspondanceMission;
  std::unordered_map<std::string, std::vector<int>> correspondanceEmployee;

  int z; // objective function value
public:
  solution();
  solution(data *data);
  ~solution();

  void printSolution();
};


#endif //IT45_PROJECT_SOLUTION_HPP
