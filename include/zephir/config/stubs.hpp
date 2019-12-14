// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_STUBS_HPP_
#define ZEPHIR_CONFIG_STUBS_HPP_

#include <string>

#include <zephir/config/yaml/stubs.hpp>

namespace zephir::config {
class Stubs {
 public:
  Stubs();
  explicit Stubs(std::string path, bool regenerate, std::string banner);

  friend YAML::Node
  YAML::convert<StubsPtr>::encode(const zephir::config::StubsPtr &sptr);
  friend bool YAML::convert<StubsPtr>::decode(const YAML::Node &node,
                                              zephir::config::StubsPtr &sptr);

  bool operator==(const Stubs &rhs) const;
  Stubs &operator=(const Stubs &rhs);

 private:
  std::string path_;
  bool regenerate_;
  std::string banner_;
};
}  // namespace zephir::config
#endif  // ZEPHIR_CONFIG_STUBS_HPP_