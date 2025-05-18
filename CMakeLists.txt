cmake_minimum_required(VERSION 3.10)

#--------------------------------------------------------------------------------------------------
# variables
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_NAME GithubUnfollowersChecker)

#--------------------------------------------------------------------------------------------------
# project
project(${PROJECT_NAME})

if (MSVC)
	# enable VS-Solution filters support
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif (MSVC)

#--------------------------------------------------------------------------------------------------
# builds
add_executable(${PROJECT_NAME}
	${SRC_DIR}/main.cpp
)

# properties
set_target_properties(${PROJECT_NAME}
	PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED ON
)


#--------------------------------------------------------------------------------------------------
# dependencies
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr nlohmann_json::nlohmann_json)

#--------------------------------------------------------------------------------------------------
# compiler settings
if (MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

	add_compile_options("/std:c++latest")
	
	target_compile_options(${PROJECT_NAME} PRIVATE
		/W4
	)
else ()
	target_compile_options(${PROJECT_NAME} PRIVATE
		-std=c++23 -Wall -Wextra -pedantic -Werror
	)
endif (MSVC)
