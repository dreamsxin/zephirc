# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.
#
# Initially written by Alexander Haase <alexander.haase@rwth-aachen.de>
# Adapted by Serghei Iakovlev <egrep@protonmail.ch>

# Include required Modules
include(FindPackageHandleStandardArgs)

get_property(ENABLED_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)
foreach(LANG ${ENABLED_LANGUAGES})
  # Gcov evaluation is dependent on the used compiler. Check gcov support for
  # each compiler that is used. If gcov binary was already found for this
  # compiler, do not try to find it again.

  if(NOT GCOV_${CMAKE_${LANG}_COMPILER_ID}_EXE)
    get_filename_component(COMPILER_PATH "${CMAKE_${LANG}_COMPILER}" PATH)

    if("${CMAKE_${LANG}_COMPILER_ID}" STREQUAL "GNU")
      # Some distributions like OSX (homebrew) ship gcov with the compiler
      # version appended as gcov-x. To find this binary we'll build the
      # suggested binary name with the compiler version.
      string(REGEX MATCH "^[0-9]+" GCC_VERSION
                   "${CMAKE_${LANG}_COMPILER_VERSION}")

      find_program(
        GCOV_EXE
        NAMES gcov-${GCC_VERSION} gcov
        HINTS ${COMPILER_PATH})
    elseif("${CMAKE_${LANG}_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
      # Some distributions like Debian ship llvm-cov with the compiler version
      # appended as llvm-cov-x.y. To find this binary we'll build the suggested
      # binary name with the compiler version.
      string(REGEX MATCH "^[0-9]+.[0-9]+" LLVM_VERSION
                   "${CMAKE_${LANG}_COMPILER_VERSION}")

      find_program(
        LLVM_COV_EXE
        NAMES llvm-cov-${LLVM_VERSION} llvm-cov
        HINTS ${COMPILER_PATH})
      mark_as_advanced(LLVM_COV_EXE)

      if(LLVM_COV_EXE)
        get_filename_component(_MOD_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
        configure_file("${_MOD_DIR}/llvm-cov-wrapper.in"
                       "${zephir_BINARY_DIR}/llvm-cov-wrapper")

        execute_process(COMMAND chmod 755 ${zephir_BINARY_DIR}/llvm-cov-wrapper)

        set(GCOV_EXE "${zephir_BINARY_DIR}/llvm-cov-wrapper")
      endif()

      if(NOT GCOV_EXE)
        # Fall back to gcov binary if llvm-cov was not found or is incompatible.
        # This is the default on OSX, but may crash on recent Linux versions.
        find_program(GCOV_EXE gcov HINTS ${COMPILER_PATH})
        mark_as_advanced(GCOV_EXE)
      endif()
    endif()

    if(GCOV_EXE)
      set(GCOV_${CMAKE_${LANG}_COMPILER_ID}_EXE
          "${GCOV_EXE}"
          CACHE STRING "${LANG} gcov binary.")

      if(NOT CMAKE_REQUIRED_QUIET)
        message(
          STATUS "Found gcov for ${CMAKE_${LANG}_COMPILER_ID}: ${GCOV_EXE}")
      endif()

      unset(GCOV_EXE CACHE)
    endif()
  endif()
endforeach()

# Add a new global target for all gcov targets. This target could be used to
# generate the gcov files for the whole project instead of calling <TARGET>-gcov
# for each target.
if(NOT TARGET gcov)
  add_custom_target(gcov)
endif()

# Add gcov evaluation for target <TARGET_NAME>.
#
# ~~~
# Only sources of this target will be evaluated and no dependencies will be
# added. It will call gcov on any source file of <TARGET_NAME> once and store
# the gcov file in the same directory.
#
# Required:
# TARGET_NAME - Name of the target to generate code coverage for.
# ~~~
function(add_gcov_target TARGET_NAME)
  get_target_property(TARGET_BIN_DIR ${TARGET_NAME} BINARY_DIR)
  set(TARGET_DIR ${TARGET_BIN_DIR}/CMakeFiles/${TARGET_NAME}.dir)

  # We don't have to check, if the target has support for coverage, thus this
  # will be checked by target_code_coverage in CodeCoverage.cmake. Instead we
  # have to determine which gcov binary to use.
  get_target_property(TARGET_SOURCES ${TARGET_NAME} SOURCES)

  set(SOURCES "")
  set(TARGET_COMPILER "")

  foreach(FILE ${TARGET_SOURCES})
    relative_path(${FILE} FILE)
    if(NOT "${FILE}" STREQUAL "")
      detect_language(${FILE} LANG)
      if(NOT "${LANG}" STREQUAL "")
        list(APPEND SOURCES "${FILE}")
        set(TARGET_COMPILER ${CMAKE_${LANG}_COMPILER_ID})
      endif()
    endif()
  endforeach()

  # If no gcov binary was found, coverage data can't be evaluated.
  if(NOT GCOV_${TARGET_COMPILER}_EXE)
    message(
      WARNING "No coverage evaluation binary found for ${TARGET_COMPILER}.")
    return()
  endif()

  set(GCOV_EXE "${GCOV_${TARGET_COMPILER}_EXE}")
  set(BUFFER "")

  foreach(FILE ${SOURCES})
    get_filename_component(FILE_PATH "${TARGET_DIR}/${FILE}" PATH)

    # call gcov
    add_custom_command(
      OUTPUT ${TARGET_DIR}/${FILE}.gcov
      COMMAND ${GCOV_EXE} ${TARGET_DIR}/${FILE}.gcno > /dev/null
      DEPENDS ${TARGET_NAME} ${TARGET_DIR}/${FILE}.gcno
      WORKING_DIRECTORY ${FILE_PATH})

    list(APPEND BUFFER ${TARGET_DIR}/${FILE}.gcov)
  endforeach()

  # add target for gcov evaluation of <TARGET_NAME>
  add_custom_target(${TARGET_NAME}-gcov DEPENDS ${BUFFER})

  # add evaluation target to the global gcov target.
  add_dependencies(gcov ${TARGET_NAME}-gcov)
endfunction()
