// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <memory>

#include "Console/Application.hpp"
#include "Console/Commands/InstallCommand.hpp"

using namespace zephir::console::commands;

class InstallCommandTest : public ::testing::Test {
 protected:
  InstallCommandTest() : argv(){};
  std::vector<std::string> argv;
};

TEST_F(InstallCommandTest, RunWithoutOptions) {
  argv.assign({"install"});
  auto config = std::make_shared<zephir::Config>("foo");
  auto app = std::make_unique<zephir::console::Application>(config, argv);
  app->AddCommand(std::make_unique<InstallCommand>("install"));

  auto retval = app->Run();
  EXPECT_EQ(retval, 0);
}
