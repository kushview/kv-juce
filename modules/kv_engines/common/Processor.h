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

class Processor :  public juce::AudioPluginInstance
{

public:
    Processor() { }
    virtual ~Processor() { }

    /** Returns a channel index for a given port */
    int getChannelPort (uint32 port);

    /** Returns the total number of ports for this processor */
    virtual uint32 getNumPorts();

    /** Returns the total number of ports for a given filter */
    virtual uint32 getNumPorts (PortType type, bool isInput);

    /** Returns the port index from a 'channel' index of a particular
        port type */
    uint32 getNthPort (PortType type, int index, bool isInput, bool indexIsOneBased = true);

    /** Returns the type for a given port */
    virtual PortType getPortType (uint32 port);

    /** Returns true if the port is an input (destination port) */
    virtual bool isPortInput (uint32 port);

    /** Returns true if the port is an output (source port) */
    inline bool isPortOutput (uint32 port) { return ! isPortInput (port); }

    /** Write data to a port */
    virtual bool writeToPort (uint32 port, uint32 size, uint32 protocol, void const* data);

    bool writeControlValue (uint32 port, float value);

    static uint32 getPortForAudioChannel (AudioProcessor*, int, bool);
    static uint32 getNumPorts (AudioProcessor*);
    static uint32 getNumPorts (AudioProcessor*, PortType type, bool isInput);
    static PortType getPortType (AudioProcessor*, uint32 port);
    static bool isPortInput (AudioProcessor*, uint32 port);
    static bool writeToPort (AudioProcessor*, uint32 port, uint32 size, uint32 protocol, void const* data);
};
