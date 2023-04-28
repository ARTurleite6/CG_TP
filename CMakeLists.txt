cmake_minimum_required(VERSION 3.24)
project(CG_TP CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(my_math)
add_subdirectory(generator)
add_subdirectory(engine)

include(FetchContent)
FetchContent_Declare(
    tiny_xml
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
    GIT_TAG 9.0.0
    )

FetchContent_MakeAvailable(tiny_xml)

find_package(GLUT REQUIRED)

find_package(OpenGL REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/my_math)
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if(NOT APPLE)
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif(NOT APPLE)

target_precompile_headers(my_math PRIVATE include/pch.h)
target_link_libraries(engine GLUT::GLUT tinyxml2::tinyxml2 ${GLEW_LIBRARIES} my_math)
target_link_libraries(generator my_math)
target_include_directories(generator PRIVATE ${PROJECT_SOURCE_DIR}/my_math)
target_include_directories(engine PRIVATE ${PROJECT_SOURCE_DIR}/my_math)
target_precompile_headers(engine PRIVATE include/pch.h)
target_precompile_headers(generator PRIVATE include/pch.h)


if(WIN32)

    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")


	include_directories(${TOOLKITS_FOLDER}/glut )
	target_link_libraries(engine ${OPENGL_LIBRARIES}
										  ${TOOLKITS_FOLDER}/glut/glut32.lib my_math)

	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" )

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	
	target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} my_math)
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)

endif(WIN32)

