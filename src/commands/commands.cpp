// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "commands.hpp"

#include <memory>
#include <string>

#include <CLI/CLI11.hpp>

#include "cmd_api.hpp"
#include "cmd_build.hpp"
#include "cmd_clean.hpp"
#include "cmd_compile.hpp"
#include "cmd_fullclean.hpp"
#include "cmd_generate.hpp"
#include "cmd_init.hpp"
#include "cmd_install.hpp"
#include "cmd_stubs.hpp"
#include "formatter.hpp"
#include "zephir/config.hpp"
#include "zephir/filesystem.hpp"
#include "zephir/main.hpp"
#include "zephir/version.hpp"

int zephir::commands::CreateFromArgv(std::vector<std::string>& options) {
  auto cwd = zephir::filesystem::GetCurrentWorkingPath();
  auto config = zephir::Config::CreateFromArgv(options, cwd + "/.zephir.yml");

  std::string out = "Zephir " + std::string(ZEPHIR_VERSION_STRING);
  out += " by Serghei Iakovlev and Alexander Andriiako";

  CLI::App app(out, "zephir");

  out = "See \"" + app.get_name() + " <command> --help\"";
  out += " to read about a specific command or concept.";

  app.footer(out);

  auto fmt = std::make_shared<Formatter>();

  fmt->column_width(17);
  fmt->label("OPTIONS", "options");
  fmt->label("ARGUMENTS", "arguments");
  fmt->label("COMMAND", "command");
  fmt->label("Positionals", "Arguments");

  app.formatter(fmt);

  // Global options
  app.add_flag("--dumpversion",
               "Print the version of the compiler and don't do anything else "
               "(also works with a single hyphen)");

  auto help =
      app.set_help_flag("-h, --help", "Print this help message and quit");

  app.add_flag("--vernum",
               "Print the version of the compiler as integer and quit");
  app.add_flag("-V, --version", "Print compiler version information and quit");

  // Commands
  const auto commands_group = "Available commands";

  zephir::commands::SetupApiCommand(app, commands_group);
  zephir::commands::SetupBuildCommand(app, commands_group);
  zephir::commands::SetupCleanCommand(app, commands_group);
  zephir::commands::SetupCompileCommand(app, commands_group);
  zephir::commands::SetupFullcleanCommand(app, commands_group);
  zephir::commands::SetupGenerateCommand(app, commands_group);
  zephir::commands::SetupInitCommand(app, commands_group);
  zephir::commands::SetupInstallCommand(app, commands_group);
  zephir::commands::SetupStubsCommand(app, commands_group);

  try {
    app.parse(options);

    if (*help) {
      throw CLI::CallForHelp();
    }
  } catch (const CLI::ParseError& e) {
    int retval = app.exit(e);
    if (e.get_name() == "CallForHelp") {
      retval = EXIT_HELP;
    }

    // TODO(klay): print error message
    return retval;
  }

  return 0;
}

std::string zephir::commands::CommonCompilationFlagsHelp() {
  const char* FLAGS = R"FLAGS(
  Common flags are:
      -f([a-z0-9\-]+)    Enables compiler optimizations
      -fno-([a-z0-9\-]+) Disables compiler optimizations
      -w([a-z0-9\-]+)    Turns a warning on
      -W([a-z0-9\-]+)    Turns a warning off)FLAGS";

  return std::string(FLAGS);
}
