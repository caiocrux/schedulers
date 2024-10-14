set(LIB_GANTT_NAME "LibGannt")
set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/GanttChart.cc")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/GanttChart.h")
set(LIBRARY_INCLUDES "./")

find_package(Python3 COMPONENTS Development NumPy REQUIRED)
add_library(${LIB_GANTT_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIB_GANTT_NAME}  PUBLIC ${LIBRARY_INCLUDES} ${matplotlib-cpp_SOURCE_DIR})
target_link_libraries(${LIB_GANTT_NAME} Python3::Python Python3::NumPy)
