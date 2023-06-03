
configure_file("malefemaleplayer.png" ${CMAKE_BINARY_DIR}/resources COPYONLY)
configure_file("tileset.png" ${CMAKE_BINARY_DIR}/resources COPYONLY)
configure_file("tilesetbuilding.png" ${CMAKE_BINARY_DIR}/resources COPYONLY)
configure_file("framesSpritesheet.png" ${CMAKE_BINARY_DIR}/resources COPYONLY)

file(COPY ${CMAKE_SOURCE_DIR}/resources/fonts DESTINATION ${CMAKE_BINARY_DIR}/resources)
configure_file("fonts/Pokemon.FON" ${CMAKE_BINARY_DIR}/resources/fonts COPYONLY)