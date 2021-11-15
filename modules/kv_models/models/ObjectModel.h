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

/** A thin wrapper around a juce ValueTree */
class JUCE_API ObjectModel
{
public:
    explicit ObjectModel (const ValueTree& data = ValueTree());
    ObjectModel (const Identifier& slugId);
    virtual ~ObjectModel() { }

    /** Get a property from the underlying ValueTree */
    inline var getProperty (const Identifier& id, const var& d = var()) const {
        return objectData.getProperty (id, d);
    }
    
    /** Get a property as a juce Value from the ValueTree */
    Value getPropertyAsValue (const Identifier& property, bool updateSynchronously = false);

    /** Set a property */
    inline ObjectModel& setProperty (const Identifier& property, const var& val)
    {
        objectData.setProperty (property, val, nullptr);
        return *this;
    }
    
    /** Returns true if the property exists */
    inline bool hasProperty (const Identifier& property) const { return objectData.hasProperty (property); }

    /** Get the ValueTree's type */
    inline Identifier getType() const { return objectData.getType(); }

    /** Determine this objects ValueTree type */
    inline bool hasType (const Identifier& type) const { return objectData.hasType (type); }

    /** Access to the underlying ValueTree (const version) */
    inline const ValueTree& node() const { return objectData; }
    inline const ValueTree& getValueTree() const { return objectData; }

    /** Access to the underlying ValueTree */
    ValueTree node() { return objectData; }
    ValueTree getValueTree() { return objectData; }
    
    virtual std::unique_ptr<XmlElement> createXml() const { return objectData.createXml(); }

    /** Replace this objects ValueTree with another
        If you need to do something special when data is set, then override
        the canAcceptData and setNodeData methods

        @param The new data to use
    */
    ValueTree setData (const ValueTree& data);

    /** Returns the number of children the underlying ValueTree has */
    int32 getNumChildren() const { return objectData.getNumChildren(); }

    /** Count the number of children with a type */
    int32 countChildrenOfType (const Identifier& slug) const;

    String toXmlString() const { return objectData.toXmlString(); }
protected:

    /** Override this to handle special data validation This is called
        during setData

        @param data The new data to set
    */
    virtual bool canAcceptData (const ValueTree& data);

    /** Override this to handle special data setting. This is called during
        setData and only if canAcceptData returns true

        @param data The data being setData
    */
    virtual void setNodeData (const ValueTree& data);
    ValueTree objectData;

    template<typename POD>
    inline void stabilizePropertyPOD (const Identifier& prop, const POD& defaultValue = var()) {
        if (objectData.isValid())
            objectData.setProperty (prop, (POD) objectData.getProperty (prop, defaultValue), nullptr);
    }

    inline void stabilizePropertyString (const Identifier& prop, const String& defaultValue = String()) {
        if (objectData.isValid())
            objectData.setProperty (prop, objectData.getProperty (prop, defaultValue).toString(), nullptr);
    }

    inline void stabilizeProperty (const Identifier& prop, const var& defaultValue) {
        if (objectData.isValid())
            objectData.setProperty (prop, objectData.getProperty (prop, defaultValue), nullptr);
    }
};

}
