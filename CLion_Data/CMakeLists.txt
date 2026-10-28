cmake_minimum_required(VERSION 4.3)
project(Data)

set(CMAKE_CXX_STANDARD 20)

# ========================================
# 主目标：CLion 模板代码
# ========================================
add_executable(Data main.cpp 1.cpp)

# ========================================
# 自动收集 第三阶段-录制代码 下所有 .cpp 文件
# 每个文件独立成为一个可执行目标
# ========================================
file(GLOB_RECURSE RECORD_CPP_FILES "../第三阶段-录制代码/*.cpp")

set(COUNTER 0)

foreach(CPP_FILE ${RECORD_CPP_FILES})
    get_filename_component(FILENAME_WE ${CPP_FILE} NAME_WE)

    # 跳过非独立的辅助文件（没有 main 函数）
    if(FILENAME_WE STREQUAL "person")
        continue()
    endif()

    math(EXPR COUNTER "${COUNTER} + 1")

    # 提取祖父目录名中的 ASCII 字符（数字/字母），作为可读前缀
    get_filename_component(DIRECTORY ${CPP_FILE} DIRECTORY)
    get_filename_component(PARENT_DIR ${DIRECTORY} NAME)
    get_filename_component(GP "${DIRECTORY}" DIRECTORY)
    get_filename_component(GRANDPARENT_DIR ${GP} NAME)

    # 只保留 ASCII 字母和数字
    string(REGEX REPLACE "[^a-zA-Z0-9_]" "" SAFE_PREFIX "${GRANDPARENT_DIR}")

    # 生成 ASCII 安全的 target 名称
    if(SAFE_PREFIX)
        set(TARGET_NAME "${SAFE_PREFIX}_${COUNTER}")
    else()
        set(TARGET_NAME "cpp_demo_${COUNTER}")
    endif()

    add_executable("${TARGET_NAME}" "${CPP_FILE}")
endforeach()
