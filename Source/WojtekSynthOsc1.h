/*
  ==============================================================================

    WojtekSynthOscillators.h
    Created: 15 Jan 2018 9:52:01pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WojtekSynthOsc1    : public Component
{
public:
    WojtekSynthOsc1(WojtekSynthAudioProcessor& p);
    ~WojtekSynthOsc1();

    void paint (Graphics&) override;
    void resized() override;

private:
    ComboBox osc1Menu;
 
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> setOsc1Attache;
    
    WojtekSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WojtekSynthOsc1)
};
