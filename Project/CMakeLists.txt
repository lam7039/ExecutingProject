cmake_minimum_required(VERSION 3.6)

project(ExecutableProject)

set(GAMEENGINE3D_DIR "${PROJECT_SOURCE_DIR}/../../GameEngine3D")
set(ROOT_DIR "${PROJECT_SOURCE_DIR}/../")

include_directories(
	${PROJECT_SOURCE_DIR}/../Include
	${GAMEENGINE3D_DIR}/Include
)

if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset configurations" FORCE)
endif()

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/../Source/*.cpp)

file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/../Include/*.h)

add_executable(ExecutableProject WIN32 ${SOURCE_FILES} ${HEADER_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ExecutableProject)

if(${WIN32})
	set(DEBUG_LINK_LIBRARIES
		debug ${GAMEENGINE3D_DIR}/Libraries/debug/GameEngine3D.lib
	)
	set(RELEASE_LINK_LIBRARIES
		optimized ${GAMEENGINE3D_DIR}/Libraries/release/GameEngine3D.lib
	)
	set(ALL_LINK_LIBRARIES ${DEBUG_LINK_LIBRARIES} ${RELEASE_LINK_LIBRARIES})
	target_link_libraries(ExecutableProject ${ALL_LINK_LIBRARIES})
	add_custom_command(TARGET ExecutableProject PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "../../../GameEngine3D/Binaries/debug/GameEngine3D.dll" "${ROOT_DIR}/Development/GameEngine3D.dll"
	)
endif()