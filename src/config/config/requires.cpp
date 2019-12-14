// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <utility>

#include <zephir/config/requires.hpp>

zephir::config::Requires::Requires() : extensions_{} {}

zephir::config::Requires::Requires(std::vector<std::string> extensions)
    : extensions_(std::move(extensions)) {}

bool zephir::config::Requires::operator==(
    const zephir::config::Requires &rhs) const {
  auto lhs_key = std::tie(extensions_);
  auto rhs_key = std::tie(rhs.extensions_);

  return lhs_key == rhs_key;
}

zephir::config::Requires &zephir::config::Requires::operator=(
    const zephir::config::Requires &rhs) = default;