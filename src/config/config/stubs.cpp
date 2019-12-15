// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <string>
#include <tuple>
#include <utility>

#include <zephir/config/stubs.hpp>

zephir::config::Stubs::Stubs()
    : path_("ide/%version%/%namespace%"), regenerate_(false), banner_("") {}

zephir::config::Stubs::Stubs(std::string path, bool regenerate,
                             std::string banner)
    : path_(std::move(path)),
      regenerate_(regenerate),
      banner_(std::move(banner)) {}

bool zephir::config::Stubs::operator==(const zephir::config::Stubs &rhs) const {
  auto lhs_key = std::tie(path_, regenerate_, banner_);
  auto rhs_key = std::tie(rhs.path_, rhs.regenerate_, rhs.banner_);

  return lhs_key == rhs_key;
}

zephir::config::Stubs &
zephir::config::Stubs::operator=(const zephir::config::Stubs &rhs) = default;
