// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <string>

#include <zephir/config/requires.hpp>

TEST(RequiresTest, EncodeClass) {
  std::vector<std::string> extensions = {"PDO", "SPL", "standard", "hash",
                                         "json"};
  auto requires = std::make_shared<zephir::config::Requires>(extensions);

  YAML::Node node;
  node["requires"] =
      YAML::convert<zephir::config::RequiresPtr>::encode(requires);

  EXPECT_TRUE(node.IsMap());
  EXPECT_EQ(extensions,
            node["requires"]["extensions"].as<std::vector<std::string>>());
}