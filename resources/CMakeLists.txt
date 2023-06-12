

configure_file("maleSpriteSheet.png" ${CMAKE_BINARY_DIR}/resources COPYONLY)
configure_file("spritesheet.png" ${CMAKE_BINARY_DIR}/resources COPYONLY)
configure_file("firstTown.json" ${CMAKE_BINARY_DIR}/resources COPYONLY)

file(COPY ${CMAKE_SOURCE_DIR}/resources/fonts DESTINATION ${CMAKE_BINARY_DIR}/resources)
configure_file("fonts/Pokemon.ttf" ${CMAKE_BINARY_DIR}/resources/fonts COPYONLY)