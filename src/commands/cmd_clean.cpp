// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "cmd_clean.hpp"

void zephir::commands::SetupCleanCommand(const std::shared_ptr<CLI::App>& app,
                                         const std::string& group) {
  auto cmd = app->add_subcommand(
                    "clean", "Cleans any object files created by the extension")
                 ->group(group);

  // Add options to cmd, binding them to options.
  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  // TODO(klay): Make it better.
  // Right now I've set empty string to override parent footer
  cmd->footer("");

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([]() { ExecuteCleanCommand(); });
}

void zephir::commands::ExecuteCleanCommand() {
  // Do stuff...
  std::cout << "Fullclean command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
}
