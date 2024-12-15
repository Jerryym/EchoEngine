cmake_minimum_required(VERSION 3.16)
project(Glad)
set(Glad_LIB_NAME Glad)

add_library(${Glad_LIB_NAME} include/glad/glad.h src/glad.c)
target_include_directories(${Glad_LIB_NAME} PUBLIC include/)

set_target_properties(${Glad_LIB_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    VERSION ${ECHO_VERSION}
    EXPORT_NAME ${Glad_LIB_NAME}
    
    # Debug
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/Glad
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/Glad
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Debug-windows-x86_64/Glad

    # Release
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/Glad
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/Glad
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/../bin/Release-windows-x86_64/Glad
)
