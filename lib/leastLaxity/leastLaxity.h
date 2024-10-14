#pragma once

#include <Task.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

class LeastLaxity {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit LeastLaxity(const std::vector<Task>& tasks_input);
    void calculateLcmFromPeriods();
    std::optional<bool> isSchedulable() const;
    void sortTasksByLaxity(int currentTime);
    std::vector<int> runLeastLaxity();
};
