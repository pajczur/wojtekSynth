/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "WojtekSynthOsc1.h"
#include "WojtekSynthEnvelopeGraph.h"


//==============================================================================
/**
*/
class WojtekSynthAudioProcessorEditor  : public AudioProcessorEditor,
                                         public Slider::Listener
{
public:
    WojtekSynthAudioProcessorEditor (WojtekSynthAudioProcessor& p);
    ~WojtekSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider *slider) override;
    
    void drawAttack();
    void drawDecay();
    void drawRelease();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WojtekSynthAudioProcessor& processor;
    Slider gainSlider;
    Label gainL;
    
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    
    Slider attackShape;
    Slider decayShape;
    Slider releaseShape;
    
    Label attackL;
    Label attackSL;
    Label decayL;
    Label decaySL;
    Label sustainL;
    Label releaseL;
    Label releaseSL;
    
    WojtekSynthOsc1 setOsc1;
    WojtekSynthOsc1 setOsc2;
    
    Slider oscMixSlider;
    Label osc1L;
    Label osc2L;
    Label mixL;
    
    WojtekSynthEnvelopeGraph envGraphWindow;
    
    Slider lowCutSlider;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackShapeAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayShapeAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseShapeAttache;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> oscMixAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainAttache;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> setOsc1Attache;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> setOsc2Attache;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lowCutAttache;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WojtekSynthAudioProcessorEditor)
};
