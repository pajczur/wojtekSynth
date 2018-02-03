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
    WojtekSynthEnvelopeGraph(int wColor);
    ~WojtekSynthEnvelopeGraph();

    void paint (Graphics&) override;
    void resized() override;
    
    void drawAttack(double attSliderValue, double attSliderMax, double attShapeSliderValue, double dGain);
    void drawDecay(double decSliderValue, double decSliderMax, double decShapeSliderValue, double susSliderValue, double dGain);
    void drawRelease(double relSliderValue, double relSliderMax, double relShapeSliderValue, double susSliderValue, double dGain);

    WojtekSynthEnvelope adsrGraph;
    Path attackPath;
    Path jointPathA;
    
    Path decayPath;
    Path jointPathD;
    
    Path releasePath;
    Path jointPathR;
    
    float startPointX = 10.0f;
    float startPointY = 190.0f;
    int wBackgroundColour;
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WojtekSynthEnvelopeGraph)
};
