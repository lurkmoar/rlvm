// -*- Mode: C++; tab-width:2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi:tw=80:et:ts=2:sts=2
//
// -----------------------------------------------------------------------
//
// This file is part of RLVM, a RealLive virtual machine clone.
//
// -----------------------------------------------------------------------
//
// Copyright (C) 2011 Elliot Glaysher
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
// -----------------------------------------------------------------------

#include "Systems/Base/ColourFilterObjectData.hpp"

#include <ostream>

#include "Systems/Base/Colour.hpp"
#include "Systems/Base/GraphicsObject.hpp"
#include "Systems/Base/GraphicsSystem.hpp"
#include "Utilities/Exception.hpp"

ColourFilterObjectData::ColourFilterObjectData(GraphicsSystem& system,
                                               const Rect& screen_rect)
    : graphics_system_(system),
      screen_rect_(screen_rect) {
}

ColourFilterObjectData::~ColourFilterObjectData() {}

void ColourFilterObjectData::render(const GraphicsObject& go,
                                    std::ostream* tree) {
  RGBAColour colour = go.colour();
  colour.setAlpha(
      static_cast<int>(colour.a_float() * go.alpha()));

  graphics_system_.fillScreenArea(screen_rect_, colour);

  if (tree)
    objectInfo(*tree);
}

int ColourFilterObjectData::pixelWidth(
    const GraphicsObject& rendering_properties) {
  throw rlvm::Exception("There is no sane value for this!");
}

int ColourFilterObjectData::pixelHeight(
    const GraphicsObject& rendering_properties) {
  throw rlvm::Exception("There is no sane value for this!");
}

GraphicsObjectData* ColourFilterObjectData::clone() const {
  return new ColourFilterObjectData(graphics_system_, screen_rect_);
}

void ColourFilterObjectData::execute() {
  // Nothing to do.
}

bool ColourFilterObjectData::isAnimation() const {
  return false;
}

void ColourFilterObjectData::playSet(int set) {
  // No op
}

boost::shared_ptr<Surface> ColourFilterObjectData::currentSurface(
    const GraphicsObject& rp) {
  return boost::shared_ptr<Surface>();
}

void ColourFilterObjectData::objectInfo(std::ostream& tree) {
  tree << "ColourFilterObjectData(" << screen_rect_ << ")" << std::endl;
}