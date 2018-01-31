/*
  ==============================================================================

    wojtekSynthEnvelopeGraph.h
    Created: 16 Jan 2018 6:16:13pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WojtekSynthEnvelope.h"

//==============================================================================
/*
*/
class WojtekSynthEnvelopeGraph    : public Component
{
public:
    WojtekSynthEnvelopeGraph();
    ~WojtekSynthEnvelopeGraph();

    void paint (Graphics&) override;
    void resized() override;

    WojtekSynthEnvelope adsrGraph;
    Path attackPath;
    Path jointPathA;
    
    Path decayPath;
    Path jointPathD;
    
    Path releasePath;
    Path jointPathR;
    
    float startPointX = 10.0f;
    float startPointY = 190.0f;
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WojtekSynthEnvelopeGraph)
};
