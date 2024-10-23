# Create an interface library for nlohmann JSON
add_library(nlohmann_json INTERFACE)

# Specify the include directory for the header files
target_include_directories(nlohmann_json INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann)
