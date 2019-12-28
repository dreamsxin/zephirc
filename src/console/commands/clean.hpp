// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file clean.hpp
/// \brief Provides CleanCommand.

#ifndef ZEPHIR_CLI_COMMANDS_CLEAN_HPP_
#define ZEPHIR_CLI_COMMANDS_CLEAN_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Cleans any object files created by the extension.
class CleanCommand : public AbstractCommand {
 public:
  /// \brief Construct CleanCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit CleanCommand(std::string name);

  /// \brief Configures the CleanCommand command.
  ///
  /// \param app A `CLI::App` instance
  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes CleanCommand command.
  void Execute() override;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_CLEAN_HPP_
