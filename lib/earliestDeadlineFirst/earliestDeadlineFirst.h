#pragma once

#include <Task.h>
#include <scheduler.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

class EarliestDeadlineFirst : public Scheduler {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit EarliestDeadlineFirst(const std::vector<Task>& tasks_input);
    void calculateLcmFromPeriods() override;
    void sortTasksByDeadline(int currentTime);
    std::optional<bool> isSchedulable() override;
    std::vector<int> run() override;
};
