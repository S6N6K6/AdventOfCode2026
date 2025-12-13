message("AoC2025 day3 Solution")

set(DAY3_EXE "${PROJECT_NAME}_day3")

add_executable(${DAY3_EXE} day3.cpp ${UTILS_FILES})
target_include_directories(${DAY3_EXE} PUBLIC ${UTILS_FILES})
option(EXAMPLES3 "Build Example version" OFF)
if(EXAMPLES3)
    message("BUILD Day3 with examples")
    target_compile_definitions(${DAY3_EXE} PRIVATE DAY3_EXAMPLE)
    add_custom_command(TARGET ${DAY3_EXE} POST_BUILD 
    COMMAND "${CMAKE_COMMAND}" -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/day3_example.txt"
    "$<TARGET_FILE_DIR:${DAY3_EXE}>"
    COMMENT "Copying data")
endif()

add_custom_command(TARGET ${DAY3_EXE} POST_BUILD 
    COMMAND "${CMAKE_COMMAND}" -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/day3_input.txt"
    "$<TARGET_FILE_DIR:${DAY3_EXE}>"
    COMMENT "Copying data")