/*
  ==============================================================================

    WojtekSynthSetOsc2.cpp
    Created: 19 Jan 2018 9:46:13pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WojtekSynthSetOsc2.h"


//==============================================================================
WojtekSynthSetOsc2::WojtekSynthSetOsc2(WojtekSynthAudioProcessor& p) :
processor(p)
{
    setSize(300, 35);
    
    osc2Menu.addItem("sine",     1);
    osc2Menu.addItem("saw",      2);
    osc2Menu.addItem("squere",   3);
    osc2Menu.addItem("triangle", 4);
    osc2Menu.addItem("phasor",   5);
    osc2Menu.addItem("noise",    6);
    osc2Menu.setJustificationType(Justification::centred);
    setOsc2Attache = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype2", osc2Menu);
    addAndMakeVisible(&osc2Menu);
}

WojtekSynthSetOsc2::~WojtekSynthSetOsc2()
{
}

void WojtekSynthSetOsc2::paint (Graphics& g)
{
    
}

void WojtekSynthSetOsc2::resized()
{
    //    Rectangle<int> area = getLocalBounds().reduced(40);
    osc2Menu.setBounds(0, 0, 150, 35);
}
