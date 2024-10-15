#include "rateMonotonic.h"

RateMonotonic::RateMonotonic(const std::vector<Task>& tasks_input)
    : Scheduler(tasks_input) {
    sortTasksByPeriod();
}

void RateMonotonic::calculateLcmFromPeriods() {
    m_lcm = 1;
    for (const auto& task : m_tasks) {
        m_lcm = std::lcm(m_lcm, task.getT());
    }
    std::cout << "LCM: " << m_lcm << std::endl;
}

std::optional<bool> RateMonotonic::isSchedulable() {
    double U = 0;
    int n = m_tasks.size();

    for (const auto& task : m_tasks) {
        U += static_cast<double>(task.getC()) / task.getT();
    }

    double bound = n * (std::pow(2.0, 1.0 / n) - 1);
    std::cout << "Utotal: " << U << std::endl;
    std::cout << "Umax: " << bound << std::endl;

    return (U <= bound) ? std::optional<bool>(true)
                        : std::optional<bool>(false);
}

void RateMonotonic::sortTasksByPeriod() {
    std::sort(m_tasks.begin(), m_tasks.end(),
              [](const Task& a, const Task& b) { return a.getT() < b.getT(); });
}

std::vector<int> RateMonotonic::run() {
    std::vector<int> schedule(m_lcm, -1);
    int time = 0;

    for (auto& task : m_tasks) {
        task.setRemaining(task.getC());
    }

    while (time < m_lcm) {
        Task* next_task = nullptr;

        for (auto& task : m_tasks) {
            if (time % task.getT() == 0) {
                task.setRemaining(task.getC());
            }

            if (task.getRemaining() > 0 &&
                (next_task == nullptr || task.getT() < next_task->getT())) {
                next_task = &task;
            }
        }

        if (next_task) {
            schedule[time] = next_task->getId();
            next_task->setRemaining(next_task->getRemaining() - 1);
        }

        time++;
    }

    return schedule;
}
