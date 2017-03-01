find_package(Doxygen)
if(NOT DOXYGEN_FOUND)
    message(WARNING "doxygen not found - target will be unavailable.")
    return()
endif()
set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${doxyfile_in} ${doxyfile} @ONLY)

add_custom_target(documentation
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        COMMAND ${CMAKE_COMMAND} -E echo "Done."
        )

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
        DESTINATION ../build/docs)