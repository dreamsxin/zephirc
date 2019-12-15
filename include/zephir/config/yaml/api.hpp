// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_API_HPP_
#define ZEPHIR_CONFIG_YAML_API_HPP_

#include <yaml-cpp/yaml.h>

#include <zephir/config/ptr/api.hpp>

namespace YAML {
template <>
struct convert<zephir::config::ApiPtr> {
  /**
   * @brief Encode Api object to the Yaml Node.
   *
   * @param aptr Api smart pointer
   * @return Yaml Node
   */
  static Node encode(const zephir::config::ApiPtr &aptr);

  /**
   * @brief Decode Yaml Node to the Api object.
   *
   * @param node Yaml Node
   * @param aptr Api smart pointer
   * @return true on success, false otherwise
   */
  static bool decode(const Node &node, zephir::config::ApiPtr &aptr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_API_HPP_
