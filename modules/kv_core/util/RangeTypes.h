/*
    This file is part of the Kushview Modules for JUCE
    Copyright (c) 2014-2019  Kushview, LLC.  All rights reserved.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#pragma once

namespace kv {
class FrameSpan : public juce::Range<int64>
{
public:
    inline FrameSpan (int64 i, int64 o) : juce::Range<int64> (i, o) { }
    inline ~FrameSpan() { }
    inline int64 inPoint()  const { return getStart(); }
    inline int64 outPoint() const { return getEnd(); }
    inline int64 length() const { return getLength(); }
    inline bool isZero() const { return getLength() == 0; }
    inline void setInPoint (const int64 in) { setStart (in); }
    inline void setOutPoint (const int64 out) { setEnd (out); }
};
}
