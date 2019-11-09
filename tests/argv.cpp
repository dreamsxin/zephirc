// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "argv.hpp"

#include <cstring>
#include <initializer_list>
#include <utility>

Argv::Argv(std::initializer_list<const char *> args)
    : m_argv(new char *[args.size()]), m_argc(args.size()) {
  int i = 0;
  auto iter = args.begin();
  while (iter != args.end()) {
    auto len = std::strlen(*iter) + 1;
    auto ptr = std::unique_ptr<char[]>(new char[len]);

    std::strncpy(ptr.get(), *iter, len);
    m_args.push_back(std::move(ptr));
    m_argv.get()[i] = m_args.back().get();

    ++iter;
    ++i;
  }
}

char **Argv::argv() const { return m_argv.get(); }

int Argv::argc() const { return m_argc; }