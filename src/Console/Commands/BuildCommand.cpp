// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "BuildCommand.hpp"

#include <memory>
#include <string>
#include <utility>

zephir::console::commands::BuildCommand::BuildCommand(std::string name)
    : AbstractCommand(std::move(name)),
      options_(std::make_unique<BuildOptions>()) {}

void zephir::console::commands::BuildCommand::Setup(CLI::App_p app) {
  auto cmd = app->group(group_)->add_subcommand(
      "build", "Generates/Compiles/Installs a Zephir extension");

  options_->backend = "ZendEngine3";

  // Add options to cmd, binding them to options.
  cmd->add_option(
         "--backend", options_->backend,
         "Used backend to generate extension [default: \"ZendEngine3\"]")
      ->type_name("BACKEND");

  auto dev = cmd->add_flag(
      "--dev", "Compile the extension in development mode [default]");
  auto no_dev =
      cmd->add_flag("--no-dev", "Compile the extension in production mode");
  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  // TODO(klay): Check for PHP build mode if no_dev == false && dev == false
  options_->dev = no_dev->count() <= dev->count();

  const char* HELP = R"HELP(
  This is a meta command that just calls the generate, compile and install commands.

  Using --dev option will force compiling the extension in development mode
  (debug symbols and no optimizations). An extension compiled with debugging symbols means
  you can run a program or library through a debugger and the debugger's output will be user
  friendlier. These debugging symbols also enlarge the program or library significantly.

  NOTE: Zephir development mode will be enabled silently if your PHP binary was compiled in
  a debug configuration.

  In some cases, we would like to get production ready extension even if the PHP binary was
  compiled in a debug configuration. Use --no-dev option to achieve this behavior.)HELP";

  cmd->footer(std::string(HELP) + "\n" + CommonCompilationFlagsHelp());

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([&]() { Execute(); });
}

void zephir::console::commands::BuildCommand::Execute() {
  // Do stuff...
  std::cout << "Build command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
  std::cout << "    options.dev = " << options_->dev << std::endl;
  std::cout << "    options.backend = " << options_->backend << std::endl;
}
