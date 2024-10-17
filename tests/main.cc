#define CATCH_CONFIG_MAIN
#include <Task.h>
#include <deadlineMonotonic.h>
#include <earliestDeadlineFirst.h>
#include <leastLaxity.h>
#include <rateMonotonic.h>

#include <catch2/catch_test_macros.hpp>
TEST_CASE("Task properties test", "[Task]") {
    // Arrange: create the vector of tasks
    std::vector<Task> tasks = {Task(1, 3, 7, 7), Task(2, 2, 12, 12),
                               Task(3, 2, 20, 20)};

    SECTION("Task IDs are correctly set") {
        REQUIRE(tasks[0].getId() == 1);
        REQUIRE(tasks[1].getId() == 2);
        REQUIRE(tasks[2].getId() == 3);
    }

    SECTION("Execution times are correctly set") {
        REQUIRE(tasks[0].getC() == 3);
        REQUIRE(tasks[1].getC() == 2);
        REQUIRE(tasks[2].getC() == 2);
    }

    SECTION("Periods are correctly set") {
        REQUIRE(tasks[0].getT() == 7);
        REQUIRE(tasks[1].getT() == 12);
        REQUIRE(tasks[2].getT() == 20);
    }

    SECTION("Deadlines are correctly set") {
        REQUIRE(tasks[0].getD() == 7);
        REQUIRE(tasks[1].getD() == 12);
        REQUIRE(tasks[2].getD() == 20);
    }
}

TEST_CASE("Rate Monotonic Class Tests", "[RateMonotonic]") {
    // Sample tasks: id, computation time (C), period (T), deadline (D)
    std::vector<Task> tasks = {Task(1, 3, 7, 7), Task(2, 2, 12, 12),
                               Task(3, 2, 20, 20)};

    RateMonotonic rm(tasks);

    SECTION("Schedulability test") {
        auto schedulable = rm.isSchedulable();
        REQUIRE(schedulable.has_value());
        REQUIRE(schedulable.value() ==
                true);  // Expected all tasks to be schedulable
    }

    SECTION("Task schedule generation") {
        rm.calculateLcmFromPeriods();
        auto schedule = rm.run();
        // Verify schedule for specific times, if known, e.g., check task
        // execution frequency
        REQUIRE(schedule[0] == 1);
        REQUIRE(schedule[3] == 2);
        REQUIRE(schedule[6] == 3);
        REQUIRE(schedule[11] == -1);
    }
}
