#include "GanttChart.h"

void GanttChart::saveToCSV(const std::vector<int>& schedule,
                           const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file << "Time,TaskID\n";  // CSV header
    for (size_t t = 0; t < schedule.size(); ++t) {
        file << t << "," << schedule[t] << "\n";
    }
    file.close();
}

void GanttChart::drawGanttChart(const std::vector<int>& schedule,
                                std::string title) {
    std::map<int, std::vector<int>>
        task_times;               // Stores intervals for each task
    std::vector<int> idle_times;  // Stores idle intervals

    for (size_t t = 0; t < schedule.size(); ++t) {
        int task_id = schedule[t];
        if (task_id != -1) {
            task_times[task_id].push_back(t);
        } else {
            idle_times.push_back(t);
        }
    }

    // Draw each task on the Gantt chart
    for (const auto& [task_id, times] : task_times) {
        std::vector<double> x, y;
        for (const auto& time : times) {
            x.push_back(time);
            y.push_back(task_id);
        }

        plt::scatter(x, y, 50, {{"label", "Task " + std::to_string(task_id)}});
    }

    // Draw idle times (IDLE)
    if (!idle_times.empty()) {
        std::vector<double> idle_x(idle_times.begin(), idle_times.end());
        std::vector<double> idle_y(idle_times.size(),
                                   0);  // IDLE represented at Y=0

        plt::scatter(idle_x, idle_y, 50,
                     {{"label", "IDLE"}, {"color", "gray"}});
    }

    // Set title and labels
    plt::title(title);
    plt::xlabel("Time");
    plt::ylabel("Task ID");

    // Add legend
    plt::legend();
    // Show the chart
    plt::show();
    // Clear the figure after saving (optional)
    plt::clf();
}
