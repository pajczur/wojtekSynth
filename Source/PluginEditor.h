/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "WojtekSynth_SetOsc.h"
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


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WojtekSynthAudioProcessor& processor;
    
    Slider polyVoices;  Label polyVoicesL;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> polyVoicesAttache;

    
    //== O S C I L L A T O R == M I X E R ==
    WojtekSynth_SetOsc  setOsc1;        Label osc1L;
    WojtekSynth_SetOsc  setOsc2;        Label osc2L;
    Slider              oscMixSlider;   Label mixL;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> setOsc1Attache;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> setOsc2Attache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>   oscMixAttache;
    
    
    
    
    //== O S C == 2 == S E M I == P I T C H ==
    Slider              setOsc2Pitch;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>   osc2PitchAttache;
    
    
    
    
    //== V O I C E == E N V E L O P E ==
    Slider  attackShape;    Label attackSL;
    Slider  decayShape;     Label decaySL;
    Slider  releaseShape;   Label releaseSL;
    
    Slider  attackSlider;   Label attackL;
    Slider  decaySlider;    Label decayL;
    Slider  sustainSlider;  Label sustainL;
    Slider  releaseSlider;  Label releaseL;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackShapeAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayShapeAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseShapeAttache;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainAttache;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseAttache;
    
    
    //== S E C O N D == E N V E L O P E ==
    Slider  attackShape_2;    Label attackSL_2;
    Slider  decayShape_2;     Label decaySL_2;
    Slider  releaseShape_2;   Label releaseSL_2;
    
    Slider  attackSlider_2;   Label attackL_2;
    Slider  decaySlider_2;    Label decayL_2;
    Slider  sustainSlider_2;  Label sustainL_2;
    Slider  releaseSlider_2;  Label releaseL_2;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackShapeAttache_2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayShapeAttache_2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseShapeAttache_2;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackAttache_2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayAttache_2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainAttache_2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseAttache_2;
    
    Slider env2AmountSlider;    Label env2AmountSliderL;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> env2AmountSliderAttache;
    
    
    
    //== E N V == C H O O S E R ==
    Slider                      wojtekEnvelopeSwitch;
    WojtekSynthEnvelopeGraph    envGraphWindow;
    WojtekSynthEnvelopeGraph    envGraphWindow_2;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> EnvSwitchAttache;
    
    
    
    //== G A I N == S L I D E R ==
    Slider gainSlider;
    Label gainL;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainAttache;
    
    
    

    //== F I L T E R == S L I D E R S ==
    Slider lowCutSliderA1;      Label lowCutA1L;
    Slider lowCutSliderA0;      Label lowCutA0L;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lowCutAttache_a1;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lowCutAttache_a0;


    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WojtekSynthAudioProcessorEditor)
};
