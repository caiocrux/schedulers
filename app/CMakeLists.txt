set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/schedulers.cc")
add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})
target_link_libraries(${EXECUTABLE_NAME} "LibTask" "LibGannt" "LibRM" "LibDL" "LibEDF" "LibLL")

