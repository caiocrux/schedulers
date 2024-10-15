#include <deadlineMonotonic.h>
#include <earliestDeadlineFirst.h>
#include <leastLaxity.h>
#include <rateMonotonic.h>
#include <scheduler.h>

std::unique_ptr<Scheduler> createScheduler(const std::string& type,
                                           const std::vector<Task>& tasks) {
    if (type == "RateMonotonic") {
        return std::make_unique<RateMonotonic>(tasks);
    } else if (type == "DeadlineMonotonic") {
        return std::make_unique<DeadlineMonotonic>(tasks);
    } else if (type == "EarliestDeadlineFirst") {
        return std::make_unique<EarliestDeadlineFirst>(tasks);
    } else if (type == "LeastLaxity") {
        return std::make_unique<LeastLaxity>(tasks);
    } else {
        std::cerr << "Unknown scheduling algorithm type: " << type << std::endl;
        return nullptr;
    }
}
