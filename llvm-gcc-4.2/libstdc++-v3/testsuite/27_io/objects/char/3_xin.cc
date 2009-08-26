// 2000-08-02 bkoz

// Copyright (C) 2000, 2001, 2002 Free Software Foundation, Inc.
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

#include <iostream>

// Interactive test, to be exercised as follows:
// run test under truss(1) or strace(1).  Look at
// size and pattern of write system calls.
// Should be 2 or 3 write(1,[...]) calls when run interactively
// depending upon buffering mode enforced.
void test05()
{
  std::cout << "hello" << ' ' << "world" << std::endl;
  std::cout << "Enter your name: ";
  std::string s;
  std::cin >> s;
  std::cout << "hello " << s << std::endl;
}

int 
main()
{
  test05();
  return 0;
}
