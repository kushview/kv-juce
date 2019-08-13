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

namespace kv {

static uint32 portBufferPadSize (uint32 size)
{
    return (size + 7) & (~7);
}

PortBuffer::PortBuffer (const URIs* ids, uint32 bufferType, uint32 bufferSize)
    : uris (ids), type (bufferType), capacity (bufferSize)
{
    atom_Float      = uris->atom_Float;
    atom_Sequence   = uris->atom_Sequence;
    atom_Sound      = uris->atom_Sound;
    midi_MidiEvent  = uris->midi_MidiEvent;

    data.reset (new uint8 [std::max (sizeof (float), (size_t) capacity)]);

    if (type == atom_Sequence)
    {
        buffer.atom = (LV2_Atom*) data.get();
    }
    else if (type == event_Event)
    {
        buffer.event = (LV2_Event_Buffer*) data.get();
    }
	else if (type == atom_Sound)
    {
		LV2_Atom_Vector* vec = (LV2_Atom_Vector*) buffer.atom;
		vec->body.child_size = sizeof (float);
		vec->body.child_type = uris->atom_Float;
	}
    else if (type == atom_Float)
    {
        buffer.control = (float*) data.get();
    }
    else
    {
        // trying to use an unsupported buffer type
        jassertfalse;
    }

    reset();
}

PortBuffer::~PortBuffer()
{
    buffer.atom = nullptr;
    data.reset();
}

void PortBuffer::setTypes (std::function<uint32_t(const char*)> map)
{
    atom_Float      = map (LV2_ATOM__Float);
    atom_Sequence   = map (LV2_ATOM__Sequence);
    midi_MidiEvent  = map (LV2_MIDI__MidiEvent);
}

bool PortBuffer::addEvent (int64 frames, uint32 size, uint32 bodyType, const uint8* data)
{
    if (isSequence())
    {
        if (sizeof(LV2_Atom) + buffer.atom->size + lv2_atom_pad_size(size) > capacity)
            return false;

        LV2_Atom_Sequence* seq = (LV2_Atom_Sequence*) buffer.atom;
        LV2_Atom_Event*    ev  = (LV2_Atom_Event*) ((uint8*)seq + lv2_atom_total_size (&seq->atom));

        ev->time.frames = frames;
        ev->body.size   = size;
        ev->body.type   = bodyType;
        memcpy (ev + 1, data, size);

        buffer.atom->size += sizeof (LV2_Atom_Event) + lv2_atom_pad_size (size);
        return true;
    }
    else if (isEvent())
    {
        if (buffer.event->capacity - buffer.event->size < sizeof(LV2_Event) + size)
            return false;

        LV2_Event* ev = (LV2_Event*)(buffer.event->data + buffer.event->size);
        ev->frames    = static_cast<uint32> (frames);
        ev->subframes = 0;
        ev->type      = type;
        ev->size      = size;
        memcpy ((uint8*)ev + sizeof(LV2_Event), data, size);

        buffer.event->size        += portBufferPadSize (sizeof (LV2_Event) + size);
        buffer.event->event_count += 1;
        return true;
    }

	return false;
}

void PortBuffer::clear()
{
    if (isAudio() || isControl())
    {

	}
    else if (isSequence())
    {
		buffer.atom->size = sizeof (LV2_Atom_Sequence_Body);
	}
    else if (isEvent())
    {
        buffer.event->event_count = 0;
        buffer.event->size        = 0;
    }
}

void PortBuffer::reset (const bool forOutput)
{
    if (isAudio())
    {
        buffer.atom->size = capacity - sizeof (LV2_Atom);
	}
    else if (isControl())
    {
        buffer.atom->size = sizeof (float);
        buffer.atom->type = type;
    }
    else if (isSequence())
    {
        buffer.atom->size = ! forOutput ? sizeof (LV2_Atom_Sequence_Body) 
                                        : capacity - sizeof (LV2_Atom_Sequence_Body);
        buffer.atom->type = type;
        LV2_Atom_Sequence* seq = (LV2_Atom_Sequence*) buffer.atom;
		seq->body.unit    = 0;
		seq->body.pad     = 0;
	}
    else if (isEvent())
    {
        buffer.event->capacity    = capacity - sizeof (LV2_Event_Buffer);
        buffer.event->header_size = sizeof (LV2_Event_Buffer);
        buffer.event->stamp_type  = LV2_EVENT_AUDIO_STAMP;
        buffer.event->event_count = 0;
        buffer.event->size        = 0;
        buffer.event->data        = data.get() + sizeof (LV2_Event_Buffer);
    }
}

void* PortBuffer::getPortData() const { return data.get(); }

}
