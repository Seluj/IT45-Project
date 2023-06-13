/**
 * @file kMedoids.cpp
 * @brief Source file for kMedoids.hpp
 * @date 02/06/2023
 * 
 * Source file containing the kMedoids class
*/

#include "kMedoids.hpp"

/* ----------------------------------- Constructor ----------------------------------- */
    
kMedoids::kMedoids() {
  this->cost = 1000;
  this->oldCost = std::numeric_limits<float>::max();
  this->medoids = std::vector<int>();
  this->assignments = std::vector<std::vector<int>>();
}

kMedoids::kMedoids(data* data1) {
  this->cost = 1000;
  this->oldCost = std::numeric_limits<float>::max();
  this->assignments = std::vector<std::vector<int>>(data1->nbCenters);
  this->medoids = std::vector<int>();
  for (int i = 0; i < data1->nbCenters; i++) {
      this->medoids.insert(this->medoids.end(), i);
  }
}

/* ----------------------------------- KMedoid ----------------------------------- */

void kMedoids::kMedoidsAlgo(data* data1, int printDetails) {
  int temp;
  int i = 0; //Keeps track of the number of iterations
  bool medoidsModified = true; //Keeps track of whether the medoids have been modified or not
  std::vector<std::unordered_map<std::string, std::vector<std::unordered_map<int, int>>>> capacityCopy(data1->nbCenters);
  //We have to copy the old capacities because we will be changing them during our assignments
  for (int j = 0; j < data1->nbCenters; ++j) {
      capacityCopy[j] = data1->centers[j]->getCapacity();
  }
  //We don't want to iterate too many times
  while (this->cost < this->oldCost && i < 10 && medoidsModified){
    if (printDetails == 1) {
      std::cout << "============== KMedoids iteration " << i+1 << "==============" << std::endl;
      std::cout << "Our medoids : ";
      for (int j = 0; j < data1->nbCenters; ++j) {
        std::cout << this->medoids[j] << " // ";
      }
      std::cout << std::endl;
    }
    
    //We reset the assignments and the capacities of each center
    for (int j = 0; j < data1->nbCenters; ++j) {
      this->assignments[j].clear();
      data1->centers[j]->updateCapacity(capacityCopy[j]);
    }

    //We assign each mission to a center
    this->medoidsAssign(data1);

    //We calculate the cost of the new solution
    this->oldCost = this->cost;
    this->cost = 0;
    for (int j = 0; j < data1->nbCenters; j++) {//We cumulate the cost of each of our medoids
      this->cost += this->calculateCost(this->medoids[j], this->assignments[j], data1);
    }
    if (printDetails == 1) {
      std::cout << std::endl << "Cost of this solution : " << this->cost << std::endl;
      printMedoids(data1);
    }
    //We update the medoids, to choose the point in the cluster that minimizes the cost
    medoidsModified = this->medoidsUpdate(data1);
    i++;
  }
  //We then reassign the centers as the medoid to facilitate the upcoming operations
  for(int j = 0; j < data1->nbCenters; j++){
    //If the medoid isn't a center, we replace it by the position of the center
    if (this->medoids[j] > data1->nbCenters){
      temp = this->assignments[j][0];
      this->assignments[j][0] = this->medoids[j];
      this->medoids[j] = temp;
    }
  }

  //Now that we have our final solution, we can definitely assign the missions to the centers, and update their "assigned" attribute
  std::unordered_map<std::string, std::vector<mission *>> newMissions;
  
  for (int j = 0; j < data1->nbCenters; j++) { //Iterate over the medoids
    newMissions["LSF"].clear();
    newMissions["LPC"].clear();
    for (int i = 0; i < this->assignments[j].size(); i++) { //Iterate over the assignments
      newMissions[data1->missions[this->assignments[j][i]-data1->nbCenters]->getSkill()].push_back(data1->missions[this->assignments[j][i]-data1->nbCenters]);
      data1->missions[this->assignments[j][i]-data1->nbCenters]->setAssigned(1);
    }
    data1->centers[this->medoids[j]]->updateMissions(newMissions);
  } 
}

void kMedoids::medoidsAssign(data* data1) {
  float distance;
  int row = 0; //Keeps track of the distance row
  int tempAssign = 0; //Position of the medoid the assignment has been assigned to [it's position in the distance matrix]
  int centerPos = 0; //Position of the center, used to test if the center has the capacity for the mission [only used when assigning missions to medoids]
  bool assigned = false;
  //For the first i positions [i < nbCenters] we make sure that the medoid the assignment is compared to is not a center [We can't assign a center to a center]
  for (int i = 0; i < data1->nbCenters; i++) { //Iterate over the centers
    distance = std::numeric_limits<float>::max(); //We reset the distance
    tempAssign = 0; //We reset the assignment
    for (int j = 0; j < data1->nbCenters; j++) { //Iterate over the medoids
      //We verify that we haven't already assigned a center to this medoid
      if (this->assignments[j].empty() ) {
        //We check that the position of our row is not on a medoid, if it is we go to the next
        while (std::count(this->medoids.begin(), this->medoids.end(), row)) {
          row ++;
        }
        //We check that the medoid isn't a center to avoid assigning a center to a center
        if (this->medoids[j] > data1->nbCenters) {
           //We make sure the center has the capacity for this mission
          if (data1->centers[row]->getCapacity(data1->missions[this->medoids[j] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[j] - data1->nbCenters]->getDay()-1,data1->missions[this->medoids[j] - data1->nbCenters]->getStartingPeriod()) > 0) {
              if (data1->distancesMatrix->getDistance(row, this->medoids[j]) < distance) { //We compare the distance between the assignment and the medoid with the smallest distant previously found
              distance = data1->distancesMatrix->getDistance(row, medoids[j]); //New smallest distance
              tempAssign = j; //Keep track of the new best medoid
              assigned = true;
            }
          }
        }
      }
    }
    //We check to see if the center has been assigned [it will only be assigned if it isn't already a medoid itself]
    if (assigned){
        //We assign the assignment to the medoid
        this->assignments[tempAssign].insert(this->assignments[tempAssign].end(),row);
        //We update the capacity of the center
        data1->centers[row]->updateCapacity(data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getSkill(), data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getDay()-1,data1->missions[this->medoids[tempAssign] - data1->nbCenters]->getStartingPeriod());
        row++;
    }
    assigned = false; //reset assigned bool
  }

  //Now we move on to assigning the missions to the medoids
  while (row < data1->nbMissions) { //We iterate over the assignments, we know these ones are missions
    //std::cout << std::endl << "==========================" << std::endl;
    //std::cout << "Assignment of mission n " << row-data1->nbCenters+1 << std::endl;
    distance = std::numeric_limits<float>::max(); //We reset the distance
    int tempAssign = 0;
    int tempCenterpos = 0;
    centerPos = 0;

    for (int j = 0; j < data1->nbCenters; j++) { //We iterate over the medoids
      //We check that the position of our row is not on a medoid, if it is we go to the next
      while (std::count(this->medoids.begin(), this->medoids.end(), row)) {
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
      if (data1->centers[centerPos]->getCapacity(data1->missions[row - data1->nbCenters]->getSkill(), data1->missions[row - data1->nbCenters]->getDay()-1,data1->missions[row - data1->nbCenters]->getStartingPeriod()) > 0) {
          //std::cout << "Distance between the medoid and the mission : " << data1->distancesMatrix->getDistance(row, this->medoids[j]) << std::endl;
          if (data1->distancesMatrix->getDistance(row, this->medoids[j]) < distance) { //We compare the distance between the mission and the medoid with the smallest distant previously found
          distance = data1->distancesMatrix->getDistance(row, medoids[j]);
          tempAssign = j; //Keep track of new best medoid assignment
          tempCenterpos = centerPos;
          assigned = true;
        }
      }
    }
    if (assigned){
        //std::cout << "The mission was assigned to " << tempAssign << " with a distance of " << distance << std::endl;
        //We assign the assignment to the medoid
        this->assignments[tempAssign].insert(this->assignments[tempAssign].end(),row);
        //Change the capacity of the center
        data1->centers[tempCenterpos]->updateCapacity(data1->missions[row - data1->nbCenters]->getSkill(), data1->missions[row - data1->nbCenters]->getDay()-1,data1->missions[row - data1->nbCenters]->getStartingPeriod());
        //std::cout << "New capacity : " << data1->centers[tempCenterpos]->getCapacity(data1->missions[row - data1->nbCenters]->getSkill(), data1->missions[row - data1->nbCenters]->getStartingPeriod()); 
    }
    assigned = false;
    row++; //We increment the row
  }
}

bool kMedoids::medoidsUpdate(data* data1){
  /**For each or our medoid we calculate all possible costs
   * Meaning for each assignment we calculate the cost we would have if it was the medoid
   * We then compare the cost of the current medoid with the cost of the new medoid, and choose the smallest one as our new medoid
   */
  float cost = std::numeric_limits<float>::max();
  float oldCost = 0;
  int tempMedoid = 0; //Position of the medoid we're testing, pos in distance matrix
  int bestMedoid = 0; //Position of the best medoid, pos in distance matrix
  std::vector<int> bestAssignments; //Assignments of the best medoid
  std::vector<int> tempAssignments; //Assignments of the medoid we're testing
  bool assigned = false;
  bool medoidUpdated = false;

  for (int i = 0; i < data1->nbCenters; i++) {//Iterate over the medoids
    oldCost = calculateCost(this->medoids[i], this->assignments[i], data1); //We set the cost of the current medoid
    tempAssignments.clear();
    bestAssignments.clear();

    for (int j = 0; j < this->assignments[i].size(); j++) {//Iterates over the assignments of the medoid
      tempMedoid = this->assignments[i][j]; //We get the medoid we're testing [the assignment]
      tempAssignments = this->assignments[i]; //We copy the assignments of the old medoid
      tempAssignments[j] = this->medoids[i]; //We change the assignment that contained the position of the medoid being tested, to the position of the old medoid
      cost = calculateCost(tempMedoid, tempAssignments, data1); //We calculate the cost of the medoid we're testing
      if (cost < oldCost) {//If this medoid is better than the old one
        bestMedoid = tempMedoid; //We set the best medoid to the one we're testing
        bestAssignments = tempAssignments; //We set the best assignments to the ones of the medoid we're testing
        oldCost = cost; //We set the old cost to the cost of the medoid we're testing
        assigned = true;
      }
    }
    //We change the medoids and assignments with our new (or old) best values
    if (assigned){
      this->medoids[i] = bestMedoid;
      this->assignments[i] = bestAssignments;
      medoidUpdated = true;
    }
    assigned = false;
  }
  return medoidUpdated;
}
    
float kMedoids::calculateCost(int medoid, std::vector<int> assignments, data* data1){
  float cost = 0;
  //We iterate over the assignments and add the distance between the medoid and the assignment
  for (int i = 0; i < assignments.size(); i++){
    cost += data1->distancesMatrix->getDistance(medoid, assignments[i]) * 0.2;
  }
  return cost;
}

void kMedoids::printMedoids(data* data1){
  bool center;
  std::cout << std::endl << "=========== ASSIGNMENTS ===========" << std::endl;
  for (int i = 0; i < this->medoids.size(); i++) { //We iterate over the medoids
    std::cout << "Assignments for Center n\370";
    if (this->medoids[i] > data1->nbCenters) {
        std::cout << this->assignments[i][0]+1;
        std::cout << " using mission n\370" << this->medoids[i]-data1->nbCenters+1 << std::endl;
        center = false;
    } else{
        std::cout << this->medoids[i]+1 << std::endl;
        center = true;
    }
    for (int j = 0; j < this->assignments[i].size() ; j++) {//We iterate over the assignments
      if (!center) { //If the medoid isn't a center, we know the first assignment is the center and not a mission
          j++;
          center = true;
      }
      std::cout << "mission n\370" << this->assignments[i][j]-data1->nbCenters+1 << " // ";
    }
    std::cout << std::endl << std::endl;
  }
  std::cout << std::endl;
}