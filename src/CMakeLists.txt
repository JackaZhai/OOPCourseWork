# 收集所有源文件
file(GLOB_RECURSE SOURCES "*.cpp")

# 创建可执行文件
add_executable(restaurant_system ${SOURCES})

# 链接库（如有需要可添加）
# target_link_libraries(restaurant_system some_library)

# 安装规则
install(TARGETS restaurant_system DESTINATION bin)
