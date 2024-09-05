cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(codeforces)

set(PROJECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

find_package(fmt REQUIRED)
find_package(Catch2 REQUIRED)
find_package(spdlog REQUIRED)

include_directories(${PROJECT_INCLUDE_DIRS})

#=======================================================================
set(EXCLUDED_DIRECTORIES)
#=======================================================================

# 定义用于递归处理子目录的函数
function(add_subprojects ROOT_DIR)
    file(GLOB SUB_PROJECTS "${ROOT_DIR}/*")
    foreach (SUB_PROJECT ${SUB_PROJECTS})
        if (IS_DIRECTORY ${SUB_PROJECT})
            # 获取文件夹名称
            get_filename_component(LAST_PART ${SUB_PROJECT} NAME)
            if (NOT LAST_PART IN_LIST EXCLUDED_DIRECTORIES)
                # 设置子项目名称
                set(PROJECT_NAME ${LAST_PART})
                project(${PROJECT_NAME})

                # 获取所有cpp源文件 (现在cpp文件直接在子项目根目录)
                file(GLOB_RECURSE SOURCE_FILES ${SUB_PROJECT}/*.cpp)

                # 设置输出目录
                if (${ROOT_DIR} MATCHES "problem_set")
                    set(OUTPUT_DIR ${EXECUTABLE_OUTPUT_PATH}/problem_set)
                else ()
                    # 获取contest的上一级目录名
                    get_filename_component(PARENT_DIR ${SUB_PROJECT} DIRECTORY)
                    get_filename_component(CONTEST_NAME ${PARENT_DIR} NAME)
                    set(OUTPUT_DIR ${EXECUTABLE_OUTPUT_PATH}/contest/${CONTEST_NAME})
                endif ()

                # 为子项目添加可执行文件
                add_executable(${PROJECT_NAME} ${SOURCE_FILES})
                set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

                # 添加依赖库
                target_link_libraries(${PROJECT_NAME} fmt::fmt)
                target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain)
                target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
            endif ()
        endif ()
    endforeach ()
endfunction()

# 处理 problem_set 目录
add_subprojects(${PROJECT_SOURCE_DIR}/problem_set)

# 处理 contest 目录 (逐个比赛的文件夹)
file(GLOB CONTESTS "${PROJECT_SOURCE_DIR}/contest/*")
foreach (CONTEST ${CONTESTS})
    if (IS_DIRECTORY ${CONTEST})
        add_subprojects(${CONTEST})
    endif ()
endforeach ()
