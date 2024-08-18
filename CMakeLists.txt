cmake_minimum_required(VERSION 3.15)
project(OpenGLApp)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
fetchcontent_declare(
        glew
        URL https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    fetchcontent_populate(glew)

    add_subdirectory(${glew_SOURCE_DIR}/build/cmake ${glew_BINARY_DIR})
endif()

fetchcontent_declare(
        glfw3
        URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
fetchcontent_makeavailable(glfw3)

find_package(OpenGL REQUIRED)
file(GLOB SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/vendor/glm/*.cpp
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/*.cpp
        ${CMAKE_SOURCE_DIR}/src/vendor/stb_image/*.cpp
        ${CMAKE_SOURCE_DIR}/src/test/*.cpp)
file(GLOB HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/vendor/glm/*.h
        ${CMAKE_SOURCE_DIR}/src/vendor/imgui/*.h
        ${CMAKE_SOURCE_DIR}/src/vendor/stb_image/*.h
        ${CMAKE_SOURCE_DIR}/src/test/*.h)
add_executable(OpenGLApp ${HEADER_FILES} ${SRC_FILES}
        src/test/BatchRenderTest.cpp
        src/test/BatchRenderTest.h)

add_compile_definitions(GLEW_STATIC)

target_include_directories(OpenGLApp
        PRIVATE
        ${glew_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/test
        ${CMAKE_SOURCE_DIR}/src/vendor
        ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(OpenGLApp glfw glew_s OpenGL::GL)

install(TARGETS OpenGLApp DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/res DESTINATION .)

include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_NAME "OpenGLTest")
set(CPACK_NSIS_DISPLAY_NAME "OpenGLTest")
set(CPACK_NSIS_PACKAGE_NAME "OpenGLTest")
set(CPACK_NSIS_MODIFY_PATH ON)
include(CPack)