// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "application.hpp"

#include <utility>

#include <zephir/version.hpp>

#include "../filesystem/filesystem.hpp"

zephir::console::Application::Application(zephir::ConfigPtr config,
                                          std::vector<std::string> args,
                                          const std::string& base_path)
    : args_(std::move(args)),
      base_path_(base_path),
      config_(std::move(config)),
      formatter_(std::make_shared<zephir::console::Formatter>()),
      app_(std::make_shared<CLI::App>()),
      help_(nullptr),
      commands_() {
  auto out =
      std::string(ZEPHIR_PACKAGE_NAME) + " " + std::string(ZEPHIR_VERSION);

  app_->description(out);
  app_->name("zephir");

  out = "See \"" + app_->get_name() + " <command> --help\"";
  out += " to read about a specific command or concept.";

  app_->footer(out);

  formatter_->column_width(17);
  formatter_->label("OPTIONS", "options");
  formatter_->label("ARGUMENTS", "arguments");
  formatter_->label("COMMAND", "command");
  formatter_->label("Positionals", "Arguments");

  app_->formatter(formatter_);

  // Global options

  app_->add_flag(
      "--dumpversion",
      [](std::size_t /* not used */) {
        std::cout << ZEPHIR_VERSION << std::endl;
      },
      "Print the version of the compiler and don't do anything else "
      "(also works with a single hyphen)");

  app_->add_flag(
      "--vernum",
      [](std::size_t /* not used */) {
        std::cout << ZEPHIR_VERSION_ID << std::endl;
      },
      "Print the version of the compiler as integer and quit");

  app_->add_flag(
      "-V, --version",
      [&](std::size_t /* not used */) {
        std::cout << ZEPHIR_VERSION_FULL
                  << " (built: " << ZEPHIR_PACKAGE_BUILD_DATE << ") "
                  << std::endl;
        std::cout << "Copyright " << ZEPHIR_COPYRIGHT << std::endl;
        std::cout << "This is free software; see the source for copying "
                     "conditions.  There is NO"
                  << std::endl;
        std::cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
                     "PARTICULAR PURPOSE."
                  << std::endl
                  << std::endl;
      },
      "Print compiler version information and quit");

  // Remove help flag because it shortcuts all processing
  app_->set_help_flag();

  // Add custom flag that activates help
  help_ = app_->add_flag("-h, --help", "Print this help message and quit");
};

void zephir::console::Application::AddCommand(
    zephir::console::commands::CommandPtr command) {
  if (command) {
    commands_.push_back(std::move(command));
  }
}

int zephir::console::Application::Run() {
  for (const auto& cmd : commands_) {
    cmd->Setup(app_);
  }

  try {
    app_->parse(args_);

    if (*help_) {
      throw CLI::CallForHelp();
    }
  } catch (const CLI::Error& e) {
    auto retval = app_->exit(e);

    // TODO(klay): print error message
    return retval;
  }

  return EXIT_SUCCESS;
}
