#include "earliestDeadlineFirst.h"

EarliestDeadlineFirst::EarliestDeadlineFirst(
    const std::vector<Task>& tasks_input)
    : m_tasks(tasks_input), m_lcm(1) {}

void EarliestDeadlineFirst::calculateLcmFromPeriods() {
    m_lcm = 1;
    for (const auto& task : m_tasks) {
        m_lcm = std::lcm(m_lcm, task.getT());
    }
    std::cout << "LCM: " << m_lcm << std::endl;
}

void EarliestDeadlineFirst::sortTasksByDeadline(int currentTime) {
    std::sort(m_tasks.begin(), m_tasks.end(),
              [currentTime](const Task& a, const Task& b) {
                  int deadlineA = a.getT() - (currentTime % a.getT());
                  int deadlineB = b.getT() - (currentTime % b.getT());
                  return deadlineA < deadlineB;
              });
}

std::optional<bool> EarliestDeadlineFirst::isSchedulable() {
    double U = 0;
    double maxCore = 1.0;

    for (const auto& task : m_tasks) {
        U += static_cast<double>(task.getC()) / task.getT();
    }

    std::cout << "Utotal: " << U << std::endl;
    return (U <= maxCore) ? std::optional<bool>(true)
                          : std::optional<bool>(false);
}

std::vector<int> EarliestDeadlineFirst::runEarliestDeadlineFirst() {
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
        }

        sortTasksByDeadline(time);

        for (auto& task : m_tasks) {
            if (task.getRemaining() > 0) {
                next_task = &task;
                break;
            }
        }

        if (next_task) {
            schedule[time] = next_task->getId();
            next_task->setRemaining(next_task->getRemaining() - 1);
        } else {
            schedule[time] = -1;  // Idle
        }

        time++;
    }

    return schedule;
}
