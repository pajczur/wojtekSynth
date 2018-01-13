/*
  ==============================================================================

    WojtekSynthSound.h
    Created: 3 Jan 2018 10:26:08pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class WojtekSynthSound : public SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiChannel) override
    {
        return true;
    }
};
