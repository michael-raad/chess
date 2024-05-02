cmake_minimum_required(VERSION 3.22)

project(
  chess
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Find the X11 package
find_package(X11 REQUIRED)

# Define a function to add sources
function(add_sources target_name source_dir)
  file(GLOB_RECURSE sources "${source_dir}/*.cc")
  target_sources(${target_name} PRIVATE ${sources})
endfunction()

# Create an executable target
add_executable(${PROJECT_NAME})

# Add sources to the target
add_sources(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Include directories for the target
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link X11 libraries to the target
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
