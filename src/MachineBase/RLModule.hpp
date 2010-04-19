// -*- Mode: C++; tab-width:2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi:tw=80:et:ts=2:sts=2
//
// -----------------------------------------------------------------------
//
// This file is part of RLVM, a RealLive virtual machine clone.
//
// -----------------------------------------------------------------------
//
// Copyright (C) 2006 Elliot Glaysher
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------------

#ifndef SRC_MACHINEBASE_RLMODULE_HPP_
#define SRC_MACHINEBASE_RLMODULE_HPP_

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

#include <map>
#include <vector>
#include <string>

namespace libReallive {
class FunctionElement;
class CommandElement;
};

struct RLOperation;
class RLMachine;

// Modules and Opcode Definitions
//
// Contains definitions for each operation that RLVM executes based
// off of an instruction in the SEEN.TXT file.
//
// Each opcode/overload that RLVM recognizes has a concrete instance
// of RLOperation represented with it's opcode number. There are a set
// of GeneralOperations that take parameters and are used as function
// binders to call various functions, but most opcodes are defined by
// having a concrete subclass of RLOp_Store<> or RLOp_Void<>.
//
// Subclasses of RLModule are used to contain subclasses of
// RLOperation; Each module should have a class derived from RLModule,
// where, in the constructor, the modules two identification numbers
// (@c module_type and @c module_number) are passed up to RLModule's
// constructor. The subclass constructor should then call
// RLModule::add_opcode for each opcode/overload pair with the
// RLOperation object that implements that operation.
//
// Example:
// @code
// FakeModule::FakeModule()
//   : RLModule("Fake", 0, 0)
// {
//   addOpcode(0, 0, new Fake_fake_operation_0);
//   addOpcode(0, 1, new Fake_fake_operation_1);
// }
// @endcode
//
// An instance of this module can now be passed to
// RLMachine::attach_module to expose these opcodes to an instance of RLMachine:
//
// @code
// RLMachine machine(some_archive_object);
// machine.attachModule(new FakeModule);
// @endcode
//
// For information on how to write an RLOperation subclass, see the
// documentation on @ref RLOperationGroup "RLOperation and it's type system"

// Describes a Module, a grouping of functions. Modules are added to
// an RLMachine before the machine starts.
class RLModule : public boost::noncopyable {
 public:
  // Storage type of the opcodes. Exposed so TestMachine can iterate over this.
  typedef boost::ptr_map<int, RLOperation> OpcodeMap;

 public:
  virtual ~RLModule();

  // Used in derived Module constructors to declare all the
  // operations the module handles. Takes ownership |op|.
  virtual void addOpcode(int opcode, unsigned char overload, const char* name,
                         RLOperation* op);

  // Adds an UndefinedFunction object to this module.
  void addUnsupportedOpcode(int opcode, unsigned char overload,
                            const std::string& name);

  // Accessor that returns this module's type number
  int moduleType() const { return module_type_; }

  // Accessor that returns this modules's identification number
  int moduleNumber() const { return module_number_; }

  // Accessor that returns this module's mnemonic nmae
  const std::string& moduleName() const { return module_name_; }

  void setProperty(int property, int value);
  bool getProperty(int property, int& value) const;

  // Using the bytecode element CommandElement f, try to find an
  // RLOperation implementation of the instruction in this module, and
  // execute it.
  void dispatchFunction(RLMachine& machine,
                        const libReallive::CommandElement& f);

  OpcodeMap::iterator begin() { return stored_operations.begin(); }
  OpcodeMap::iterator end() { return stored_operations.end(); }

  static int packOpcodeNumber(int opcode, unsigned char overload);
  static void unpackOpcodeNumber(int packed_opcode, int& opcode,
                                 unsigned char& overload);

 protected:
  RLModule(const std::string& in_module_name, int in_module_type,
           int in_module_number);

 private:
  typedef std::pair<int, int> Property;
  typedef std::vector<Property> PropertyList;

  PropertyList::iterator findProperty(int property) const;

  PropertyList* property_list_;

  int module_type_;
  int module_number_;
  std::string module_name_;

  // Store functions.
  OpcodeMap stored_operations;
};

std::ostream& operator<<(std::ostream&, const RLModule& module);

#endif  // SRC_MACHINEBASE_RLMODULE_HPP_
