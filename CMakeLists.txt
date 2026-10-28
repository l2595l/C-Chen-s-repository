cmake_minimum_required(VERSION 4.3)
project(Data)

set(CMAKE_CXX_STANDARD 20)

# ========================================
# CLion 模板代码
# ========================================
add_executable(Data_CLion CLion_Data/main.cpp CLion_Data/1.cpp)

# ========================================
# 第三阶段-录制代码：每个 .cpp 独立为一个可执行目标
# ========================================
file(GLOB_RECURSE RECORD_CPP_FILES "第三阶段-录制代码/*.cpp")

set(COUNTER 0)

foreach(CPP_FILE ${RECORD_CPP_FILES})
    get_filename_component(FILENAME_WE ${CPP_FILE} NAME_WE)

    # 跳过没有 main 函数的辅助文件
    if(FILENAME_WE STREQUAL "person")
        continue()
    endif()

    math(EXPR COUNTER "${COUNTER} + 1")

    # 从祖父目录名中提取 ASCII 作为目标名前缀
    get_filename_component(DIRECTORY ${CPP_FILE} DIRECTORY)
    get_filename_component(GP "${DIRECTORY}" DIRECTORY)
    get_filename_component(GRANDPARENT_DIR ${GP} NAME)

    string(REGEX REPLACE "[^a-zA-Z0-9_]" "" SAFE_PREFIX "${GRANDPARENT_DIR}")

    if(SAFE_PREFIX)
        set(TARGET_NAME "${SAFE_PREFIX}_${COUNTER}")
    else()
        set(TARGET_NAME "cpp_demo_${COUNTER}")
    endif()

    add_executable("${TARGET_NAME}" "${CPP_FILE}")
endforeach()
