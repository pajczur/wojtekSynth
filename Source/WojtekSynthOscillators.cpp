/*
  ==============================================================================

    WojtekSynthOscillators.cpp
    Created: 15 Jan 2018 9:52:01pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WojtekSynthOscillators.h"


//==============================================================================
WojtekSynthOscillators::WojtekSynthOscillators(WojtekSynthAudioProcessor& p) :
processor(p)
{
    setSize(200, 50);
    
    oscMenu.addItem("sine",     1);
    oscMenu.addItem("saw",      2);
    oscMenu.addItem("savn",     3);
    oscMenu.addItem("squere",   4);
    oscMenu.addItem("triangle", 5);
    oscMenu.addItem("phasor",   6);
    oscMenu.addItem("noise",    7);
    
    oscMenu.setJustificationType(Justification::centred);
    
    oscGUIattache = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype", oscMenu);
    addAndMakeVisible(&oscMenu);
}

WojtekSynthOscillators::~WojtekSynthOscillators()
{
}

void WojtekSynthOscillators::paint (Graphics& g)
{

}

void WojtekSynthOscillators::resized()
{
//    Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(getLocalBounds());

}
