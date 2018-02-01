/*
  ==============================================================================

    WojtekSynthOscillators.cpp
    Created: 15 Jan 2018 9:52:01pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WojtekSynth_SetOsc.h"


//==============================================================================
WojtekSynth_SetOsc::WojtekSynth_SetOsc(WojtekSynthAudioProcessor& p) :
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
    osc1Menu.addListener(this);
//    setOsc1Attache = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "wavetype1", osc1Menu);
    addAndMakeVisible(&osc1Menu);
}

WojtekSynth_SetOsc::~WojtekSynth_SetOsc()
{
}

void WojtekSynth_SetOsc::setMenuBounds(int _X, int _Y)
{
    oscMenuBoundX = _X;
    oscMenuBoundY = _Y;
}

void WojtekSynth_SetOsc::paint (Graphics& g)
{

}

void WojtekSynth_SetOsc::resized()
{
//    Rectangle<int> area = getLocalBounds().reduced(40);
    osc1Menu.setBounds(0, 0, oscMenuBoundX, oscMenuBoundY);
}

void WojtekSynth_SetOsc::comboBoxChanged (ComboBox *comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &osc1Menu) {
        processor.wParamIsChanged = true;
    }

}
