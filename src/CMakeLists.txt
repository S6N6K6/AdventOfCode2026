message("Main src CMakeLists.txt")

file(GLOB UTILS_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.hpp
)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/utils)

# DAY 1 Solution Executable
add_subdirectory(day1)

# DAY 2 Solution Executable
add_subdirectory(day2)