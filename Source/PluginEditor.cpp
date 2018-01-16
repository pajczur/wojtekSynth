/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
WojtekSynthAudioProcessorEditor::WojtekSynthAudioProcessorEditor (WojtekSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 800);
    
    attackL.setText("wAttack", dontSendNotification);
    attackL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&attackL);
    attackL.attachToComponent(&attackSlider, false);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    attackSlider.setRange(500.0f, 2000000.0f);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    attackSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&attackSlider);
//    attackAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.attackTree, "attack", attackSlider);
    attackAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    
    decayL.setText("wDecay", dontSendNotification);
    decayL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&decayL);
    decayL.attachToComponent(&decaySlider, false);
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    decaySlider.setRange(500.0f, 10000000.0f);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    decaySlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&decaySlider);
//    decayAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.decayTree, "decay", decaySlider);
    decayAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    
    sustainL.setText("wSustain", dontSendNotification);
    sustainL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&sustainL);
    sustainL.attachToComponent(&sustainSlider, false);
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    sustainSlider.setTextValueSuffix(" dB");
    addAndMakeVisible(&sustainSlider);
//    sustainAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.sustainTree, "sustain", sustainSlider);
    sustainAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    
    releaseL.setText("wRelease", dontSendNotification);
    releaseL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&releaseL);
    releaseL.attachToComponent(&releaseSlider, false);
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    releaseSlider.setRange(500.0f, 2000000.0f);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    releaseSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&releaseSlider);
//    releaseAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.releaseTree, "release", releaseSlider);
    releaseAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);
    
    addAndMakeVisible(&oscGUI);
}

WojtekSynthAudioProcessorEditor::~WojtekSynthAudioProcessorEditor()
{
}

//==============================================================================
void WojtekSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void WojtekSynthAudioProcessorEditor::resized()
{
    attackSlider.setBounds(50, 25, 300, 50);
    decaySlider.setBounds(50, 150, 300, 50);
    sustainSlider.setBounds(50, 275, 300, 50);
    releaseSlider.setBounds(50, 400, 300, 50);
    
    oscGUI.setBounds(100, 525, 200, 50);
}
