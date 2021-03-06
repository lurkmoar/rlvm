// -*- Mode: C++; tab-width:2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi:tw=80:et:ts=2:sts=2
//
// -----------------------------------------------------------------------
//
// This file is part of RLVM, a RealLive virtual machine clone.
//
// -----------------------------------------------------------------------
//
// Copyright (C) 2009 Elliot Glaysher
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
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
// -----------------------------------------------------------------------

#include "Utilities/Exception.hpp"

#include <fstream>
#include <sstream>
#include <string>

using std::ostringstream;

namespace rlvm {

// -----------------------------------------------------------------------
// Exception
// -----------------------------------------------------------------------

Exception::Exception(const std::string& what)
  : description(what),
    operation_(NULL) {
}

Exception::~Exception() throw() {}

const char* Exception::what() const throw() {
  return description.c_str();
}

// -----------------------------------------------------------------------
// UserPresentableError
// -----------------------------------------------------------------------
UserPresentableError::UserPresentableError(
    const std::string& message_text,
    const std::string& informative_text)
    : Exception(message_text + ": " + informative_text),
      message_text_(message_text),
      informative_text_(informative_text) {
}

UserPresentableError::~UserPresentableError() throw() {}

// -----------------------------------------------------------------------
// UnimplementedOpcode
// -----------------------------------------------------------------------
UnimplementedOpcode::UnimplementedOpcode(
    const std::string& funName,
    int modtype, int module, int opcode, int overload)
    : Exception("") {
  std::ostringstream oss;
  oss << funName << " (opcode<" << modtype << ":" << module << ":" << opcode
      << ", " << overload << ">)";
  name_ = oss.str();
  setDescription();
}

UnimplementedOpcode::UnimplementedOpcode(
    int modtype, int module, int opcode, int overload)
    : Exception("") {
  ostringstream oss;
  oss << "opcode<" << modtype << ":" << module << ":" << opcode
      << ", " << overload << ">";
  name_ = oss.str();
  setDescription();
}

UnimplementedOpcode::~UnimplementedOpcode() throw() {
}

void UnimplementedOpcode::setDescription() {
  ostringstream oss;
  oss << "Undefined: " << name_;
  description = oss.str();
}

}  // namespace rlvm

