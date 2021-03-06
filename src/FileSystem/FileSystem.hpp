// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file FileSystem.hpp
/// \brief Represents filesystem helpers to use internally in the Zephir
/// compiler.

#ifndef ZEPHIR_FILESYSTEM_HPP_
#define ZEPHIR_FILESYSTEM_HPP_

#include <string>

namespace zephir::filesystem {
/// \brief Fastest way to check if a file exist.
///
/// \param name The location of the file
/// \return True if file exists, false otherwise.
bool exists(const std::string& name) noexcept;

/// \brief Get the current path.
///
/// \return The current working path.
std::string current_path();
}  // namespace zephir::filesystem

#endif  // ZEPHIR_FILESYSTEM_HPP_
