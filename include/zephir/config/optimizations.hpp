// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_OPTIMIZATIONS_HPP_
#define ZEPHIR_CONFIG_OPTIMIZATIONS_HPP_

#include <map>
#include <string>

#include <zephir/config/yaml/optimizations.hpp>

namespace zephir::config {
class Optimizations {
 public:
  Optimizations();
  explicit Optimizations(std::map<std::string, bool> container);

  friend YAML::Node YAML::convert<OptimizationsPtr>::encode(
      const zephir::config::OptimizationsPtr &optr);
  friend bool YAML::convert<OptimizationsPtr>::decode(
      const YAML::Node &node, zephir::config::OptimizationsPtr &optr);

  bool operator==(const Optimizations &rhs) const;
  Optimizations &operator=(const Optimizations &rhs);

 private:
  std::map<std::string, bool> container_;
};
}  // namespace zephir::config

#endif  // ZEPHIR_CONFIG_OPTIMIZATIONS_HPP_