message("AoC2025 day2 Solution")

set(DAY2_EXE "${PROJECT_NAME}_day2")

add_executable(${DAY2_EXE} day2.cpp ${UTILS_FILES})
target_include_directories(${DAY2_EXE} PUBLIC ${UTILS_FILES})
option(EXAMPLES2 "Build Example version" OFF)
if(EXAMPLES2)
    message("BUILD Day2 with examples")
    target_compile_definitions(${DAY2_EXE} PRIVATE DAY2_EXAMPLE)
    add_custom_command(TARGET ${DAY2_EXE} POST_BUILD 
    COMMAND "${CMAKE_COMMAND}" -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/day2_example.txt"
    "$<TARGET_FILE_DIR:${DAY2_EXE}>"
    COMMENT "Copying data")
endif()

add_custom_command(TARGET ${DAY2_EXE} POST_BUILD 
    COMMAND "${CMAKE_COMMAND}" -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/day2_input.txt"
    "$<TARGET_FILE_DIR:${DAY2_EXE}>"
    COMMENT "Copying data")