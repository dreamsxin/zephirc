// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_HPP_
#define ZEPHIR_CONFIG_HPP_

#include <memory>
#include <string>
#include <vector>

#include "config/api.hpp"
#include "config/extra.hpp"
#include "config/optimizations.hpp"
#include "config/requires.hpp"
#include "config/stubs.hpp"
#include "config/warnings.hpp"
#include "yaml/config.hpp"

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
  Config();

  /**
   * @brief Load configuration from a file path.
   *
   * @param path The path to the configuration file.
   * @return A shared pointer to the zephir::Config
   */
  static zephir::ConfigPtr Load(const std::string &path);

  /**
   * @brief Is config changed?
   *
   * @return true if default config is changed, false otherwise.
   */
  bool IsChanged();

  /**
   * @brief Factory method to create a Config instance from argv and config
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
  static ConfigPtr Factory(std::vector<std::string> &options,
                           const std::string &path);

  /**
   * @brief Encode Config object to a Yaml Node.
   *
   * @param cptr The smart pointer to a Config instance
   * @return Yaml Node
   */
  friend YAML::Node
  YAML::convert<ConfigPtr>::encode(const zephir::ConfigPtr &cptr);

  /**
   * @brief Decode Yaml Node to a Config object.
   *
   * @param node The Yaml Node
   * @param cptr The smart pointer to a Config instance
   * @return true on success, false otherwise
   */
  friend bool YAML::convert<ConfigPtr>::decode(const YAML::Node &node,
                                               zephir::ConfigPtr &cptr);

  bool operator==(const Config &rhs) const;
  Config &operator=(const Config &rhs);

  void SetWarning(const std::string &key, const bool &value);

 private:
  /**
   * @brief The namespace of the extension.
   */
  std::string ns_;

  /**
   * @brief Extension name used in compiled C code.
   */
  std::string name_;

  /**
   * @brief Extension description.
   */
  std::string description_;

  /**
   * @brief Company, developer, institution, etc that developed the extension.
   */
  std::string author_;

  /**
   * @brief Extension version.
   */
  std::string version_;

  /**
   * @brief Provides a way to configure the Zend Engine backend used by your
   * extension.
   */
  std::string backend_;

  /**
   * @brief Displays more detail in error messages from exceptions generated by
   * zephir commands (same as --verbose).
   */
  bool verbose_;

  /**
   * @brief Suppresses most/all output from zephir commands
   * (same as -w, -q or --quiet).
   * @TODO(klay): add support for "-w"
   */
  bool silent_;

  /**
   * @brief Used path to load project configuration.
   */
  std::string path_;

  /**
   * @brief Is project configuration was changed?
   */
  bool changed_;

  /**
   * @brief Allows you to list other extensions as required to build/use your
   * own.
   */
  config::Requires requires_;

  /**
   * @brief Allows adjusting the way IDE documentation stubs are generated.
   */
  config::Stubs stubs_;

  /**
   * @brief Used to configure the automatically generated HTML documentation for
   * your extension.
   */
  config::Api api_;

  /**
   * @brief Compiler warnings which should be enabled or disabled in the current
   * project.
   */
  config::Warnings warnings_;
  /**
   * @brief Compiler optimizations which should be enabled or disabled in the
   * current project.
   */
  config::Optimizations optimizations_;

  /**
   * @brief Contains extra settings that also can be passed, as is, on the
   * command line.
   */
  zephir::config::Extra extra_;
};
}  // namespace zephir

#endif  // ZEPHIR_CONFIG_HPP_