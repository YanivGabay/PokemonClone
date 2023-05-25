# Zip target generates .zip file in the parent dir of the project, but only if it builds correctly
# ZipBackup target generates similar .zip file even if it doesn't build, and adds a timestamp to the filename

set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY ON)
set (CPACK_SOURCE_GENERATOR "ZIP")
set (CPACK_SOURCE_IGNORE_FILES
  \\.git/
  \\.vs/
  out/
  .*\\.zip
)
set (MY_ZIP_FILENAME ${CMAKE_PROJECT_NAME}-${MY_AUTHORS})
set (CPACK_VERBATIM_VARIABLES YES)
set (CPACK_SOURCE_PACKAGE_FILE_NAME ${MY_ZIP_FILENAME})
include (CPack)

cmake_path (GET CMAKE_SOURCE_DIR PARENT_PATH MY_ZIP_TARGET_DIR)
add_custom_target (Zip ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target package_source
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${MY_ZIP_FILENAME}.zip ${MY_ZIP_TARGET_DIR}
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "*** ${MY_ZIP_TARGET_DIR}/${MY_ZIP_FILENAME}.zip file created ***")
add_dependencies (Zip ${CMAKE_PROJECT_NAME})

# Using cmake script to get updated timestamp on each run
file (WRITE ${CMAKE_BINARY_DIR}/ZipBackup.cmake "string (TIMESTAMP MY_TIMESTAMP \"%Y-%m-%d-%H-%M-%S\")\n")
file (APPEND ${CMAKE_BINARY_DIR}/ZipBackup.cmake "execute_process (COMMAND ${CMAKE_COMMAND} --build \"${CMAKE_BINARY_DIR}\" --target package_source)\n")
file (APPEND ${CMAKE_BINARY_DIR}/ZipBackup.cmake "execute_process (COMMAND ${CMAKE_COMMAND} -E copy \"${CMAKE_BINARY_DIR}/${MY_ZIP_FILENAME}.zip\" \"${MY_ZIP_TARGET_DIR}/${MY_ZIP_FILENAME}-\${MY_TIMESTAMP}.zip\")\n")
file (APPEND ${CMAKE_BINARY_DIR}/ZipBackup.cmake "execute_process (COMMAND ${CMAKE_COMMAND} -E echo \"\")\n")
file (APPEND ${CMAKE_BINARY_DIR}/ZipBackup.cmake "execute_process (COMMAND ${CMAKE_COMMAND} -E echo \"***\" ${MY_ZIP_TARGET_DIR}/${MY_ZIP_FILENAME}-\${MY_TIMESTAMP}.zip \"file created ***\")\n")

add_custom_target (ZipBackup ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/ZipBackup.cmake)
