# CMakeList.txt: SandBox 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.16)

#设置版本号
set(SANDBOX_VERSION 0.1.0)
message(STATUS "SANDBOX_VERSION: ${SANDBOX_VERSION}")
project(SandBox VERSION ${SANDBOX_VERSION} LANGUAGES CXX)

set(SANDBOX_HEADERS
	src/ExampleLayer.h
)

set(SANDBOX_SOURCES
	src/ExampleLayer.cpp
	src/SandBoxApp.cpp
)

add_executable(SandBox
	${SANDBOX_HEADERS}
	${SANDBOX_SOURCES}
)

# 预编译头文件
target_precompile_headers(SandBox PRIVATE src/pch.h)

# 添加目录
target_include_directories(SandBox PUBLIC
	${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(SandBox PUBLIC Echo)

# 预处理宏定义
target_compile_definitions(SandBox PRIVATE 
	ECHO_PLATFORM_WINDOWS
	GLM_ENABLE_EXPERIMENTAL
)

# 设置目标属性
include(GNUInstallDirs)
set_target_properties(SandBox PROPERTIES
	CXX_EXTENSIONS OFF
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	VERSION ${SANDBOX_VERSION}
	EXPORT_NAME SandBox
	
	# Debug
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/SandBox
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/SandBox
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/SandBox

	# Release
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/SandBox
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/SandBox
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/SandBox
)

# 设置Visual Studio的文件树结构
file(GLOB Base_SRC "src/*.h" "src/*.cpp")
source_group("src" FILES ${Base_SRC})

# 设置生成后事件
add_custom_command(
	TARGET SandBox POST_BUILD

	# 复制GLFW的DLL文件到相应的文件夹
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:glfw> # 获取生成的 DLL 文件
	$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/SandBox/glfw.dll,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/SandBox/glfw.dll>

	# 复制GLFW的DLL文件到相应的文件夹
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:Echo> # 获取生成的 DLL 文件
	$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/SandBox/Echod.dll,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/SandBox/Echo.dll>

	VERBATIM
)
