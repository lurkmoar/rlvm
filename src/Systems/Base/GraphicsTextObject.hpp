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
//
// -----------------------------------------------------------------------

#ifndef SRC_SYSTEMS_BASE_GRAPHICSTEXTOBJECT_HPP_
#define SRC_SYSTEMS_BASE_GRAPHICSTEXTOBJECT_HPP_

#include "MachineBase/RLMachine.hpp"
#include "MachineBase/Serialization.hpp"
#include "Systems/Base/GraphicsObjectData.hpp"

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/split_member.hpp>

class GraphicsObject;
class Surface;
class System;

/**
 * Represents the textual data made with commands such as obj_of_text,
 * obj_set_text, obj_text_opts, et cetera.
 */
class GraphicsTextObject : public GraphicsObjectData {
 public:
  explicit GraphicsTextObject(System& system);
  ~GraphicsTextObject();

  // ------------------------------------ [ GraphicsObjectData interface ]
  virtual int pixelWidth(const GraphicsObject& rendering_properties);
  virtual int pixelHeight(const GraphicsObject& rendering_properties);

  virtual GraphicsObjectData* clone() const;
  virtual void execute() { }

 protected:
  virtual boost::shared_ptr<const Surface> currentSurface(
      const GraphicsObject& go);
  virtual void objectInfo(std::ostream& tree);

 private:
  /// Current machine context.
  System& system_;

  std::string cached_utf8_str_;

  boost::shared_ptr<Surface> surface_;

  /**
   * Redraw surface_.
   */
  void updateSurface(const GraphicsObject& rp);

  bool needsUpdate(const GraphicsObject& rendering_properties);

  /// boost::serialization support
  friend class boost::serialization::access;

  template<class Archive>
  void save(Archive & ar, const unsigned int file_version) const;

  template<class Archive>
  void load(Archive& ar, const unsigned int file_version);

  BOOST_SERIALIZATION_SPLIT_MEMBER()
};

/**
 * We need help creating GraphicsTextObject s since they don't have a default
 * constructor:
 */
namespace boost { namespace serialization {
template<class Archive>
inline void load_construct_data(
  Archive & ar, GraphicsTextObject* t, const unsigned int file_version) {
  ::new(t)GraphicsTextObject(Serialization::g_current_machine->system());
}
  }}

#endif  // SRC_SYSTEMS_BASE_GRAPHICSTEXTOBJECT_HPP_
