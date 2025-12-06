message("Build for day1 executable solving the day1 problem")
add_executable("AoC25_day1" day1.cpp)

option(EXAMPLES "Build Example version" OFF)
if(EXAMPLES)
    message("BUILD WITH EXAMPLES")
    target_compile_definitions("AoC25_day1" PRIVATE DAY1_EXAMPLE) 
endif()


add_custom_command(TARGET "AoC25_day1" POST_BUILD 
    COMMAND "${CMAKE_COMMAND}" -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/day1_input.txt"
    "$<TARGET_FILE_DIR:AoC25_day1>"
    COMMENT "Copying data")