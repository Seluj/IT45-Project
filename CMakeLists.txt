cmake_minimum_required(VERSION 3.25)
project(IT45_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(IT45_Project main.cpp accessCSV/distanceCSV.cpp accessCSV/distanceCSV.hpp accessCSV/centersCSV.cpp accessCSV/centersCSV.hpp accessCSV/missionsCSV.cpp accessCSV/missionsCSV.hpp accessCSV/employeesCSV.cpp accessCSV/employeesCSV.hpp dataCollection.cpp dataCollection.hpp classes/employee.cpp classes/employee.hpp classes/mission.cpp classes/mission.hpp classes/center.cpp classes/center.hpp dataAnalysis.cpp dataAnalysis.hpp data.cpp data.hpp classes/distances.cpp classes/distances.h)
