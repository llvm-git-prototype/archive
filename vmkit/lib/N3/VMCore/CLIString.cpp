//===---- CLIString.cpp - Internal correspondance with CLI Strings --------===//
//
//                                N3
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "CLIString.h"
#include "N3.h"
#include "VMArray.h"
#include "VMClass.h"
#include "VMThread.h"

using namespace n3;


CLIString* CLIString::stringDup(const UTF8*& utf8, N3* vm) {
  CLIString* obj = (CLIString*)(*N3::pString)();
  obj->capacity = utf8->size;
  obj->length = utf8->size;
  if (utf8->size == 0) {
    obj->firstChar = 0;
  } else {
    obj->firstChar = utf8->at(0);
  }
  obj->value = utf8; 
  return obj;
}

char* CLIString::strToAsciiz() {
  return value->UTF8ToAsciiz();
}

const UTF8* CLIString::strToUTF8(N3* vm) {
  return value;
}
