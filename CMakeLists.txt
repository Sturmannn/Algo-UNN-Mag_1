cmake_minimum_required(VERSION 3.12)
project(Algo_shad)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# list(APPEND CMAKE_CXX_FLAGS "-Wall -Werror -Wsign-compare")

# set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all -O2"
#     CACHE STRING "Compiler flags in asan build"
#     FORCE)

# set(CMAKE_CXX_FLAGS_SHADREL "-O2 -DNDEBUG"
#     CACHE STRING "Compiler flags for the release version that executes on Yandex.Contest"
#     FORCE)

message("General compiler flags: " ${CMAKE_CXX_FLAGS})
message("Debug build compiler flags: " ${CMAKE_CXX_FLAGS_DEBUG})
message("ASAN build compiler flags: " ${CMAKE_CXX_FLAGS_ASAN})
message("ShadRel build compiler flags: " ${CMAKE_CXX_FLAGS_SHADREL})

# # Contest 1
# add_executable(problem_0A ${CMAKE_CURRENT_SOURCE_DIR}/contest_1/problem_A.cpp)
# add_executable(problem_0B ${CMAKE_CURRENT_SOURCE_DIR}/contest_1/problem_B.cpp)
# add_executable(problem_0C ${CMAKE_CURRENT_SOURCE_DIR}/contest_1/problem_C.cpp)
# add_executable(problem_0D ${CMAKE_CURRENT_SOURCE_DIR}/contest_1/problem_D.cpp)

file(GLOB CONTEST_DIRS LIST_DIRECTORIES true "contest_*")
foreach(contest_dir ${CONTEST_DIRS})
    get_filename_component(contest_dir_name ${contest_dir} NAME)
    file (GLOB TASKS "${contest_dir_name}/*.cpp")

    foreach(task ${TASKS})
        get_filename_component(task_name ${task} NAME_WE)
        add_executable(${task_name} ${task})    
    endforeach()
endforeach()
