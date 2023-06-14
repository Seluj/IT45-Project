/**
 * @file solution.hpp
 * @brief Header file containing the solution class
 * @date 11/06/2023
 * 
 * Header file containing the solution class
*/

#ifndef IT45_PROJECT_SOLUTION_HPP
#define IT45_PROJECT_SOLUTION_HPP

#include "inclusion.hpp"
#include "data.hpp"
#include "kMedoids.hpp"


/**
 * @class solution
 * @brief Class used to store the solution of the problem
 */
class solution {

private:

  std::string name;

  /**
   * 1st key: skill [LSF, LPC]<br>
   * 2nd key: id of the employee<br>
   * 3rd key: day [0 - 4] 0 = Monday, 1 = Tuesday, 2 = Wednesday, 3 = Thursday, 4 = Friday<br>
   * 4th key: id of the mission<br><br>
   *
   * Example 1: affectations["LSF"][1][2][5] = true means that the employee 1 is affected to the mission 5 on the day 2<br>
   * Example 2: affectations["LPC"][2][3][1] = false means that the employee 2 is not affected to the mission 1 on the day 3
   */
  std::unordered_map<std::string, std::map<int, std::vector<std::map<int, bool>>>> affectations;


  /**
   * 1st key : id of the employee<br>
   * 2nd key : day [0 - 4] 0 = Monday, 1 = Tuesday, 2 = Wednesday, 3 = Thursday, 4 = Friday<br>
   * 3rd key : type : 0 = Number of hours, 1 = time range, 2 = start of work, 3 = end of work, 4 = id last mission, 5 = first mission, 6 = cost<br><br>
   *
   * Example 1: horaires[1][2][0] = 3 means that the employee 1 has 3 hours of work on the day 2<br>
   * Example 2: horaires[1][3][1] = 12 means that the employee 1 was at work 12 hours on the day 3<br>
   */
  std::map<int, std::vector<std::vector<int>>> hours;

public:

  solution(data *data, std::string name);

  /**
   * Initialises a solution by using the smallest cost method
   * @param kMedoids1 Contains the missions affected to each center
   * @param data1 Information about our problem
   * @return the initial solution
   */
  void initialSolution(data *data1);

  ~solution();

  /**
   * Compare two solution and return the best one
   * @param newSolution The new solution to compare
   * @param data Information about our problem
   * @return The best solution
   */
  solution *compareSolutions(solution *newSolution, data *data);

  solution *compareSolutions(std::vector<solution *> solutions, data *data);

  /**
   * Compare the number of affectations of two solutions
   * @param newSolution The new solution to compare
   * @param data Information about our problem
   * @return - 0 if the number of affectations of the new solution is greater than the number of affectations of the current solution<br>
   * - 1 if the number of affectations is equal<br>
   * - 2 if the number of affectations of the new solution is lower than the number of affectations of the current solution
   */
  int compareNBAffectations(solution *newSolution, data *data);

  /**
   * Compare the distance of two solutions
   * @param newSolution The new solution to compare
   * @param data Information about our problem
   * @return - 0 if the distance of the new solution is lower than the distance of the current solution<br>
   * - 1 if the distance is equal<br>
   * - 2 if the distance of the new solution is greater than the distance of the current solution
   */
  int compareDistance(solution *newSolution, data *data);

  /**
   * Compare the number of speciality covered of two solutions
   * @param newSolution The new solution to compare
   * @param data Information about our problem
   * @return - 0 if the number of speciality covered of the new solution is greater than the number of speciality covered of the current solution<br>
   * - 1 if the number of speciality covered is equal<br>
   * - 2 if the number of speciality covered of the new solution is lower than the number of speciality covered of the current solution
   */
  int compareNBSpeciality(solution *newSolution, data *data);

  /**
   * Print the solution
   * The function prints the affectations of each employee for each day and the number of hours worked by each employee for each day
   * @param data Information about our problem
   */
  void printSolution(data *data);

  /**
   * Utility function to count the number of affectations of an employee for a day
   * @param data Information about our problem
   * @param i The id of the employee
   * @param k The day
   * @return The number of affectations of the employee i for the day k
   */
  int countAffectations(data *data, int i, int k);

  /**
   * @brief Counts the number of hours worked by an employee for the week
   * @param idEmployee Id of the employee
   * @param days Number of days of the week you want to count the hours of
  */
  int minutesWeek(int idEmployee, int days);

  /**
   * @brief Checks if the employee has time to do the mission 
   * @param idEmployee Id of the employee
   * @param day Day of the mission
   * @param idMission Id of the mission
   * @param data Information about our problem
  */
  bool hasTime(int idEmployee, int day, int idMission, data *data, int center);

  /**
   * @bried Gets the number of affectations of the solution
   * @param data Information about our problem
   * @return The number of affectations of the solution
   */
  int getNBAffectations(data *data);

  /**
   * @brief Gets the distance of the solution
   * @param data Information about our problem
   * @return The distance of the solution
   */
  float getDistance(data *data);

  /**
   * @brief Gets the number of speciality covered of the solution
   * @param data
   * @return The number of speciality covered of the solution
   */
  int getNBSpeciality(data *data);
};


#endif //IT45_PROJECT_SOLUTION_HPP
