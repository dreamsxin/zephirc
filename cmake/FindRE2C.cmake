# FindRE2C.cmake
#
# Provides a macro to generate custom build rules:
#
# RE2C_TARGET(
#     [NAME <target>]
#     [INPUT <input>]
#     [OUTPUT <output>]
#     [COMPILE_FLAGS <flags>]
#     [DEPENDS <list of files>])
#
# which creates a custom commands to generate the <output> file from the <output>
# file. If COMPILE_FLAGS option is specified, the next parameter is added to the
# re2c commands line. Name is an alias used to get details of this custom
# commands.
#
# Argument details:
#   - NAME <target> (mandatory):               cmake target name to build the lexer
#   - INPUT <input> (mandatory):               the input file to give to re2c
#   - OUTPUT <output> (mandatory):             the output file generated by re2c
#   - OPTIONS <options> (optionnal):           command line options to pass to re2c
#   - DEPENDS <file1> ... <file2> (optionnal): a list of files the lexer depends on
#
# Example:
#
# find_package(Re2c)
# RE2C_TARGET(
#     NAME MyScanner
#     INPUT scanner.re
#     OUPUT scanner.cpp
#     COMPILE_FLAGS "-W"
#     DEPENDS scanner.hpp)
#
# add_library(MyLib scanner.hpp "${RE2C_MyScanner_OUTPUTS}")
# add_executable(Foo Foo.cpp)
#
# target_link_libraries(Foo PRIVATE MyLib)
#
# The module defines the following variables:
#
# RE2C_EXECUTABLE - the path to the re2c executable
# RE2C_VERSION    - version of the re2c

if(UNIX)
    find_program(RE2C_EXECUTABLE
        NAMES re2c
        PATHS $ENV{RE2C_DIR} /usr /usr/local /opt /opt/local
        PATH_SUFFIXES re2c/bin bin
        DOC "path to the re2c executable")
elseif(WIN32)
    find_program(RE2C_EXECUTABLE
        NAMES re2c.exe
        PATHS $ENV{RE2C_DIR} C:/
        PATH_SUFFIXES ""
        DOC "path to the re2c executable")
endif()

mark_as_advanced(RE2C_EXECUTABLE)

if(RE2C_EXECUTABLE)
    execute_process(COMMAND ${RE2C_EXECUTABLE} --vernum
        OUTPUT_VARIABLE RE2C_VERSION_RAW_OUTPUT
        RESULT_VARIABLE RE2C_VERSION_RESULT
        ERROR_VARIABLE RE2C_VERSION_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    if(RE2C_VERSION_RESULT)
        string(CONCAT RE2C_FIND_ERROR
              "Command \"${RE2C_EXECUTABLE} --vernum\" failed "
              "with output:\n${RE2C_VERSION_ERROR}")

        message(FATAL_ERROR "${RE2C_FIND_ERROR}")
    endif()

    math(EXPR RE2C_MAJOR_VERSION "${RE2C_VERSION_RAW_OUTPUT} / 10000")
    math(EXPR RE2C_MINOR_VERSION "(${RE2C_VERSION_RAW_OUTPUT} - ${RE2C_MAJOR_VERSION} * 10000) / 100")
    math(EXPR RE2C_PATCH_VERSION "${RE2C_VERSION_RAW_OUTPUT} - ${RE2C_MAJOR_VERSION} * 10000 - ${RE2C_MINOR_VERSION} * 100")

    set(RE2C_VERSION "${RE2C_MAJOR_VERSION}.${RE2C_MINOR_VERSION}.${RE2C_PATCH_VERSION}")

    include(CMakeParseArguments)
    macro(RE2C_TARGET)
        cmake_parse_arguments(PARSED_ARGS "" "NAME;INPUT;OUTPUT" "COMPILE_FLAGS;DEPENDS" ${ARGN})

        if(NOT PARSED_ARGS_NAME)
            message(FATAL_ERROR "RE2C_TARGET expect a target name")
        endif()

        if(NOT PARSED_ARGS_INPUT)
            message(FATAL_ERROR "RE2C_TARGET expect an input filename")
        endif()

        if(NOT PARSED_ARGS_OUTPUT)
            message(FATAL_ERROR "RE2C_TARGET expect an output filename")
        endif()

        get_filename_component(PARSED_ARGS_INPUT ${PARSED_ARGS_INPUT} ABSOLUTE)
        get_filename_component(PARSED_ARGS_OUTPUT ${PARSED_ARGS_OUTPUT} ABSOLUTE)

        add_custom_command(
            COMMAND ${RE2C_EXECUTABLE}
                    ${PARSED_ARGS_COMPILE_FLAGS}
                    -o${PARSED_ARGS_OUTPUT} ${PARSED_ARGS_INPUT}
            OUTPUT  ${PARSED_ARGS_OUTPUT}
            DEPENDS ${PARSED_ARGS_INPUT} ${PARSED_ARGS_DEPENDS}
            COMMENT "[RE2C][${PARSED_ARGS_NAME}] Building scanner with ${RE2C_EXECUTABLE}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM USES_TERMINAL)

        add_custom_target(${PARSED_ARGS_NAME}
            SOURCES ${PARSED_ARGS_INPUT}
            DEPENDS ${PARSED_ARGS_OUTPUT})

        set_property(DIRECTORY APPEND
            PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${PARSED_ARGS_OUTPUT}")

        set(RE2C_${PARSED_ARGS_NAME}_OUTPUTS ${PARSED_ARGS_OUTPUT})
    endmacro()

    include(FindPackageHandleStandardArgs)

    if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED AND NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
        find_package_handle_standard_args(${CMAKE_FIND_PACKAGE_NAME}
            REQUIRED_VARS RE2C_EXECUTABLE
            VERSION_VAR RE2C_VERSION)
    else()
        find_package_handle_standard_args(${CMAKE_FIND_PACKAGE_NAME}
            "No re2c found in the $PATH. Consider install re2c or/and add re2c executable to the $PATH"
            RE2C_EXECUTABLE)
    endif()
endif()

# FindRe2c.cmake ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
