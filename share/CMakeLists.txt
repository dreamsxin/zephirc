# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

set(shareDirectories kernels templates)

add_custom_target(
  copy_share_to_builddir ALL
  COMMENT "Copy files into build directory"
  VERBATIM)

foreach(dir IN ITEMS ${shareDirectories})
  add_custom_command(
    TARGET copy_share_to_builddir
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${dir}"
            "${ZEPHIR_OUTPUT_DIR}/${ZEPHIR_DATA_DIR}/${dir}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Copy files into build directory: ${dir}"
    VERBATIM)
endforeach()

install(DIRECTORY ${shareDirectories} DESTINATION "${ZEPHIR_DATA_DIR}")
