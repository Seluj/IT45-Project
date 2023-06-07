//
// Created by jules on 02/06/2023.
//

#include "kMedoids.hpp"

/* ----------------------------------- Constructor ----------------------------------- */
    
kMedoids::kMedoids() {
  this->cost = 0;
  this->oldCost = std::numeric_limits<float>::max();
  this->medoids = std::vector<int>();
  this->assignments = std::vector<std::vector<int>>();
}

kMedoids::kMedoids(data* data1) {
  this->cost = 0;
  this->oldCost = std::numeric_limits<float>::max();
  this->assignments = std::vector<std::vector<int>>();
  this->medoids = std::vector<int>();
  for (int i = 0; i < data1->nbCenters; i++) {
    this->medoids.insert(this->medoids.begin(), i);
  }
}

/* ----------------------------------- KMedoid ----------------------------------- */

void kMedoids::kMedoidsAlgo(data* data1) {
  int i = 0; //Keeps track of the number of iterations
  //How many do we want to iterate?
  while (this->cost < this->oldCost && i < 4){
    //We reset the assignments
    this->assignments.clear();

    //We assign each mission to a center
    this->medoidsAssign(data1);

    //We calculate the cost of the new solution
    this->oldCost = this->cost;
    this->cost = 0;
    for (int j = 0; j < data1->nbCenters; j++) {//We cumulate the cost of each of our medoids
      this->cost += this->calculateCost(this->medoids[j], this->assignments[j], data1);
    }

    printMedoids();
        
    //We update the medoids, to choose the point in the cluster that minimizes the cost
    this->medoidsUpdate(data1);
    i++;
  }
}

void kMedoids::medoidsAssign(data* data1) {
  float distance;
  int row = NULL; //Keeps track of the distance row
  int tempAssign = NULL; //Position of the medoid the assignment has been assigned to [it's position in the distance matrix]
  int centerPos = NULL; //Position of the center, used to test if the center has the capacity for the mission [only used when assigning missions to medoids]

  //For the first i positions [i < nbCenters] we make sure that the medoid the assignment is compared to is not a center [We can't assign a center to a center]
  for (int i = 0; i < data1->nbCenters; i++) {
    distance = std::numeric_limits<float>::max(); //We reset the distance
    tempAssign = NULL;
    for (int j = 0; j < data1->nbCenters; j++) {

      //We verify that we haven't already assigned a center to this medoid
      if (this->assignments[j].empty() == true) {

        //We check that the row is not the one belonging to a medoid
        if (row == this->medoids[j]) {
          row++;
        }

        //We check that the medoid isn't a center to avoid assigning a center to a center
        if (this->medoids[j] > data1->nbCenters) {

          //We make sure the center has the capacity for this mission
          if (data1->centers[row]->getCapacity(data1->missions[this->medoids[j] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[j] - data1->nbCenters]->getStartingPeriod()) > 0) {
                        
            if (data1->distancesMatrix->getDistance(row, this->medoids[j]) < distance) { //We compare the distance between the assignment and the medoid with the smallest distant previously found
              distance = data1->distancesMatrix->getDistance(row, medoids[j]); //New smallest distance
              tempAssign = j; //Keep track of the new best medoid
            }
          }
        }
      }
    }

    //We assign the assignment to the medoid
    this->assignments[tempAssign].insert(this->assignments[tempAssign].end(),row);
    //We update the capacity of the center
    data1->centers[i]->updateCapacity(data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getStartingPeriod());
    row++; //We increment the row
  }
    
  //Now we move on to assinging the missions to the medoids
  for (int i = data1->nbCenters-1; i < data1->nbMissions; i++) { //We iterate over the assignments, we know these ones are missions
    distance = std::numeric_limits<float>::max(); //We reset the distance
    tempAssign = NULL;
    centerPos = NULL;

    for (int j = 0; j < data1->nbCenters; j++) { //We iterate over the medoids

      //We check that the position of our i is not on a medoid
      if (row == this->medoids[j]) {
        row ++;
      }

      /** When assigning to a medoid we have to check the center capacity
       * There are two possibilities: either the medoid itself is a center
       * or one of it's assignments is a center
       * So we have to check both cases
       */
      if (this->medoids[j] < data1->nbCenters) { //If the medoid is a center
        centerPos = this->medoids[j];
      } else { //If the medoid isn't a center, then it's 1 assignment is the center, that's what we'll use to test the capacity
        centerPos = this->assignments[j][0];
      }
            
      //Check that the medoid [Or the center assigned to this medoid] has enough capacity to take on the mission
      if (data1->centers[centerPos]->getCapacity(data1->missions[this->medoids[row] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[row] - data1->nbCenters]->getStartingPeriod()) > 0) {
        if (data1->distancesMatrix->getDistance(row, this->medoids[j]) < distance) { //We compare the distance between the mission and the medoid with the smallest distant previously found
          distance = data1->distancesMatrix->getDistance(row, medoids[j]);
          tempAssign = this->medoids[j]; //Keep track of new best medoid assignment
        }
      }
    }

    //We assign the assignment to the medoid
    this->assignments[tempAssign].insert(this->assignments[tempAssign].end(),row);
    //Change the capacity of the center
    if (this->medoids[tempAssign] < data1->nbCenters) { //If the medoid is a center
      data1->centers[centerPos]->updateCapacity(data1->missions[this->medoids[row] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[row] - data1->nbCenters]->getStartingPeriod());
    } else { //If the medoid isn't a center, then it's 1 assignment is the center, that's what we'll use to test the capacity
      data1->centers[this->assignments[tempAssign][0]]->updateCapacity(data1->missions[this->medoids[row] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[row] - data1->nbCenters]->getStartingPeriod());
    }
    row++; //We increment the row
  }
}

void kMedoids::medoidsUpdate(data* data1){
  /**For each or our medoid we calculate all possible costs
   * Meaning for each assignment we calculate the cost we would have if it was the medoid
   * We then compare the cost of the current medoid with the cost of the new medoid, and choose the smallest one as our new medoid
   */
  float cost = std::numeric_limits<float>::max();
  float oldCost = 0;
  int tempMedoid = NULL; //Position of the medoid we're testing, pos in distance matrix
  int bestMedoid = NULL; //Position of the best medoid, pos in distance matrix
  std::vector<int> bestAssignments; //Assignments of the best medoid
  std::vector<int> tempAssignments; //Assignments of the medoid we're testing

  for (int i = 0; i < data1->nbCenters; i++) {//Iterate over the medoids
    oldCost = calculateCost(this->medoids[i], this->assignments[i], data1); //We set the cost of the current medoid

    for (int j = 0; j < this->assignments[i].size(); j++) {//Iterates over the assignments of the medoid
      tempMedoid = this->assignments[i][j]; //We get the medoid we're testing
      tempAssignments = this->assignments[i]; //We copy the assignments of the old medoid
      tempAssignments[j] = this->medoids[i]; //We change the assignment that contained the position of the medoid being tested, to the position of the old medoid
      cost = calculateCost(tempMedoid, tempAssignments, data1); //We calculate the cost of the medoid we're testing
      if (cost < oldCost) {//If this medoid is better than the old one
        bestMedoid = tempMedoid; //We set the best medoid to the one we're testing
        bestAssignments = tempAssignments; //We set the best assignments to the ones of the medoid we're testing
        oldCost = cost; //We set the old cost to the cost of the medoid we're testing
      }
    }
    //We change the medoids and assignments with our new (or old) best values
    this->medoids[i] = bestMedoid;
    this->assignments[i] = bestAssignments;
  }
}
    
float kMedoids::calculateCost(int medoid, std::vector<int> assignments, data* data1){
  float cost = 0;
  //We iterate over the assignments and add the distance between the medoid and the assignment
  for (int i = 0; i < assignments.size(); i++){
    cost += data1->distancesMatrix->getDistance(medoid, assignments[i]);
  }
  return cost;
}

void kMedoids::printMedoids(){
  printf("Assignments for each Medoid : \n");
  for (int i = 0; i < this->medoids.size(); i++){ //We iterate over the medoids
    printf("Medoid : %d ", this->medoids[i]);
    for (int j = 0; j < this->assignments[i].size() ; j++) {//We iterate over the assignments
      printf("%d ", this->assignments[i][j]);
    }
    printf("\n");
  }
  std::cout << std::endl;
}