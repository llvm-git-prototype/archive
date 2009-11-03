// 2002-04-13  Paolo Carlini  <pcarlini@unitus.it>

// Copyright (C) 2002, 2004, 2005 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.

// 20.2.1 Operators

#include <utility>
#include <vector>

using namespace std::rel_ops;

// libstdc++/3628
void test01()
{
  std::vector<int> v;
  std::vector<int>::iterator vi;
  v.push_back(1);
  vi = v.end();
  vi != v.begin();
  vi > v.begin();
  vi <= v.begin();
  vi >= v.begin();
}

int main()
{
  test01();
  return 0;
}

