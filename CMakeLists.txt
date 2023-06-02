cmake_minimum_required(VERSION 3.9.1)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)

project(
  main
  VERSION 0.1.0
  LANGUAGES CXX
)

file(GLOB_RECURSE PROJECT_BASE_INCLUDE_LIST include/**/*.hpp)
file(GLOB_RECURSE PROJECT_BASE_SRC_LIST src/**/*.cpp)
set(PROJECT_BASE_INCLUDE ${CMAKE_CURRENT_LIST_DIR}/include)

file(GLOB_RECURSE tkgpg_BASE_INCLUDE_LIST modules/tkgpg/include/**/*.hpp)
file(GLOB_RECURSE tkgpg_BASE_SRC_LIST modules/tkgpg/src/**/*.cpp)
set(tkgpg_BASE_INCLUDE modules/tkgpg/include)

add_executable(${PROJECT_NAME} main.cpp
  ${tkgpg_BASE_INCLUDE_LIST} ${tkgpg_BASE_SRC_LIST}
  ${PROJECT_BASE_INCLUDE_LIST} ${PROJECT_BASE_SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC
  ${tkgpg_BASE_INCLUDE}
  ${PROJECT_BASE_INCLUDE})

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/asset/fonts ${CMAKE_CURRENT_BINARY_DIR}/fonts
)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES 
  LINKER_LANGUAGE CXX
  CXX_STANDARD 17
)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(tkcore CONFIG REQUIRED)
find_package(tkgl CONFIG REQUIRED)
find_package(tkbox CONFIG REQUIRED)
find_package(tkgm CONFIG REQUIRED)
find_package(tkgui CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
  nlohmann_json::nlohmann_json
  GLEW::GLEW
  glfw
  imgui::imgui
  box2d::box2d
  tkcore::tkcore
  tkgl::tkgl
  tkbox::tkbox
  tkgm::tkgm
  tkgui::tkgui)