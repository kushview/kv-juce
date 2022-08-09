/*
    kv_gui.cpp - This file is part of KV JUCE Modules
    Copyright (C) 2016-2021 Kushview, LLC.  All rights reserved.

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

#if JUCE_MODULE_AVAILABLE_kv_engines
 #include <juce_audio_processors/juce_audio_processors.h>
 #include <kv_engines/kv_engines.h>
#endif

#include <kv_models/kv_models.h>
#include "kv_gui.h"

#include "base/FileComboBox.cpp"
#include "base/DecibelScaleComponent.cpp"
#include "base/DigitalMeter.cpp"
#include "base/PatchMatrixComponent.cpp"

#if JUCE_MODULE_AVAILABLE_kv_engines
 #include "timeline/TimelineComponent.cpp"
 #include "timeline/TimelineClip.cpp"
#endif

#include "base/LookAndFeel_KV1.cpp"

#if KV_DOCKING_WINDOWS
 #include "docking/Dock.cpp"
 #include "docking/DockArea.cpp"
 #include "docking/DockItem.cpp"
 #include "docking/DockLayout.cpp"
 #include "docking/DockPanel.cpp"
 #include "docking/DockItemTabs.cpp"
 #include "docking/DockWindow.cpp"
 #include "docking/DockContainer.cpp"
#endif
