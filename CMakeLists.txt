cmake_minimum_required(VERSION 3.10)
project(RestaurantManagementSystem VERSION 1.0)

# C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 数据文件目录
set(DATA_DIR ${CMAKE_SOURCE_DIR}/data)

# 设置构建目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# 将数据文件复制到构建目录
file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/bin)

# 添加子目录
add_subdirectory(src)

# 启用测试
enable_testing()
add_subdirectory(test)
