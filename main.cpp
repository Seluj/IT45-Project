#include <iostream>
#include "dataCollection.hpp"
#include "data.hpp"
#include "dataAnalysis.hpp"
#include "kMedoids.hpp"
#include "solution.hpp"
#include "genetic.hpp"

int main(int argc, char *argv[]) {

  std::string path = "../instances/200Missions-2centres/";;
  int printDetails;

  if (argc == 1) {
    std::cout << "No arguments given." << std::endl;
    std::cout << "Take default path: " << path << std::endl;
  } else if (argc == 2) {
    std::cout << "Take path: " << argv[1] << std::endl;
    path = argv[1];
  } else {
    std::cout << "To many arguments" << std::endl;
    std::cout << "Take default path: " << path << std::endl;
  }

  printf("Press enter to continue");
  getchar();

  printf("Would you like the details for the kMedoid operations? [enter 1 for yes and 0 for no]\n");
  std::cin >> printDetails;
  while (printDetails != 0 && printDetails != 1) {
    printf("Please enter either 1 or 0 [enter 1 for yes and 0 for no]\n");
    std::cin >>printDetails;
  }
  
  auto *dataColl = new dataCollection(path);

  auto *data1 = new data();
  auto *dataAnalysis1 = new dataAnalysis(dataColl, data1);
  
  dataAnalysis1->dataAnalysisPrint(data1);

  auto *kMedoids1 = new kMedoids(data1);
  kMedoids1->kMedoidsAlgo(data1, printDetails);

  auto *genetic1 = new genetic();

  auto *solution1 = new solution(data1, "Solution 1");
  auto *solution2 = new solution(data1, "Solution 2");
  auto *solution3 = new solution(data1, "Solution 3");
  auto *solution4 = new solution(data1, "Solution 4");
  auto *solution5 = new solution(data1, "Solution 5");


  solution1->initialSolution(data1);


  /* --------------------------------------- Mutation 1 --------------------------------------- */

  data1 = genetic1->mutateData(data1);
  std::cout << "Mutate data done 1" << std::endl;
  solution2->initialSolution(data1);
  //solution2->printSolution(data1);


  /* --------------------------------------- Mutation 2 --------------------------------------- */

  data1 = genetic1->mutateData(data1);
  std::cout << "Mutate data done 2" << std::endl;
  solution3->initialSolution(data1);
  //solution3->printSolution(data1);


  /* --------------------------------------- Mutation 3 --------------------------------------- */

  data1 = genetic1->mutateData(data1);
  std::cout << "Mutate data done 3" << std::endl;
  solution4->initialSolution(data1);
  //solution4->printSolution(data1);


  /* --------------------------------------- Mutation 4 --------------------------------------- */

  data1 = genetic1->mutateData(data1);
  std::cout << "Mutate data done 4" << std::endl;
  solution5->initialSolution(data1);
  //solution5->printSolution(data1);

  std::cout << "Best solution" << std::endl;



  solution1 = solution1->compareSolutions({solution1, solution2, solution3, solution4, solution5}, data1);
  //solution1 = solution1->compareSolutions(solution2, data1);
  solution1->printSolution(data1);
  std::cout << "nbAffectation :" << solution1->getNBAffectations(data1) << std::endl;
  std::cout << "Distance : " << solution1->getDistance(data1) << std::endl;
  std::cout << "nbSpeciality : " << solution1->getNBSpeciality(data1) << std::endl;
  printf("Press enter to continue");
  getchar();
  return 0;
}
