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
class WojtekSynthOscillators    : public Component
{
public:
    WojtekSynthOscillators(WojtekSynthAudioProcessor& p);
    ~WojtekSynthOscillators();

    void paint (Graphics&) override;
    void resized() override;

private:
    ComboBox oscMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> oscGUIattache;
    
    WojtekSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WojtekSynthOscillators)
};
