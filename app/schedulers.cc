/*
 * untitled.cxx
 *
 * Copyright 2024 caio felipe soares da cruz  <caio-cruz@ENCSABCAMLT0872>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <GanttChart.h>
#include <Task.h>
#include <deadlineMonotonic.h>
#include <rateMonotonic.h>
#include <rateMonotonic.h>
#include <earliestDeadlineFirst.h>
#include <algorithm>
#include <cmath>
#include <fstream>  // for file output
#include <iostream>
#include <map>
#include <numeric>   // std::lcm
#include <optional>  // std::optional
#include <vector>

class LeastLaxity {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit LeastLaxity(const std::vector<Task> &tasks_input)
        : m_tasks(tasks_input), m_lcm(1) {}

    void calculateLcmFromPeriods() {
        m_lcm = 1;
        for (const auto &task : m_tasks) {
            m_lcm = std::lcm(m_lcm, task.getT());
        }
        std::cout << "LCM: " << m_lcm << std::endl;
    }

    std::optional<bool> isSchedulable() const {
        return std::optional<bool>(true);
    }

    void sortTasksByLaxity(int currentTime) {
        std::sort(m_tasks.begin(), m_tasks.end(),
                  [currentTime](const Task &a, const Task &b) {
                      int laxityA = (a.getT() - (currentTime % a.getT())) -
                                    a.getRemaining();
                      int laxityB = (b.getT() - (currentTime % b.getT())) -
                                    b.getRemaining();
                      return laxityA < laxityB;
                  });
    }

    std::vector<int> runLeastLaxity() {
        std::vector<int> schedule(m_lcm, -1);
        int time = 0;

        for (auto &task : m_tasks) {
            task.setRemaining(task.getC());
        }

        while (time < m_lcm) {
            Task *next_task = nullptr;

            for (auto &task : m_tasks) {
                if (time % task.getT() == 0) {
                    task.setRemaining(task.getC());
                }
            }

            sortTasksByLaxity(time);

            for (auto &task : m_tasks) {
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
};
// int main(int argc, char **argv) {
int main(void) {
    //  int n;
    //  std::cout << "Digite o número de tarefas: ";
    //  std::cin >> n;

    // Tabela 1
#if 0
  std::vector<Task> tasks = {Task(1, 3, 7, 7), Task(2, 2, 12, 12),
                             Task(3, 2, 20, 20)};
  std::string task1_img = "Tabela_1.csv";
#endif

#if 0
  std::vector<Task> tasks = {Task(1, 6.25, 25, 7), Task(2, 6.25, 50, 12),
                             Task(3, 40, 100, 20)};
#endif

    // Tabela 2
#if 0
  std::vector<Task> tasks = {Task(1, 1, 4, 4), Task(2, 2, 6, 6),
                             Task(3, 3, 10, 7)};
  std::string task1_img = "Tabela_2.csv";

#endif

    // Tabela 6
#if 0
  std::vector<Task> tasks = {Task(1, 3, 10, 10), Task(2, 3, 10, 10),
                             Task(3, 3, 10, 10), Task(4, 2, 100, 100)};
  std::string task1_img = "Tabela_6.csv";
#endif

// exemplo para graficos diferentes
#if 0 
  std::vector<Task> tasks = {Task(1, 1, 4, 4), 
                             Task(2, 2, 5, 3),
                             Task(3, 2, 7, 6),
                             Task(4, 3, 12, 10)};
#endif

#if 0

std::vector<Task> tasks = {Task(1, 2, 10, 5), 
                           Task(2, 5, 20, 7),
                           Task(3, 10, 50, 10)};
#endif
    /*
      for (int i = 0; i < n; i++) {
        int C, T, D;
        std::cout << "Digite o tempo de execução (C), o período (T) e "
                  << "o deadline (D) para a tarefa " << (i + 1) << ": ";
        std::cin >> C >> T >> D;
        // Using emplace_back() to create instances of Task directly in
        // the vector avoids an additional copy and improves performance
        tasks.emplace_back(i + 1, C, T, D);
      }
    */
    // for (auto i : tasks) {
    //   i.print_task();
    // }

#if 0
  std::vector<Task> tasks = {Task(1, 1, 7, 7),
                             Task(2, 2, 9, 9),
                             Task(3, 3, 11, 11),
                             Task(4, 4, 13, 13)};
  std::string task1_img = "Tabela_1.csv";
#endif
#if 1
    std::vector<Task> tasks = {Task(1, 2, 7, 7), Task(2, 3, 12, 12),
                               Task(3, 2, 5, 5)};
    //                               Task(3, 1, 20, 20)};
    // Task(4, 4, 13, 13)};
    std::string task1_img = "Tabela_1.csv";

#endif

    RateMonotonic rmScheduler(tasks);
    rmScheduler.calculateLcmFromPeriods();
    rmScheduler.sortTasksByPeriod();

    DeadlineMonotonic dmScheduler(tasks);
    dmScheduler.calculateLcmFromPeriods();
    dmScheduler.sortTasksByDeadline();

    EarliestDeadlineFirst edfScheduler(tasks);
    edfScheduler.calculateLcmFromPeriods();

    LeastLaxity llScheduler(tasks);
    llScheduler.calculateLcmFromPeriods();

    if (!rmScheduler.isSchedulable()) {
        std::cout << "Tasks can not be schedulable using Rate "
                     "Monotonic scheduler! "
                  << std::endl;
    }
    if (!dmScheduler.isSchedulable()) {
        std::cout << "Tasks can not be schedulable using DeadLine "
                     "Monotonic scheduler! "
                  << std::endl;
    }
    if (!edfScheduler.isSchedulable()) {
        std::cout << "Tasks can not be schedulable using Earliest "
                     "Deadline First scheduler! "
                  << std::endl;
    }

    auto rmSchedule = rmScheduler.runRateMonotonic();
    auto dmSchedule = dmScheduler.runDeadlineMonotonic();
    auto edfSchedule = edfScheduler.runEarliestDeadlineFirst();
    auto llSchedule = llScheduler.runLeastLaxity();

    GanttChart ganttChart;

    ganttChart.drawGanttChart(rmSchedule, "Rate Monotonic Chart");
    ganttChart.drawGanttChart(dmSchedule, "Deadline Monotonic Chart");
    ganttChart.drawGanttChart(edfSchedule, "Earliest Deadline First Chart");
    ganttChart.drawGanttChart(llSchedule, "Least Laxity Chart");
    return 0;
}
