// Aseprite Document Library
// Copyright (c) 2001-2015 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "doc/remap.h"

#include "doc/palette_picks.h"

namespace doc {

// TODO this should be a non-member function, it's related to PalettePicks and Remap

// static
Remap Remap::moveSelectedEntriesTo(const PalettePicks& picks, int beforeIndex)
{
  Remap map(picks.size());

  int selectedTotal = 0;
  int selectedBeforeIndex = 0;

  for (int i=0; i<map.size(); ++i) {
    if (picks[i]) {
      ++selectedTotal;
      if (i < beforeIndex)
        ++selectedBeforeIndex;
    }
  }

  for (int i=0, j=0, k=0; i<map.size(); ++i) {
    if (k == beforeIndex - selectedBeforeIndex)
      k += selectedTotal;

    if (picks[i]) {
      map.map(i, beforeIndex - selectedBeforeIndex + j);
      ++j;
    }
    else {
      map.map(i, k++);
    }
  }

  return map;
}

void Remap::merge(const Remap& other)
{
  for (int i=0; i<size(); ++i) {
    m_map[i] = other[m_map[i]];
  }
}

Remap Remap::invert() const
{
  Remap inv(size());
  for (int i=0; i<size(); ++i)
    inv.map(operator[](i), i);
  return inv;
}

} // namespace doc
