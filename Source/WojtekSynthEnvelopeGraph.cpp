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
WojtekSynthEnvelopeGraph::WojtekSynthEnvelopeGraph(int wColor)
{
    setSize(350, 200);
    wBackgroundColour = wColor;
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

    if(wBackgroundColour == 1) {
        g.fillAll (Colours::darkgrey);   // clear the background
    }
    
    if(wBackgroundColour == 0) {
        g.fillAll (Colours::black);   // clear the background
    }
    
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


//=== D R A W I N G == F U N C T I O N S ===
void WojtekSynthEnvelopeGraph::drawAttack(double attSliderValue, double attSliderMax, double attShapeSliderValue, double dGain)
{
    float attackPos = attSliderValue / attSliderMax;
    attackPath.clear();
    jointPathA.clear();
    attackPath.startNewSubPath(startPointX, startPointY);
    adsrGraph.wLogAttackManip(attShapeSliderValue);
    
    for (int i=0; i<=100; i++) {
        attackPath.lineTo(startPointX+((330.0f/3.0f)*attackPos*i/100),
                          startPointY - ((180*adsrGraph.wLogAttack((float)i/100.0f))) * dGain);
        
        if(i == 100) {
            jointPathA.addEllipse(startPointX+((330.0f/3.0f)*attackPos*i/100)-3,
                                  startPointY - ((180*adsrGraph.wLogAttack((float)i/100.0f)) * dGain)-3,
                                  6, 6);
        }
    }
}


void WojtekSynthEnvelopeGraph::drawDecay(double decSliderValue, double decSliderMax, double decShapeSliderValue, double susSliderValue, double dGain)
{
    float decayPos = decSliderValue / decSliderMax;
    float sustainPos = (1 - susSliderValue) * dGain;
    float decInitAmp = 1;
    
    decayPath.clear();
    jointPathD.clear();
    decayPath.startNewSubPath(jointPathA.getCurrentPosition());
    adsrGraph.wLogDecayManip(decShapeSliderValue);
    
    for (int i=0; i<=100; i++) {
        decayPath.lineTo(-0.5+jointPathA.getCurrentPosition().getX()+((330.0f/3.0f)*decayPos*i/100),
                              jointPathA.getCurrentPosition().getY() +
                              (180*sustainPos*(1-adsrGraph.wLogDecay(decInitAmp)))+3);
        
        
        if(i == 100) {
            jointPathD.addEllipse(-0.5+jointPathA.getCurrentPosition().getX()+((330.0f/3.0f)*decayPos*i/100)-3,
                                       jointPathA.getCurrentPosition().getY() +
                                       (180*sustainPos*(1-adsrGraph.wLogDecay(decInitAmp)))-1, 8, 8);
        }
        decInitAmp -= 1.0f/100.0f;
    }
}


void WojtekSynthEnvelopeGraph::drawRelease(double relSliderValue, double relSliderMax, double relShapeSliderValue, double susSliderValue, double dGain)
{
    float releasePos = relSliderValue / relSliderMax;
    float sustainPos = susSliderValue * dGain;
    float relInitAmp = 1;
    
    Point<float> wXYr = jointPathD.getCurrentPosition();
    
    releasePath.clear();
    jointPathR.clear();
    releasePath.startNewSubPath(jointPathD.getCurrentPosition().getX(), jointPathD.getCurrentPosition().getY()+4);
    adsrGraph.wLogReleaseManip(relShapeSliderValue);
    
    for (int i=0; i<=100; i++) {
        releasePath.lineTo(wXYr.getX()+((330.0f/3.0f)*releasePos*i/100),
                           wXYr.getY() + (180*sustainPos*(1-adsrGraph.wLogRelease(relInitAmp))) + 4);
        
        if(i == 100) {
            jointPathR.addEllipse(wXYr.getX() + ((330.0f/3.0f)*releasePos*i/100)-3,
                                  wXYr.getY() + (180*sustainPos*(1-adsrGraph.wLogRelease(relInitAmp)))+1, 6, 6);
        }
        relInitAmp -= 1.0f/100.0f;
    }
}
