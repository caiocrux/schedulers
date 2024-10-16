#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "matplotlibcpp.h"  // Assuming matplotlibcpp is in your include path

class GanttChart {
   public:
    // Destructor to kill the matplotlib interpreter
    ~GanttChart();

    void saveToCSV(const std::vector<int>& schedule,
                   const std::string& filename);
    void drawGanttChart(const std::vector<int>& schedule, std::string title);
};
