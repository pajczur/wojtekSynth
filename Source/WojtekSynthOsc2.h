/*
  ==============================================================================

    WojtekSynthSetOsc2.h
    Created: 19 Jan 2018 9:46:13pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class WojtekSynthOsc2    : public Component
{
public:
    WojtekSynthOsc2(WojtekSynthAudioProcessor& p);
    ~WojtekSynthOsc2();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    ComboBox osc2Menu;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> setOsc2Attache;
    
    WojtekSynthAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WojtekSynthOsc2)
};
