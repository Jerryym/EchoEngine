# CMakeList.txt: Echo 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.16)

#设置版本号
set(ECHO_VERSION_MAJOR 0)
set(ECHO_VERSION_MINOR 1)
set(ECHO_VERSION_PATCH 0)
set(ECHO_VERSION "${ECHO_VERSION_MAJOR}.${ECHO_VERSION_MINOR}.${ECHO_VERSION_PATCH}")
message(STATUS "ECHO_VERSION: ${ECHO_VERSION}")
project(Echo VERSION ${ECHO_VERSION} LANGUAGES CXX)
set(ECHO_LIB_NAME Echo)

# 定义头文件列表
set(ECHO_HEADERS
	src/Core.h
	src/Echo.h

	# Core
	src/Core/Application.h
	src/Core/EntryPoint.h
	src/Core/Events/Event.h
	src/Core/Events/ApplicationEvent.h
	src/Core/Events/KeyEvent.h
	src/Core/Events/MouseEvent.h
	src/Core/Layer.h
	src/Core/LayerStack.h

	# GUI
	src/GUI/MainWindow.h
	
	# Renderer
	src/Renderer/GraphicsContext.h
	src/Renderer/Buffer.h
	src/Renderer/VertexArray.h
	src/Renderer/Shader.h
	src/Renderer/RendererAPI.h
	src/Renderer/RenderCommand.h
	src/Renderer/Renderer.h

	# Platform
	src/Platform/Windows/MainWindow_Windows.h
	src/Platform/OpenGL/OpenGLContext.h
	src/Platform/OpenGL/OpenGLBuffer.h
	src/Platform/OpenGL/OpenGLVertexArray.h
	src/Platform/OpenGL/OpenGLShader.h
	src/Platform/OpenGL/OpenGLRendererAPI.h

	# Utils
	src/Utils/Log.h
	src/Utils/KeyCodes.h
	src/Utils/MouseCodes.h
	src/Utils/Input.h
	src/Utils/TimeStep.h
)

# 定义源文件列表
set(ECHO_SOURCES
	# Core
	src/Core/Application.cpp
	src/Core/Layer.cpp
	src/Core/LayerStack.cpp

	# GUI
	src/GUI/MainWindow.cpp

	# Renderer
	
	src/Renderer/Buffer.cpp
	src/Renderer/VertexArray.cpp
	src/Renderer/Shader.cpp
	src/Renderer/RenderCommand.cpp
	src/Renderer/Renderer.cpp

	# Platform
	src/Platform/Windows/MainWindow_Windows.cpp
	src/Platform/Windows/WindowsInput.cpp
	src/Platform/OpenGL/OpenGLContext.cpp
	src/Platform/OpenGL/OpenGLBuffer.cpp
	src/Platform/OpenGL/OpenGLVertexArray.cpp
	src/Platform/OpenGL/OpenGLShader.cpp
	src/Platform/OpenGL/OpenGLRendererAPI.cpp

	# Utils
	src/Utils/Log.cpp
	src/Utils/TimeStep.cpp
)

# 创建一个共享库
add_library(${ECHO_LIB_NAME} SHARED
	${ECHO_SOURCES}
	${ECHO_HEADERS}
)

# 预编译头文件
target_precompile_headers(${ECHO_LIB_NAME} PRIVATE src/echopch.h)

# 添加目录
target_include_directories(${ECHO_LIB_NAME} PUBLIC
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/vendor/spdlog/include
	${PROJECT_SOURCE_DIR}/vendor/GLFW/include
	${PROJECT_SOURCE_DIR}/vendor/Glad/include
	${PROJECT_SOURCE_DIR}/vendor/glm
)

# 添加GLFW
add_subdirectory(vendor/GLFW)
target_link_libraries(${ECHO_LIB_NAME} PUBLIC glfw)
# 添加Glad
add_subdirectory(vendor/Glad)
target_link_libraries(${ECHO_LIB_NAME} PUBLIC Glad)

# 预处理宏定义
target_compile_definitions(${ECHO_LIB_NAME} PRIVATE 
	_CRT_SECURE_NO_WARNINGS
	ECHO_BUILD_DLL
	ECHO_PLATFORM_WINDOWS
	GLFW_INCLUDE_NONE
)

# 设置目标属性
include(GNUInstallDirs)
set_target_properties(${ECHO_LIB_NAME} PROPERTIES
	CXX_EXTENSIONS OFF
	DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
	VERSION ${ECHO_VERSION}
	EXPORT_NAME ${ECHO_LIB_NAME}
	
	# Debug
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/Echo
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/Echo
	LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/Echo

	# Release
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/Echo
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/Echo
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/Echo
)

# 设置Visual Studio的文件树结构
file(GLOB Base_SRC "src/*.h" "src/*.cpp")
file(GLOB Core_SRC "src/Core/*.h" "src/Core/*.cpp")
file(GLOB Event_SRC "src/Core/Events/*.h" "src/Core/Events/*.cpp")
file(GLOB GUI_SRC "src/GUI/*.h" "src/GUI/*.cpp")
file(GLOB Utils_SRC "src/Utils/*.h" "src/Utils/*.cpp")
file(GLOB Renderer_SRC "src/Renderer/*.h" "src/Renderer/*.cpp")
file(GLOB Windows_SRC "src/Platform/Windows/*.h" "src/Platform/Windows/*.cpp")
file(GLOB OpenGL_SRC "src/Platform/OpenGL/*.h" "src/Platform/OpenGL/*.cpp")
source_group("src" FILES ${Base_SRC})
source_group("src\\Core" FILES ${Core_SRC})
source_group("src\\Core\\Events" FILES ${Event_SRC})
source_group("src\\GUI" FILES ${GUI_SRC})
source_group("src\\Utils" FILES ${Utils_SRC})
source_group("src\\Renderer" FILES ${Renderer_SRC})
source_group("src\\Platform\\Windows" FILES ${Windows_SRC})
source_group("src\\Platform\\OpenGL" FILES ${OpenGL_SRC})

# 设置生成后事件
add_custom_command(
	TARGET ${ECHO_LIB_NAME} POST_BUILD

	# 创建 Debug 或 Release 的目标文件夹
	COMMAND ${CMAKE_COMMAND} -E make_directory
	$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/Echo,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/Echo>

	# 复制GLFW的DLL文件到相应的文件夹
	COMMAND ${CMAKE_COMMAND} -E copy
	$<TARGET_FILE:glfw> # 获取生成的 DLL 文件
	$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/Echo/glfw.dll,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/Echo/glfw.dll>

	COMMENT "Copying GLFW DLL to Echo folder"
	VERBATIM
)
