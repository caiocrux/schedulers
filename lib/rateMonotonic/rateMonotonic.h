#pragma once

#include <Task.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

class RateMonotonic {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit RateMonotonic(const std::vector<Task>& tasks_input);
    void calculateLcmFromPeriods();
    std::optional<bool> isSchedulable() const;
    void sortTasksByPeriod();
    std::vector<int> runRateMonotonic();
};
