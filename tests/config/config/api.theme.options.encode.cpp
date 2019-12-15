// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <zephir/config/api/theme/options.hpp>

namespace ztheme = zephir::config::api::theme;

TEST(ApiOptionsTest, EncodeClass) {
  std::map<std::string, std::string> container = {
      {"github", "https://github.com/phalcon"},
      {"analytics", "AABBCCDDFF"},
      {"main_color", "#3E6496"},
      {"link_color", "#3E6496"},
      {"link_hover_color", "#5F9AE7"},
  };

  auto warnings = std::make_shared<ztheme::Options>(container);
  auto node = YAML::convert<ztheme::OptionsPtr>::encode(warnings);

  EXPECT_TRUE(node.IsMap());

  EXPECT_EQ("https://github.com/phalcon", node["github"].as<std::string>());
  EXPECT_EQ("AABBCCDDFF", node["analytics"].as<std::string>());
  EXPECT_EQ("#3E6496", node["main_color"].as<std::string>());
  EXPECT_EQ("#3E6496", node["link_color"].as<std::string>());
  EXPECT_EQ("#5F9AE7", node["link_hover_color"].as<std::string>());
}
