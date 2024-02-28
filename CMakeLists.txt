cmake_minimum_required(VERSION 3.28.3)

project(footy-sim VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(thirdparty/glfw-3.3.9)
add_subdirectory(thirdparty/glad)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(footy-sim ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(footy-sim glfw glad)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
)

# Copy contents to root, works for some reason
file(COPY resources DESTINATION /)
