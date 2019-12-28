// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_FULLCLEAN_HPP_
#define ZEPHIR_CLI_COMMANDS_FULLCLEAN_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Cleans any object files created by the extension (including files
/// generated by phpize).
class FullCleanCommand : public AbstractCommand {
 public:
  /// \brief Construct FullCleanCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit FullCleanCommand(std::string name);

  /// \brief Configures the FullCleanCommand command.
  ///
  /// \param app A `CLI::App` instance
  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes FullCleanCommand command.
  void Execute() override;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_FULLCLEAN_HPP_
