/*
  ==============================================================================

    WojtekSynthOscillators.cpp
    Created: 15 Jan 2018 9:52:01pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WojtekSynthOsc1.h"


//==============================================================================
WojtekSynthOsc1::WojtekSynthOsc1(WojtekSynthAudioProcessor& p) :
processor(p)
{
    setSize(300, 35);
    
    osc1Menu.addItem("sine",     1);
    osc1Menu.addItem("saw",      2);
    osc1Menu.addItem("squere",   3);
    osc1Menu.addItem("triangle", 4);
    osc1Menu.addItem("phasor",   5);
    osc1Menu.addItem("noise",    6);
    osc1Menu.setJustificationType(Justification::centred);
    setOsc1Attache = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype1", osc1Menu);
    addAndMakeVisible(&osc1Menu);    
}

WojtekSynthOsc1::~WojtekSynthOsc1()
{
}

void WojtekSynthOsc1::paint (Graphics& g)
{

}

void WojtekSynthOsc1::resized()
{
//    Rectangle<int> area = getLocalBounds().reduced(40);
    osc1Menu.setBounds(0, 0, 150, 35);
}
