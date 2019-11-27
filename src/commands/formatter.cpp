// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "formatter.hpp"

#include <CLI/CLI11.hpp>
#include <vector>

zephir::commands::Formatter::Formatter() = default;

std::string zephir::commands::Formatter::make_usage(
    const CLI::App *app, __attribute__((unused)) const std::string name) const {
  std::stringstream out;

  out << get_label("Usage") << ":\n";

  if (app->get_parent()) {
    out << "  " << app->get_name();
  } else {
    out << "  command";
  }

  std::vector<std::string> groups = app->get_groups();

  // Print an Options badge if any options exist
  std::vector<const CLI::Option *> non_pos_options = app->get_options(
      [](const CLI::Option *opt) { return opt->nonpositional(); });

  if (!non_pos_options.empty()) {
    out << " [" << get_label("options") << "]";
  }

  out << " [arguments]";
  out << std::endl;

  return out.str();
}

std::string zephir::commands::Formatter::make_description(
    const CLI::App *app) const {
  const char *BANNER = R"BANNER(
 _____              __    _
/__  /  ___  ____  / /_  (_)____
  / /  / _ \/ __ \/ __ \/ / ___/
 / /__/  __/ /_/ / / / / / /
/____/\___/ .___/_/ /_/_/_/
         /_/)BANNER";

  std::stringstream out;
  out << "";

  if (!app->get_parent()) {
    std::string banner(BANNER);
    out << banner.replace(0, 1, "") << std::endl << std::endl;
  }

  return out.str();
}
