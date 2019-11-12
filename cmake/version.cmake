# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

file(STRINGS "${CMAKE_SOURCE_DIR}/include/zephir/version.hpp" zephir_version
     REGEX "#define ZEPHIR_VERSION_(MAJOR|MINOR|PATCH)")

foreach(part ${zephir_version})
  if(part MATCHES "#define ZEPHIR_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
    set(ZEPHIR_VERSION_${CMAKE_MATCH_1}
        "${CMAKE_MATCH_2}"
        CACHE INTERNAL "")
  endif()
endforeach()

set(VERSION
    ${ZEPHIR_VERSION_MAJOR}.${ZEPHIR_VERSION_MINOR}.${ZEPHIR_VERSION_PATCH})

# version.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
