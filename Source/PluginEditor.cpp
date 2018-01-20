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
    : AudioProcessorEditor (&p), processor (p), setOsc1(p), setOsc2(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (775, 500);
    
    attackSL.setText("A. shape", dontSendNotification);
    attackSL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&attackSL);
    attackSL.attachToComponent(&attackShape, false);
    attackShape.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    attackShape.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    attackShape.setRange(0.000000001, 0.999999999);
    attackShape.addListener(this);
    addAndMakeVisible(&attackShape);
    attackShapeAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attackshape", attackShape);
    
    decaySL.setText("D. shape", dontSendNotification);
    decaySL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&decaySL);
    decaySL.attachToComponent(&decayShape, false);
    decayShape.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    decayShape.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    decayShape.setRange(0.000000001, 0.999999999);
    decayShape.addListener(this);
    addAndMakeVisible(&decayShape);
    decayShapeAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decayshape", decayShape);
    
    releaseSL.setText("R. shape", dontSendNotification);
    releaseSL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&releaseSL);
    releaseSL.attachToComponent(&releaseShape, false);
    releaseShape.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    releaseShape.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    releaseShape.setRange(0.000000001, 0.999999999);
    releaseShape.addListener(this);
    addAndMakeVisible(&releaseShape);
    releaseShapeAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "releaseshape", releaseShape);
    
    
    
    attackL.setText("wAttack", dontSendNotification);
    attackL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&attackL);
    attackL.attachToComponent(&attackSlider, false);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    attackSlider.setRange(2500.0f, 2000000.0f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    attackSlider.setTextValueSuffix(" ms");
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    attackAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    
    decayL.setText("wDecay", dontSendNotification);
    decayL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&decayL);
    decayL.attachToComponent(&decaySlider, false);
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    decaySlider.setRange(2500.0f, 2000000.0f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    decaySlider.setTextValueSuffix(" ms");
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    decayAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    
    sustainL.setText("wSustain", dontSendNotification);
    sustainL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&sustainL);
    sustainL.attachToComponent(&sustainSlider, false);
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    sustainSlider.setTextValueSuffix(" dB");
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);
    sustainAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    
    releaseL.setText("wRelease", dontSendNotification);
    releaseL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&releaseL);
    releaseL.attachToComponent(&releaseSlider, false);
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    releaseSlider.setRange(2500.0f, 2000000.0f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    releaseSlider.setTextValueSuffix(" ms");
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    releaseAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);
    
    osc1L.setText("osc1", dontSendNotification);
    osc1L.setJustificationType(Justification::bottomLeft);
    osc1L.attachToComponent(&oscMixSlider, false);
    addAndMakeVisible(&osc1L);
    
    osc2L.setText("osc2", dontSendNotification);
    osc2L.setJustificationType(Justification::bottomRight);
    osc2L.attachToComponent(&oscMixSlider, false);
    addAndMakeVisible(&osc2L);
    
    mixL.setText("MIX", dontSendNotification);
    mixL.setJustificationType(Justification::centredBottom);
    mixL.attachToComponent(&oscMixSlider, false);
    addAndMakeVisible(&mixL);
    
    oscMixSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    oscMixSlider.setRange(-1.0f, 1.0f);
    oscMixSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    addAndMakeVisible(&oscMixSlider);
    oscMixAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscmix", oscMixSlider);
    
    addAndMakeVisible(&setOsc1);
    addAndMakeVisible(&setOsc2);
    addAndMakeVisible(&envGraphWindow);
    
    gainL.setText("wGain", dontSendNotification);
    gainL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&gainL);
    gainL.attachToComponent(&gainSlider, false);
    gainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    gainSlider.setRange(-66.0f, 0.0f);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.addListener(this);
    addAndMakeVisible(&gainSlider);
    gainAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "gain", gainSlider);
    
}

WojtekSynthAudioProcessorEditor::~WojtekSynthAudioProcessorEditor()
{
}

//==============================================================================
void WojtekSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour(Colours::lightblue);
    g.drawText("0s", 401, 9, 20, 10, Justification::centredTop);
    g.drawText("2s", 401+(1*110), 9, 20, 10, Justification::centredTop);
    g.drawText("4s", 401+(2*110), 9, 20, 10, Justification::centredTop);
    g.drawText("6s", 401+(3*110), 9, 20, 10, Justification::centredTop);
}

void WojtekSynthAudioProcessorEditor::resized()
{
    attackSlider.setBounds(50, 25, 300, 50);
    decaySlider.setBounds(50, 125-5, 300, 50);
    sustainSlider.setBounds(50, 225-(2*5), 300, 50);
    releaseSlider.setBounds(50, 325-(3*5), 300, 50);
    
    attackShape.setBounds(420, 250, 75, 70);
    decayShape.setBounds(530, 250, 75, 70);
    releaseShape.setBounds(640, 250, 75, 70);
    
    setOsc1.setBounds(350+((350-200)/2)-3, 440, 150, 35);
    setOsc2.setBounds(500+((350-200)/2)-3, 440, 150, 35);
    oscMixSlider.setBounds(417, 325+65, 310, 50);
    
    gainSlider.setBounds(200-35, 400, 70, 70);
    envGraphWindow.setBounds(400, 25, envGraphWindow.getWidth(), envGraphWindow.getHeight());
}

void WojtekSynthAudioProcessorEditor::sliderValueChanged (Slider *slider)
{
    if(slider == &attackShape || slider == &attackSlider) {
        drawAttack();
        drawDecay();
        drawRelease();
        envGraphWindow.repaint();
    }

    if(slider == &decayShape || slider == &decaySlider || slider == &sustainSlider) {
        drawDecay();
        drawRelease();
        envGraphWindow.repaint();
    }
    
    if(slider == &releaseShape || slider == &releaseSlider) {
        drawRelease();
        envGraphWindow.repaint();
    }
}

void WojtekSynthAudioProcessorEditor::drawAttack()
{
    float attackPos = attackSlider.getValue()/attackSlider.getMaximum();
    
    envGraphWindow.attackPath.clear();
    envGraphWindow.jointPathA.clear();
    envGraphWindow.attackPath.startNewSubPath(envGraphWindow.startPointX, envGraphWindow.startPointY);
    envGraphWindow.adsrGraph.wLogAttackManip(attackShape.getValue());
    
    for (int i=0; i<=100; i++) {
        envGraphWindow.attackPath.lineTo(envGraphWindow.startPointX+((330.0f/3.0f)*attackPos*i/100),
                                         envGraphWindow.startPointY - (160*envGraphWindow.adsrGraph.wLogAttack((float)i/100.0f)));
        
        if(i == 100) {
            envGraphWindow.jointPathA.addEllipse(envGraphWindow.startPointX+((330.0f/3.0f)*attackPos*i/100)-3, envGraphWindow.startPointY - (160*envGraphWindow.adsrGraph.wLogAttack((float)i/100.0f))-3, 6, 6);
        }
    }
}

void WojtekSynthAudioProcessorEditor::drawDecay()
{
    float decayPos = decaySlider.getValue()/decaySlider.getMaximum();
    float sustainPos = (1-sustainSlider.getValue());
    float decInitAmp = 1;
    
    envGraphWindow.decayPath.clear();
    envGraphWindow.jointPathD.clear();
    envGraphWindow.decayPath.startNewSubPath(envGraphWindow.jointPathA.getCurrentPosition());
    envGraphWindow.adsrGraph.wLogDecayManip(decayShape.getValue());
    
    for (int i=0; i<=100; i++) {
        envGraphWindow.decayPath.lineTo(-0.5+envGraphWindow.jointPathA.getCurrentPosition().getX()+((330.0f/3.0f)*decayPos*i/100),
                                        envGraphWindow.jointPathA.getCurrentPosition().getY() + (160*sustainPos*(1-envGraphWindow.adsrGraph.wLogDecay(decInitAmp)))+3);
        
        
        if(i == 100) {
            envGraphWindow.jointPathD.addEllipse(-0.5+envGraphWindow.jointPathA.getCurrentPosition().getX()+((330.0f/3.0f)*decayPos*i/100)-3, envGraphWindow.jointPathA.getCurrentPosition().getY() + (160*sustainPos*(1-envGraphWindow.adsrGraph.wLogDecay(decInitAmp)))-1, 8, 8);
        }
        decInitAmp -= 1.0f/100.0f;
    }
    
}


void WojtekSynthAudioProcessorEditor::drawRelease()
{
    float releasePos = releaseSlider.getValue()/releaseSlider.getMaximum();
    float sustainPos = sustainSlider.getValue();
    float relInitAmp = 1;

    Point<float> wXYr = envGraphWindow.jointPathD.getCurrentPosition();
    
    envGraphWindow.releasePath.clear();
    envGraphWindow.jointPathR.clear();
    envGraphWindow.releasePath.startNewSubPath(envGraphWindow.jointPathD.getCurrentPosition().getX(),
                                               envGraphWindow.jointPathD.getCurrentPosition().getY()+4);
    envGraphWindow.adsrGraph.wLogReleaseManip(releaseShape.getValue());
    
    for (int i=0; i<=100; i++) {
        envGraphWindow.releasePath.lineTo(wXYr.getX()+((330.0f/3.0f)*releasePos*i/100), wXYr.getY()+
                (160*sustainPos*(1-envGraphWindow.adsrGraph.wLogRelease(relInitAmp)))
                                          +4);
        
        if(i == 100) {
            envGraphWindow.jointPathR.addEllipse(wXYr.getX()+((330.0f/3.0f)*releasePos*i/100)-3, wXYr.getY() + (160*sustainPos*(1-envGraphWindow.adsrGraph.wLogRelease(relInitAmp)))+1, 6, 6);
        }
        relInitAmp -= 1.0f/100.0f;
    }
    
}
