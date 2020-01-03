// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file impl.hpp
/// \brief Provides implementation of Config's template functions.

#ifndef ZEPHIR_CONFIG_IMPL_HPP_
#define ZEPHIR_CONFIG_IMPL_HPP_

#include <string>

namespace zephir {
/// \brief Fetch a configuration value using a simple key.
///
/// \tparam T Requested return type.
/// \param key Which config item to look up.
/// \param fallback  Fallback default value to use when configuration object
/// has no value.
///
/// \return Requested configuration setting if any,
/// fallback otherwise
template <typename T>
inline T Config::get(const std::string &key, const T &fallback) const {
  return container_[key].as<T, T>(fallback);
}

/// \brief Fetch a configuration value using a simple key.
///
/// \tparam T Requested return type.
/// \param key Which config item to look up.
/// \param ns Used configuration namespace to retrieve value.
/// \param fallback  Fallback default value to use when configuration object
/// has no value.
///
/// \return Requested configuration setting if any,
/// fallback otherwise
template <typename T>
inline T zephir::Config::get(const std::string &key, const std::string &ns,
                             const T &fallback) const {
  if (container_[ns].IsDefined()) {
    return container_[ns][key].as<T, T>(fallback);
  }

  return fallback;
}

/// \brief Set a configuration value, using simple key.
///
/// \tparam T Used type for new value.
/// \param key This configuration key will be set.
/// \param rhs This value will be set for the given configuration key.
/// \return Returns Config instance
template <typename T>
inline zephir::Config &zephir::Config::set(const std::string &key,
                                           const T &rhs) {
  if (!key.empty()) {
    container_[key] = rhs;
  }

  return *this;
}

/// \brief Set a configuration value, using simple key and the given namespace.
///
/// \tparam T Used type for new value.
/// \param key This configuration key will be set.
/// \param ns This configuration namespace will be used.
/// \param rhs This value will be set for the given configuration key.
/// \return Returns Config instance
template <typename T>
inline zephir::Config &zephir::Config::set(const std::string &key,
                                           const std::string &ns,
                                           const T &rhs) {
  if (!ns.empty() && !key.empty()) {
    container_[ns][key] = rhs;
  }

  return *this;
}
}  // namespace zephir
#endif  // ZEPHIR_CONFIG_IMPL_HPP_