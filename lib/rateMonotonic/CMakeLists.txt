set(LIB_RM_NAME "LibRM")
set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/rateMonotonic.cc")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/rateMonotonic.h")
set(LIBRARY_INCLUDES "./")

add_library(${LIB_RM_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIB_RM_NAME}  PUBLIC ${LIBRARY_INCLUDES} )
target_link_libraries(${LIB_RM_NAME} PRIVATE LibTask)
