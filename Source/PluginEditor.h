/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class WojtekSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    WojtekSynthAudioProcessorEditor (WojtekSynthAudioProcessor&);
    ~WojtekSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WojtekSynthAudioProcessor& processor;
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    
    Label attackL;
    Label decayL;
    Label sustainL;
    Label releaseL;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseAttache;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WojtekSynthAudioProcessorEditor)
};
