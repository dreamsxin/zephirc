// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_YAML_CONFIG_HPP_
#define ZEPHIR_YAML_CONFIG_HPP_

#include <yaml-cpp/yaml.h>

#include <zephir/ptr/config.hpp>

namespace YAML {
template <>
struct convert<zephir::ConfigPtr> {
  static Node encode(const zephir::ConfigPtr &cptr);
  static bool decode(const Node &node, zephir::ConfigPtr &cptr);
};
}  // namespace YAML

#endif  // ZEPHIR_YAML_CONFIG_HPP_
