//
// Created by jules on 01/06/2023.
//

#ifndef IT45_PROJECT_DATAANALYSIS_HPP
#define IT45_PROJECT_DATAANALYSIS_HPP

#include "dataCollection.hpp"
#include "data.hpp"
#include "classes/center.hpp"

class dataAnalysis {
public:
  dataAnalysis(dataCollection* d, data* data1);

  void dataAnalysisPrint(data *data1);
};


#endif //IT45_PROJECT_DATAANALYSIS_HPP
