cmake_minimum_required (VERSION 3.23)

project (MiniMon)
set (MY_AUTHORS "shahar_asher-yaniv_gabay")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME})

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)
add_subdirectory (external/box2d/src)

include (cmake/Zip.cmake)

set (SFML_LOCATION "C:/SFML/SFML-2.5.1")
set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")


set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/external/boost_1_82_0")  

find_package(Boost 1.82.0)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
else()
    message(WARNING "Boost not found. Some features may be disabled.")
endif()

find_package (SFML 2.5 COMPONENTS graphics REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-main)
target_link_libraries (${CMAKE_PROJECT_NAME} box2d)

include (cmake/SFML.cmake)