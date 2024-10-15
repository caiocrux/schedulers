#pragma once

#include <Task.h>
#include <scheduler.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

class RateMonotonic : public Scheduler {
   public:
    explicit RateMonotonic(const std::vector<Task>& tasks_input);
    void calculateLcmFromPeriods() override;
    std::optional<bool> isSchedulable() override;
    void sortTasksByPeriod();
    std::vector<int> run() override;
};
