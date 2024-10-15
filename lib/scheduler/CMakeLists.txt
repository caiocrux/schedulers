set(LIB_SH_NAME "LibSH")
set(LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/scheduler.cc")
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/scheduler.h")
set(LIBRARY_INCLUDES "./")

add_library(${LIB_SH_NAME} STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIB_SH_NAME}  PUBLIC ${LIBRARY_INCLUDES} )
target_link_libraries(${LIB_SH_NAME} PRIVATE LibTask "LibGannt" "LibRM" "LibDL" "LibEDF" "LibLL")
