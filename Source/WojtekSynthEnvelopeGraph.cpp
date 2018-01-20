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
    
    g.strokePath(attackPath, PathStrokeType(2));
    g.fillPath(jointPathA);
    
    g.strokePath(decayPath, PathStrokeType(2));
    g.fillPath(jointPathD);
    
    g.strokePath(releasePath, PathStrokeType(2));
    g.fillPath(jointPathR);
    
    g.setColour(Colours::lightblue);
    g.drawLine(10, 0, 10, 200);
    g.drawLine(10+(330/3), 0, 10+(330/3), 200);
    g.drawLine(10+(330*2/3), 0, 10+(330*2/3), 200);
    g.drawLine(10+330, 0, 10+330, 200);
}

void WojtekSynthEnvelopeGraph::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}
