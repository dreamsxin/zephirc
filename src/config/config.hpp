// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_HPP_
#define ZEPHIR_CONFIG_HPP_

#include <yaml-cpp/yaml.h>

#include <string>
#include <vector>

#include "ptr.hpp"

// TODO(klay): Add config sections:
// - constants-sources
// - destructors
// - extension-name
// - external-dependencies
// - extra-cflags
// - extra-classes
// - extra-libs
// - extra-sources
// - globals
// - info
// - initializers
// - optimizer-dirs
// - package-dependencies
// - prototype-dir
namespace zephir {
/**
 * @brief Manages compiler global configuration.
 */
class Config {
 public:
  /**
   * @brief Config constructor.
   */
  explicit Config(std::string path);

  /**
   * @brief Is config changed?
   *
   * @return true if default config is changed, false otherwise.
   */
  bool changed();

  bool loaded();

  /**
   * \brief factory method to create a Config instance from argv and config
   * file. Initialize configuration from both the CLI and a possible config
   * file.
   *
   * @param options Provided command line arguments
   * @param path The default name/location of the config file
   * @return A fresh Config instance with loaded configurations
   *
   * Items specified in the CLI take priority over any settings loaded from
   * config file. Configuration file, if not found from the provided parameter
   * or set specifically in the CLI, will also search through any search paths
   * provided from the CLI for the provided filename.
   */
  static ConfigPtr factory(std::vector<std::string> &options,
                           const std::string &path);

  bool operator==(const Config &rhs) const;
  Config &operator=(const Config &rhs);

  /// Getting a value by its key
  template <typename T>
  inline T get(const std::string &key, const T &fallback) const;

  /// Getting a value by its key and namespace
  template <class T>
  inline T get(const std::string &key, const std::string &ns,
               const T &fallback) const;

 private:
  YAML::Node container_;

  /**
   * \brief Populate config container_ from a file path_.
   */
  void populate();

  /**
   * @brief Used path to load project configuration.
   */
  std::string path_;

  /**
   * @brief Is project configuration was changed?
   */
  bool changed_;

  bool loaded_;
};
}  // namespace zephir

#include "impl.hpp"

#endif  // ZEPHIR_CONFIG_HPP_
