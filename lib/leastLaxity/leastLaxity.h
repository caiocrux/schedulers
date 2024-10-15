#pragma once

#include <Task.h>
#include <scheduler.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

class LeastLaxity : public Scheduler {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit LeastLaxity(const std::vector<Task>& tasks_input);
    void calculateLcmFromPeriods() override;
    std::optional<bool> isSchedulable() override;
    void sortTasksByLaxity(int currentTime);
    std::vector<int> run() override;
};
