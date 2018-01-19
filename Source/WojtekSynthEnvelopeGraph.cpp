/*
  ==============================================================================

    wojtekSynthEnvelopeGraph.cpp
    Created: 16 Jan 2018 6:16:13pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WojtekSynthEnvelopeGraph.h"
#include <iomanip>

//==============================================================================
WojtekSynthEnvelopeGraph::WojtekSynthEnvelopeGraph()
{
    setSize(350, 200);
}

WojtekSynthEnvelopeGraph::~WojtekSynthEnvelopeGraph()
{
}

void WojtekSynthEnvelopeGraph::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::black);   // clear the background
    g.setColour(Colours::white);
    
    g.strokePath(attackPath, PathStrokeType(1));
    g.fillPath(jointPathA);
    
    g.strokePath(decayPath, PathStrokeType(1));
    g.fillPath(jointPathD);
    
    g.strokePath(releasePath, PathStrokeType(1));
    g.fillPath(jointPathR);
}

void WojtekSynthEnvelopeGraph::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}
