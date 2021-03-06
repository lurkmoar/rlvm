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

#ifndef SRC_SYSTEMS_BASE_VOICECACHE_HPP_
#define SRC_SYSTEMS_BASE_VOICECACHE_HPP_

#include "lru_cache.hpp"

#include <boost/shared_ptr.hpp>

class SoundSystem;
class VoiceArchive;
class VoiceSample;

/**
 *
 */
class VoiceCache {
 public:
  explicit VoiceCache(SoundSystem& sound_system);
  ~VoiceCache();

  boost::shared_ptr<VoiceSample> find(int id);

 private:
  // Searches for a file archive of voices.
  boost::shared_ptr<VoiceArchive> findArchive(int file_no) const;

  // Searches for an unarchived ogg or mp3 file.
  boost::shared_ptr<VoiceSample> findUnpackedSample(
      int file_no, int index) const;

  SoundSystem& sound_system_;

  /// A mapping between a file id number and the underlying file object.
  LRUCache<int, boost::shared_ptr<VoiceArchive> > file_cache_;
};  // class VoiceCache

#endif  // SRC_SYSTEMS_BASE_VOICECACHE_HPP_
