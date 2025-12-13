message("AoC2025 day1 Solution")
set(DAY1_EXE "${PROJECT_NAME}_day1")
add_executable(${DAY1_EXE} day1.cpp ${UTILS_FILES})
target_include_directories(${DAY1_EXE} PUBLIC ${UTILS_FILES})

option(EXAMPLES1 "Build Example version" OFF)
if(EXAMPLES1)
    message("BUILD day1 with examples")
    target_compile_definitions(${DAY1_EXE} PRIVATE DAY1_EXAMPLE)
    add_custom_command(TARGET ${DAY1_EXE} POST_BUILD 
    COMMAND "${CMAKE_COMMAND}" -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/day1_example.txt"
    "$<TARGET_FILE_DIR:${DAY1_EXE}>"
    COMMENT "Copying data")
endif()


add_custom_command(TARGET ${DAY1_EXE} POST_BUILD 
    COMMAND "${CMAKE_COMMAND}" -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/day1_input.txt"
    "$<TARGET_FILE_DIR:${DAY1_EXE}>"
    COMMENT "Copying data")