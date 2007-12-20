// -*- Mode: C++; tab-width:2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi:tw=80:et:ts=2:sts=2
//
// -----------------------------------------------------------------------
//
// This file is part of RLVM, a RealLive virtual machine clone.
//
// -----------------------------------------------------------------------
//
// Copyright (C) 2007 Elliot Glaysher
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
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

#ifndef __SaveGameHeader_hpp__
#define __SaveGameHeader_hpp__

#include <string>

//include all types plus i/o
#include <boost/date_time/posix_time/posix_time_types.hpp>

// -----------------------------------------------------------------------

/** 
 * Header structure written to and read from the start of each save
 * game file. This structure is at the top of the file since it is
 * what gets queried by SaveDate, SaveTime, et cetera.
 */
struct SaveGameHeader
{
  SaveGameHeader();
  SaveGameHeader(const std::string& inTitle);
  ~SaveGameHeader();

  /// The title of the current saved game
  std::string title;

  /// The time the save file was created.
  boost::posix_time::ptime saveTime;

  /// boost::serialization support
  template<class Archive>
  void serialize(Archive& ar, unsigned int version)
  {
    ar & title & saveTime;
  }
};

#endif