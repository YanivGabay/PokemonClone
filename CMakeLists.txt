cmake_minimum_required (VERSION 3.23)

project (MiniMon)
set (MY_AUTHORS "shahar_asher-yaniv_gabay")


include (cmake/CompilerSettings.cmake)


add_executable (${CMAKE_PROJECT_NAME} WIN32)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

add_subdirectory (include)
add_subdirectory (src) 
add_subdirectory (resources)
add_subdirectory (external/box2d/src)

include (cmake/Zip.cmake)

set (SFML_LOCATION "C:/SFML/SFML-2.5.1")
set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

#--------------------------------------

# Add the include directory for nlohmann json
include_directories(${CMAKE_SOURCE_DIR}/external/json-develop/single_include)

# Add the library to your project
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${CMAKE_SOURCE_DIR}/external/json-develop/single_include)

# Link the library to your executable
target_link_libraries(${CMAKE_PROJECT_NAME} nlohmann_json)

#--------------------------------------

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
    
    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else()
    message("Doxygen needs to be installed to generate documentation")
endif()




find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio sfml-main)
target_link_libraries (${CMAKE_PROJECT_NAME} box2d)

include (cmake/SFML.cmake)