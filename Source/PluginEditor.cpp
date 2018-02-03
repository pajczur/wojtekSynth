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
    : AudioProcessorEditor (&p), processor (p), setOsc1(p), setOsc2(p), envGraphWindow(0), envGraphWindow_2(1)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (775+120, 500);
 
    polyVoicesL.setText("polyphonic", dontSendNotification);
    polyVoicesL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&polyVoicesL);
    polyVoicesL.attachToComponent(&polyVoices, false);
    polyVoices.setSliderStyle(Slider::SliderStyle::IncDecButtons);
//    polyVoices.setRange(1.0, 10.0, 1.0);
    polyVoices.setTextBoxStyle(Slider::TextBoxLeft, true, 30, 20);
    polyVoices.addListener(this);
    addAndMakeVisible(&polyVoices);
    polyVoicesAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "polyvoices", polyVoices);
    
    
//== O S C I L L A T O R == M I X E R ====================================================================================================
    
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
    oscMixSlider.addListener(this);
    addAndMakeVisible(&oscMixSlider);
    oscMixAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "oscmix", oscMixSlider);

    addAndMakeVisible(&setOsc1);
    setOsc1Attache = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype1", setOsc1.osc1Menu);
    addAndMakeVisible(&setOsc2);
    setOsc2Attache = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype2", setOsc2.osc1Menu);
    
//== O S C == 2 == S E M I == P I T C H ==========================================================================================
    setOsc2Pitch.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    setOsc2Pitch.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 25);
    setOsc2Pitch.setRange(-1.0f, 1.0f);
    setOsc2Pitch.addListener(this);
    addAndMakeVisible(&setOsc2Pitch);
    osc2PitchAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc2pitch", setOsc2Pitch);
    
    
    
    
    
//== V O I C E == E N V E L O P E ===================================================================================================
    //== S H A P E R S ==
    attackSL.setText("A. shape - ENV. 1", dontSendNotification);
    attackSL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&attackSL);
    attackSL.attachToComponent(&attackShape, false);
    attackShape.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    attackShape.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    attackShape.setRange(0.000000001, 0.999999999);
    attackShape.addListener(this);
    addAndMakeVisible(&attackShape);
    attackShapeAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attackshape", attackShape);
    
    decaySL.setText("D. shape - ENV. 1", dontSendNotification);
    decaySL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&decaySL);
    decaySL.attachToComponent(&decayShape, false);
    decayShape.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    decayShape.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    decayShape.setRange(0.000000001, 0.999999999);
    decayShape.addListener(this);
    addAndMakeVisible(&decayShape);
    decayShapeAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decayshape", decayShape);
    
    releaseSL.setText("R. shape - ENV. 1", dontSendNotification);
    releaseSL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&releaseSL);
    releaseSL.attachToComponent(&releaseShape, false);
    releaseShape.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    releaseShape.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    releaseShape.setRange(0.000000001, 0.999999999);
    releaseShape.addListener(this);
    addAndMakeVisible(&releaseShape);
    releaseShapeAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "releaseshape", releaseShape);
    
    //== T I M I N G ==
    attackL.setText("wAttack - ENV. 1", dontSendNotification);
    attackL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&attackL);
    attackL.attachToComponent(&attackSlider, false);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
//    attackSlider.setRange(2500.0f, 2000000.0f);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    attackSlider.setTextValueSuffix(" ms");
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    attackAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    
    decayL.setText("wDecay - ENV. 1", dontSendNotification);
    decayL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&decayL);
    decayL.attachToComponent(&decaySlider, false);
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
//    decaySlider.setRange(2500.0f, 2000000.0f);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    decaySlider.setTextValueSuffix(" ms");
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);
    decayAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    
    sustainL.setText("wSustain - ENV. 1", dontSendNotification);
    sustainL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&sustainL);
    sustainL.attachToComponent(&sustainSlider, false);
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    sustainSlider.setTextValueSuffix(" dB");
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);
    sustainAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    
    releaseL.setText("wRelease - ENV. 1", dontSendNotification);
    releaseL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&releaseL);
    releaseL.attachToComponent(&releaseSlider, false);
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
//    releaseSlider.setRange(2500.0f, 2000000.0f);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    releaseSlider.setTextValueSuffix(" ms");
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    releaseAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);
    
    
    
    
    //== S E C O N D == E N V E L O P E ===================================================================================================
    //== S H A P E R S == 2
    attackSL_2.setText("A. shape - ENV. 2", dontSendNotification);
    attackSL_2.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&attackSL_2);
    attackSL_2.attachToComponent(&attackShape_2, false);
    attackShape_2.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    attackShape_2.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    attackShape_2.setRange(0.000000001, 0.999999999);
    attackShape_2.addListener(this);
    addAndMakeVisible(&attackShape_2);
    attackShapeAttache_2 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attackshape_2", attackShape_2);
    
    decaySL_2.setText("D. shape - ENV. 2", dontSendNotification);
    decaySL_2.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&decaySL_2);
    decaySL_2.attachToComponent(&decayShape_2, false);
    decayShape_2.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    decayShape_2.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    decayShape_2.setRange(0.000000001, 0.999999999);
    decayShape_2.addListener(this);
    addAndMakeVisible(&decayShape_2);
    decayShapeAttache_2 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decayshape_2", decayShape_2);
    
    releaseSL_2.setText("R. shape - ENV. 2", dontSendNotification);
    releaseSL_2.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&releaseSL_2);
    releaseSL_2.attachToComponent(&releaseShape_2, false);
    releaseShape_2.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    releaseShape_2.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    releaseShape_2.setRange(0.000000001, 0.999999999);
    releaseShape_2.addListener(this);
    addAndMakeVisible(&releaseShape_2);
    releaseShapeAttache_2 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "releaseshape_2", releaseShape_2);
    
    //== T I M I N G == 2
    attackL_2.setText("wAttack - ENV. 2", dontSendNotification);
    attackL_2.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&attackL_2);
    attackL_2.attachToComponent(&attackSlider_2, false);
    attackSlider_2.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
//    attackSlider_2.setRange(2500.0f, 2000000.0f);
    attackSlider_2.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    attackSlider_2.setTextValueSuffix(" ms");
    attackSlider_2.addListener(this);
    addAndMakeVisible(&attackSlider_2);
    attackAttache_2 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack_2", attackSlider_2);
    
    decayL_2.setText("wDecay - ENV. 2", dontSendNotification);
    decayL_2.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&decayL_2);
    decayL_2.attachToComponent(&decaySlider_2, false);
    decaySlider_2.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
//    decaySlider_2.setRange(2500.0f, 2000000.0f);
    decaySlider_2.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    decaySlider_2.setTextValueSuffix(" ms");
    decaySlider_2.addListener(this);
    addAndMakeVisible(&decaySlider_2);
    decayAttache_2 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay_2", decaySlider_2);
    
    sustainL_2.setText("wSustain - ENV. 2", dontSendNotification);
    sustainL_2.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&sustainL_2);
    sustainL_2.attachToComponent(&sustainSlider_2, false);
    sustainSlider_2.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    sustainSlider_2.setRange(0.0f, 1.0f);
    sustainSlider_2.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    sustainSlider_2.setTextValueSuffix(" dB");
    sustainSlider_2.addListener(this);
    addAndMakeVisible(&sustainSlider_2);
    sustainAttache_2 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain_2", sustainSlider_2);
    
    releaseL_2.setText("wRelease - ENV. 2", dontSendNotification);
    releaseL_2.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&releaseL_2);
    releaseL_2.attachToComponent(&releaseSlider_2, false);
    releaseSlider_2.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
//    releaseSlider_2.setRange(2500.0f, 2000000.0f);
    releaseSlider_2.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    releaseSlider_2.setTextValueSuffix(" ms");
    releaseSlider_2.addListener(this);
    addAndMakeVisible(&releaseSlider_2);
    releaseAttache_2 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release_2", releaseSlider_2);
    
    //== E N V == 2 == A M O U N T ============================================================================================
    env2AmountSliderL.setText("Env 2 gain", dontSendNotification);
    env2AmountSliderL.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&env2AmountSliderL);
    env2AmountSliderL.attachToComponent(&env2AmountSlider, false);
    env2AmountSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    env2AmountSlider.setRange(-1.0f, 1.0f);
    env2AmountSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 25);
    env2AmountSlider.addListener(this);
    addAndMakeVisible(&env2AmountSlider);
    env2AmountSliderAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "env2amount", env2AmountSlider);
    
    
    
//== E N V == C H O O S E R ====================================================================================================
    wojtekEnvelopeSwitch.setTextBoxStyle(Slider::NoTextBox, false, 50, 25);
    wojtekEnvelopeSwitch.setSliderStyle(Slider::SliderStyle::LinearVertical);
    wojtekEnvelopeSwitch.addListener(this);
    addAndMakeVisible(&wojtekEnvelopeSwitch);
    EnvSwitchAttache = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "envswitch", wojtekEnvelopeSwitch);
    


//== G A I N == S L I D E R ====================================================================================================
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
    
    
//== F I L T E R == S L I D E R S ===============================================================================================
    lowCutA1L.setText("a1 coeff.", dontSendNotification);
    lowCutA1L.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&lowCutA1L);
    lowCutA1L.attachToComponent(&lowCutSliderA1, false);
    lowCutSliderA1.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    lowCutSliderA1.setRange(-1.0, 1.0);
    lowCutSliderA1.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 25);
    lowCutSliderA1.addListener(this);
    addAndMakeVisible(&lowCutSliderA1);
    lowCutAttache_a1 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "lowcut_a1", lowCutSliderA1);
    
    lowCutA0L.setText("a0 coeff.", dontSendNotification);
    lowCutA0L.setJustificationType(Justification::centredBottom);
    addAndMakeVisible(&lowCutA0L);
    lowCutA0L.attachToComponent(&lowCutSliderA0, false);
    lowCutSliderA0.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    lowCutSliderA0.setRange(-1.0, 1.0);
    lowCutSliderA0.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 25);
    lowCutSliderA0.addListener(this);
    addAndMakeVisible(&lowCutSliderA0);
    lowCutAttache_a0 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "lowcut_a0", lowCutSliderA0);
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
    g.drawText("Env 1", 400+350+10, 68+25, 40, 10, Justification::centredTop);
    g.drawText("Env 2", 400+350+10, 75+33+25, 40, 10, Justification::centredTop);
}

void WojtekSynthAudioProcessorEditor::resized()
{
    polyVoices.setBounds(400+350+30, 20, 100, 20);
    
    setOsc1.setMenuBounds(150, 35);
    setOsc2.setMenuBounds(100, 35);
    setOsc1.setBounds(350+((350-200)/2)-3, 440-20, setOsc1.oscMenuBoundX, setOsc1.oscMenuBoundY);
    setOsc2.setBounds(500+((350-200)/2)-3, 440-20, setOsc2.oscMenuBoundX, setOsc2.oscMenuBoundY);
    oscMixSlider.setBounds(417, 325+65-20, 310, 50);
    
    setOsc2Pitch.setBounds(600+((350-200)/2)-3, 410, 80, 80);
    
    
    
    attackShape.setBounds(420, 250, 75, 70);
    decayShape.setBounds(530, 250, 75, 70);
    releaseShape.setBounds(640, 250, 75, 70);
    
    attackSlider.setBounds(50, 25, 300, 50);
    decaySlider.setBounds(50, 125-5, 300, 50);
    sustainSlider.setBounds(50, 225-(2*5), 300, 50);
    releaseSlider.setBounds(50, 325-(3*5), 300, 50);
    
    
    attackShape_2.setBounds(420, 250, 75, 70);
    decayShape_2.setBounds(530, 250, 75, 70);
    releaseShape_2.setBounds(640, 250, 75, 70);
    
    attackSlider_2.setBounds(50, 25, 300, 50);
    decaySlider_2.setBounds(50, 125-5, 300, 50);
    sustainSlider_2.setBounds(50, 225-(2*5), 300, 50);
    releaseSlider_2.setBounds(50, 325-(3*5), 300, 50);
    
    
    
    
    wojtekEnvelopeSwitch.setBounds(400+350+20, 50+25+30, 20, 30);
    env2AmountSlider.setBounds(400+350+25+30, 50+25+15, 80, 80);
    envGraphWindow.setBounds(400, 25, envGraphWindow.getWidth(), envGraphWindow.getHeight());
    envGraphWindow_2.setBounds(400, 25, envGraphWindow.getWidth(), envGraphWindow.getHeight());
    
    
    gainSlider.setBounds(50, 400, 70, 70);
    
    lowCutSliderA0.setBounds(160, 380, 90, 90);
    lowCutSliderA1.setBounds(240, 380, 90, 90);
}



//=== S L I D E R == V A L U E == C H A N G E D ========================================================

void WojtekSynthAudioProcessorEditor::sliderValueChanged (Slider *slider)
{
    //== V O I C E == E N V == S H A P E R ==
    if(slider == &attackShape || slider == &attackSlider) {
        envGraphWindow.drawAttack(attackSlider.getValue(), attackSlider.getMaximum(), attackShape.getValue(), 1.0);
        envGraphWindow.drawDecay(decaySlider.getValue(), decaySlider.getMaximum(), decayShape.getValue(), sustainSlider.getValue(), 1.0);
        envGraphWindow.drawRelease(releaseSlider.getValue(), releaseSlider.getMaximum(), releaseShape.getValue(), sustainSlider.getValue(), 1.0);
        envGraphWindow.repaint();
        
        processor.wParamIsChanged = true;
    }

    if(slider == &decayShape || slider == &decaySlider || slider == &sustainSlider) {
        envGraphWindow.drawDecay(decaySlider.getValue(), decaySlider.getMaximum(), decayShape.getValue(), sustainSlider.getValue(), 1.0);
        envGraphWindow.drawRelease(releaseSlider.getValue(), releaseSlider.getMaximum(), releaseShape.getValue(), sustainSlider.getValue(), 1.0);
        envGraphWindow.repaint();
        
        processor.wParamIsChanged = true;
    }
    
    if(slider == &releaseShape || slider == &releaseSlider) {
        envGraphWindow.drawRelease(releaseSlider.getValue(), releaseSlider.getMaximum(), releaseShape.getValue(), sustainSlider.getValue(), 1.0);
        envGraphWindow.repaint();
        
        processor.wParamIsChanged = true;
    }
    
    
    
    //== E N V == 2 == S H A P E R ==
    if(slider == &attackShape_2 || slider == &attackSlider_2 || slider == &env2AmountSlider) {
        envGraphWindow_2.drawAttack(attackSlider_2.getValue(), attackSlider_2.getMaximum(), attackShape_2.getValue(), env2AmountSlider.getValue());
        envGraphWindow_2.drawDecay(decaySlider_2.getValue(), decaySlider_2.getMaximum(), decayShape_2.getValue(), sustainSlider_2.getValue(), env2AmountSlider.getValue());
        envGraphWindow_2.drawRelease(releaseSlider_2.getValue(), releaseSlider_2.getMaximum(), releaseShape_2.getValue(), sustainSlider_2.getValue(), env2AmountSlider.getValue());
        envGraphWindow_2.repaint();
        
        processor.wParamIsChanged = true;
    }
    
    if(slider == &decayShape_2 || slider == &decaySlider_2 || slider == &sustainSlider_2) {
        envGraphWindow_2.drawDecay(decaySlider_2.getValue(), decaySlider_2.getMaximum(), decayShape_2.getValue(), sustainSlider_2.getValue(), env2AmountSlider.getValue());
        envGraphWindow_2.drawRelease(releaseSlider_2.getValue(), releaseSlider_2.getMaximum(), releaseShape_2.getValue(), sustainSlider_2.getValue(), env2AmountSlider.getValue());
        envGraphWindow_2.repaint();
        
        processor.wParamIsChanged = true;
    }
    
    if(slider == &releaseShape_2 || slider == &releaseSlider_2) {
        envGraphWindow_2.drawRelease(releaseSlider_2.getValue(), releaseSlider_2.getMaximum(), releaseShape_2.getValue(), sustainSlider_2.getValue(), env2AmountSlider.getValue());
        envGraphWindow_2.repaint();
        
        processor.wParamIsChanged = true;
    }
    
    
    
    if(slider == &oscMixSlider || slider == &gainSlider || slider == &lowCutSliderA1 ||
       slider == &lowCutSliderA0 || slider == &setOsc2Pitch || slider == &env2AmountSlider || slider == &polyVoices) {
        processor.wParamIsChanged = true;
        
        if(slider == &polyVoices) {
            processor.setPolyphonic((int)polyVoices.getValue());
        }
    }
    
    if(slider == &wojtekEnvelopeSwitch) {
        if(wojtekEnvelopeSwitch.getValue() == 1) {
            envGraphWindow_2.setVisible(false);
            attackShape_2.setVisible(false);
            decayShape_2.setVisible(false);
            releaseShape_2.setVisible(false);
            
            attackSlider_2.setVisible(false);
            decaySlider_2.setVisible(false);
            sustainSlider_2.setVisible(false);
            releaseSlider_2.setVisible(false);
            env2AmountSlider.setVisible(false);
            
            
            addAndMakeVisible(&envGraphWindow);
            addAndMakeVisible(&attackShape);
            addAndMakeVisible(&decayShape);
            addAndMakeVisible(&releaseShape);
            
            addAndMakeVisible(&attackSlider);
            addAndMakeVisible(&decaySlider);
            addAndMakeVisible(&sustainSlider);
            addAndMakeVisible(&releaseSlider);
        }
        
        if(wojtekEnvelopeSwitch.getValue() == 0) {
            envGraphWindow.setVisible(false);
            attackShape.setVisible(false);
            decayShape.setVisible(false);
            releaseShape.setVisible(false);
            
            attackSlider.setVisible(false);
            decaySlider.setVisible(false);
            sustainSlider.setVisible(false);
            releaseSlider.setVisible(false);
            
            addAndMakeVisible(&envGraphWindow_2);
            addAndMakeVisible(&attackShape_2);
            addAndMakeVisible(&decayShape_2);
            addAndMakeVisible(&releaseShape_2);
            
            addAndMakeVisible(&attackSlider_2);
            addAndMakeVisible(&decaySlider_2);
            addAndMakeVisible(&sustainSlider_2);
            addAndMakeVisible(&releaseSlider_2);
            addAndMakeVisible(&env2AmountSlider);
        }
    }
}
