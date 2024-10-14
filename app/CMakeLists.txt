set(APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/schedulers.cc")

add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})
target_include_directories( ${EXECUTABLE_NAME} PRIVATE ${matplotlib-cpp_SOURCE_DIR})
find_package(Python3 COMPONENTS Development NumPy REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} Python3::Python Python3::NumPy "LibTask")

