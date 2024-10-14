#pragma once

#include <Task.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

class DeadlineMonotonic {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit DeadlineMonotonic(const std::vector<Task>& tasks_input);
    void calculateLcmFromPeriods();
    void sortTasksByDeadline();
    std::optional<bool> isSchedulable();
    std::vector<int> runDeadlineMonotonic();
};
