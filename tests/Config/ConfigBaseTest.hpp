// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_TESTS_CONFIG_CONFIG_BASE_TEST_HPP_
#define ZEPHIR_TESTS_CONFIG_CONFIG_BASE_TEST_HPP_

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "FileSystem/FileSystem.hpp"

using input_t = std::vector<std::string>;

class ConfigBaseTest : public ::testing::Test {
 protected:
  ConfigBaseTest() : argv() {}
  void TearDown() override {
    if (zephir::filesystem::exists("fake")) {
      remove("fake");
    }
  }
  input_t argv;
};

#endif  // ZEPHIR_TESTS_CONFIG_CONFIG_BASE_TEST_HPP_
