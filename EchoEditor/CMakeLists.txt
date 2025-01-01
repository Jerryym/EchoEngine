# CMakeList.txt: EchoEditor 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.16)

project(EchoEditor VERSION ${ECHOENGINE_VERSION} LANGUAGES CXX)
set(Editor_NAME EchoEditor)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 加载Qt库，设置最低版本为6.5.3
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} 6.5.3 COMPONENTS Core Widgets OpenGLWidgets)
message(STATUS "Current Qt Version: Qt${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
qt_standard_project_setup()

# 定义头文件列表
set(EDITOR_HEADERS
	#GUI
    src/GUI/MainWindow.h
	src/GUI/ConsoleDock.h 
	src/GUI/GraphicWidget.h
)

# 定义源文件列表
set(EDITOR_SOURCES
	#GUI
	src/GUI/MainWindow.cpp
	src/GUI/ConsoleDock.cpp
	src/GUI/GraphicWidget.cpp
	src/main.cpp
)

add_executable(EchoEditor WIN32
    ${EDITOR_HEADERS}
    ${EDITOR_SOURCES}
	res/EchoEditor.qrc
)

# 预编译头文件
target_precompile_headers(${Editor_NAME} PRIVATE src/pch.h)

# 添加头文件
target_include_directories(${Editor_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/GUI
)

target_link_libraries(${Editor_NAME} PUBLIC Echo)
target_link_libraries(${Editor_NAME} PUBLIC NestApp)
target_link_libraries(${Editor_NAME} PUBLIC NestUI)
target_link_libraries(${Editor_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

# 预处理宏定义
target_compile_definitions(${Editor_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS GLFW_INCLUDE_NONE)

set_target_properties(${Editor_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
    CXX_EXTENSIONS OFF
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    VERSION ${ECHOENGINE_VERSION}
    EXPORT_NAME ${Editor_NAME}
    
    # Debug
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/EchoEditor
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/EchoEditor
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/EchoEditor

    # Release
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/EchoEditor
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/EchoEditor
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/EchoEditor
)

# 设置Visual Studio的文件树结构
file(GLOB Base_SRC "src/*.h" "src/*.cpp")
file(GLOB Core_SRC "src/Core/*.h" "src/Core/*.cpp")
file(GLOB GUI_SRC "src/GUI/*.h" "src/GUI/*.cpp")
source_group("src" FILES ${Base_SRC})
source_group("src\\Core" FILES ${Core_SRC})
source_group("src\\GUI" FILES ${GUI_SRC})

# 设置生成后事件
add_custom_command(
    TARGET EchoEditor POST_BUILD

    # 复制NestApp的DLL文件到相应的文件夹
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:NestApp> # 获取生成的 DLL 文件
    $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/EchoEditor/NestAppd.dll,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/EchoEditor/NestApp.dll>

	# 复制SARibbon的DLL文件到相应的文件夹
	COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:SARibbonBar> # 获取生成的 DLL 文件
    $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/EchoEditor/SARibbonBard.dll,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/EchoEditor/SARibbonBar.dll>

    # 复制NestUI的DLL文件到相应的文件夹
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:NestUI> # 获取生成的 DLL 文件
    $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/EchoEditor/NestUId.dll,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/EchoEditor/NestUI.dll>

	# 复制GLFW的DLL文件到相应的文件夹
	COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:glfw> # 获取生成的 DLL 文件
    $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/EchoEditor/glfw.dll,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/EchoEditor/glfw.dll>

	# 复制NestUI的DLL文件到相应的文件夹
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:Echo> # 获取生成的 DLL 文件
    $<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/bin/Debug-windows-x86_64/EchoEditor/Echod.dll,${CMAKE_BINARY_DIR}/bin/Release-windows-x86_64/EchoEditor/Echo.dll>

    VERBATIM
)
