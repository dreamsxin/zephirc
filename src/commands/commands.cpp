// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "commands.hpp"
#include "cmd_generate.hpp"

#include <CLI/CLI11.hpp>
#include <memory>
#include <string>

#include "formatter.hpp"
#include "zephir/main.hpp"
#include "zephir/version.hpp"

int zephir::commands::ParseOptions(int argc, char** argv) {
  const char* BANNER = R"BANNER( _____              __    _
/__  /  ___  ____  / /_  (_)____
  / /  / _ \/ __ \/ __ \/ / ___/
 / /__/  __/ /_/ / / / / / /
/____/\___/ .___/_/ /_/_/_/
         /_/)BANNER";

  CLI::App app("zephir");
  app.description("Zephir " + std::string(ZEPHIR_VERSION_STRING) + "\n");

  auto fmt = std::make_shared<Formatter>();
  fmt->column_width(17);
  app.formatter(fmt);

  // Global options
  app.add_flag("--dumpversion",
               "Print the version of the compiler and don't do anything else "
               "(also works with a single hyphen)");

  app.set_help_flag();
  auto help = app.add_flag("-h, --help", "Print this help message and quit");

  app.add_flag("--vernum",
               "Print the version of the compiler as integer and quit");
  app.add_flag("-V, --version", "Print compiler version information and quit");

  // Commands
  auto main_group = "Available commands";
  app.add_subcommand(
         "api",
         "Generates a HTML API based on the classes exposed in the extension")
      ->group(main_group);
  app.add_subcommand("build", "Generates/Compiles/Installs a Zephir extension")
      ->group(main_group);
  app.add_subcommand("clean",
                     "Cleans any object files created by the extension")
      ->group(main_group);
  app.add_subcommand("compile", "Compile a Zephir extension")
      ->group(main_group);
  app.add_subcommand("fullclean",
                     "Cleans any object files created by the extension "
                     "(including files generated by phpize)")
      ->group(main_group);

  zephir::commands::GenerateCommand generate(app, main_group);

  app.add_subcommand("help", "Displays help for a command")->group(main_group);
  app.add_subcommand("init", "Initializes a Zephir extension")
      ->group(main_group);
  app.add_subcommand("install",
                     "Installs the extension in the extension directory (may "
                     "require root password)")
      ->group(main_group);
  app.add_subcommand("stubs", "Generates stubs that can be used in a PHP IDE")
      ->group(main_group);

  try {
    app.parse(argc, argv);

    if (*help) {
      std::cout << BANNER << std::endl << std::endl;
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
