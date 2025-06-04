cmake_minimum_required(VERSION 3.16)
project(CMark-plus-plus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets)

qt_standard_project_setup()

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
configure_file(resources/test.md ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/test.md COPYONLY)

set(PROJECT_SOURCE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Markdown_BlockElement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Markdown_InlineElement.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Markdown_Parser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Html_Renderer.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/EHsc")