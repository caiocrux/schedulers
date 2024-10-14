#include "leastLaxity.h"

LeastLaxity::LeastLaxity(const std::vector<Task>& tasks_input)
    : m_tasks(tasks_input), m_lcm(1) {}

void LeastLaxity::calculateLcmFromPeriods() {
    m_lcm = 1;
    for (const auto& task : m_tasks) {
        m_lcm = std::lcm(m_lcm, task.getT());
    }
    std::cout << "LCM: " << m_lcm << std::endl;
}

std::optional<bool> LeastLaxity::isSchedulable() const {
    return std::optional<bool>(true);  // Placeholder for schedulability check
}

void LeastLaxity::sortTasksByLaxity(int currentTime) {
    std::sort(m_tasks.begin(), m_tasks.end(),
              [currentTime](const Task& a, const Task& b) {
                  int laxityA =
                      (a.getT() - (currentTime % a.getT())) - a.getRemaining();
                  int laxityB =
                      (b.getT() - (currentTime % b.getT())) - b.getRemaining();
                  return laxityA < laxityB;
              });
}

std::vector<int> LeastLaxity::runLeastLaxity() {
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

        sortTasksByLaxity(time);

        for (auto& task : m_tasks) {
            if (task.getRemaining() > 0) {
                next_task = &task;
                break;
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
