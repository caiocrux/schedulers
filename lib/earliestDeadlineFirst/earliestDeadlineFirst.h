#pragma once

#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include "Task.h"  // Assuming Task.h is in the same directory

class EarliestDeadlineFirst {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit EarliestDeadlineFirst(const std::vector<Task>& tasks_input);
    void calculateLcmFromPeriods();
    void sortTasksByDeadline(int currentTime);
    std::optional<bool> isSchedulable();
    std::vector<int> runEarliestDeadlineFirst();
};

