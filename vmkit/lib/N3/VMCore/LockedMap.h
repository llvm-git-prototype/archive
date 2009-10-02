//===------- LockedMap.h - A thread-safe map implementation ---------------===//
//
//                               N3
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef N3_LOCKED_MAP_H
#define N3_LOCKED_MAP_H

#include <map>


#include <string.h>

#include "mvm/Object.h"
#include "mvm/PrintBuffer.h"
#include "mvm/Threads/Locks.h"

#include "types.h"

#include "CLIString.h"
#include "VMArray.h"

namespace n3 {

class Assembly;
class N3;
class VMClass;
class VMCommonClass;
class VMField;
class VMObject;
class VMMethod;
class VMField;
class UTF8;

template<class Key, class Container, class Compare, class Upcall>
class LockedMap : public mvm::PermanentObject {
public:
  typedef typename std::map<const Key, Container*, Compare>::iterator iterator;
  typedef Container* (*funcCreate)(Key& V, Upcall* ass);

  mvm::Lock* lock;
  std::map<Key, Container*, Compare,
           gc_allocator<std::pair<const Key, Container*> > > map;
  
  inline Container* lookupOrCreate(Key& V, Upcall* ass, funcCreate func) {
    lock->lock();
    iterator End = map.end();
    iterator I = map.find(V);
    if (I == End) {
      Container* res = func(V, ass);
      map.insert(std::make_pair(V, res));
      lock->unlock();
      return res;
    } else {
      lock->unlock();
      return ((Container*)(I->second));
    }
  }
  
  inline Container* lookupOrCreate(Key&V, Container* C) {
    lock->lock();
    iterator End = map.end();
    iterator I = map.find(V);
    if (I == End) {
      map.insert(std::make_pair(V, C));
      lock->unlock();
      return C;
    } else {
      lock->unlock();
      return ((Container*)(I->second));
    }
  }

  inline Container* lookup(Key& V) {
    lock->lock();
    iterator End = map.end();
    iterator I = map.find(V);
    lock->unlock();
    return I != End ? ((Container*)(I->second)) : 0; 
  }

  inline void hash(Key& k, Container* c) {
    lock->lock();
    map.insert(std::make_pair(k, c));
    lock->unlock();
  }

  virtual void TRACER {
    //lock->MARK_AND_TRACE;
    for (iterator i = map.begin(), e = map.end(); i!= e; ++i) {
      i->second->CALL_TRACER;
    }
  }

  virtual void print(mvm::PrintBuffer* buf) const {
    buf->write("Hashtable<>");
  }

};

class ClassNameCmp {
public:
  const UTF8* name;
  const UTF8* nameSpace;

  ClassNameCmp(const UTF8* u, const UTF8* n) : name(u), nameSpace(n) {}

  inline bool operator<(const ClassNameCmp &cmp) const {
    if (name < cmp.name) return true;
    else if (name > cmp.name) return false;
    else return nameSpace < cmp.nameSpace;
  }
};


class ClassNameMap : 
  public LockedMap<ClassNameCmp, VMCommonClass, std::less<ClassNameCmp>, Assembly > {
public:
  static ClassNameMap* allocate(mvm::BumpPtrAllocator &allocator) {
    ClassNameMap* map = new(allocator, "ClassNameMap") ClassNameMap();
    map->lock = new mvm::LockNormal();
    return map;
  }
};

class ClassTokenMap : 
  public LockedMap<uint32, VMCommonClass, std::less<uint32>, Assembly > {
public:
  static ClassTokenMap* allocate(mvm::BumpPtrAllocator &allocator) {
    ClassTokenMap* map = new(allocator, "ClassTokenMap") ClassTokenMap();
    map->lock = new mvm::LockNormal();
    return map;
  }
  
};

class FieldTokenMap : 
  public LockedMap<uint32, VMField, std::less<uint32>, Assembly > {
public:
  static FieldTokenMap* allocate(mvm::BumpPtrAllocator &allocator) {
    FieldTokenMap* map = new(allocator, "FieldTokenMap") FieldTokenMap();
    map->lock = new mvm::LockNormal();
    return map;
  }
};

class MethodTokenMap : 
  public LockedMap<uint32, VMMethod, std::less<uint32>, Assembly > {
public:
  static MethodTokenMap* allocate(mvm::BumpPtrAllocator &allocator) {
    MethodTokenMap* map = new(allocator, "MethodTokenMap") MethodTokenMap();
    map->lock = new mvm::LockNormal();
    return map;
  }
};

class AssemblyMap : 
  public LockedMap<const UTF8*, Assembly, std::less<const UTF8*>, N3 > {
public:
  static AssemblyMap* allocate(mvm::BumpPtrAllocator &allocator) {
    AssemblyMap* map = new(allocator, "AssemblyMap") AssemblyMap();
    map->lock = new mvm::LockNormal();
    return map;
  }
};


class StringMap :
    public LockedMap<const UTF8*, CLIString, std::less<const UTF8*>, N3 > { 
public:
  static StringMap* allocate(mvm::BumpPtrAllocator &allocator) {
    StringMap* map = new(allocator, "StringMap") StringMap();
    map->lock = new mvm::LockRecursive();
    return map;
  }
};

class FunctionMap :
    public LockedMap<llvm::Function*, VMMethod, std::less<llvm::Function*>, N3 > { 
public:
  static FunctionMap* allocate(mvm::BumpPtrAllocator &allocator) {
    FunctionMap* map = new(allocator, "FunctionMap") FunctionMap();
    map->lock = new mvm::LockNormal();
    return map;
  }
};



class UTF8Map : public mvm::PermanentObject {
public:
  typedef std::multimap<const uint32, const UTF8*>::iterator iterator;
  
  mvm::Lock* lock;
  std::multimap<uint32, const UTF8*, std::less<uint32>,
                gc_allocator<std::pair<const uint32, const UTF8*> > > map;

  const UTF8* lookupOrCreateAsciiz(const char* asciiz); 
  const UTF8* lookupOrCreateReader(const uint16* buf, uint32 size);
  
  virtual void TRACER {
    //lock->MARK_AND_TRACE;
    for (iterator i = map.begin(), e = map.end(); i!= e; ++i) {
      i->second->MARK_AND_TRACE;
    }
  }

  virtual void print(mvm::PrintBuffer* buf) const {
    buf->write("UTF8 Hashtable<>");
  }
  
  static UTF8Map* allocate(mvm::BumpPtrAllocator &allocator) {
    UTF8Map* map = new(allocator, "UTF8Map") UTF8Map();
    map->lock = new mvm::LockNormal();
    return map;
  }


};

} // end namespace n3

#endif
