/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WojtekSynthAudioProcessor::WojtekSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                  ),
tree(*this, nullptr)
#endif
{
    std::function<String (float)> valueToTextFunction = {};

    if(!valueToTextFunction)
        valueToTextFunction = [](float value){ return (String)value; };
    
    NormalisableRange<float> polyVoicesRange(1.0f, 10.0f, 1.0f);
    tree.createAndAddParameter("polyvoices", "PolyVoices", "PolyVoices", polyVoicesRange, 1.0f, valueToTextFunction, nullptr);
    
    //== O S C I L L A T O R == M I X E R ==
    NormalisableRange<float> oscChoices(0, 6);
    tree.createAndAddParameter("wavetype1", "WaveType1", "WaveTypes1", oscChoices, 0, valueToTextFunction, nullptr);
    tree.createAndAddParameter("wavetype2", "WaveType2", "WaveTypes2", oscChoices, 1, valueToTextFunction, nullptr);
 
    NormalisableRange<float> oscMixRange(-1.0f, 1.0f);
    tree.createAndAddParameter("oscmix", "OscMix", "OscMix", oscMixRange, 0, valueToTextFunction, nullptr);
    
    
    //== O S C == 2 == S E M I == P I T C H ==
    NormalisableRange<float> osc2PitchRange(-1.0f, 1.0f);
    tree.createAndAddParameter("osc2pitch", "Osc2Pitch", "Osc2Pitch", osc2PitchRange, 0.0f, valueToTextFunction, nullptr);
    
    
    //== V O I C E == E N V E L O P E ==
    NormalisableRange<float> attShapeRange(0.000000001, 0.999999999);
    tree.createAndAddParameter("attackshape", "AttackShape", "A_shape", attShapeRange, 0.55f, nullptr, nullptr);
    
    NormalisableRange<float> decShapeRange(0.000000001, 0.999999999);
    tree.createAndAddParameter("decayshape", "DecayShape", "D_shape", decShapeRange, 0.55f, nullptr, nullptr);
    
    NormalisableRange<float> relShapeRange(0.000000001, 0.999999999);
    tree.createAndAddParameter("releaseshape", "ReleaseShape", "R_shape", relShapeRange, 0.55f, nullptr, nullptr);
    
    
    NormalisableRange<float> attackRange (100.0f, 2000000.0f);
    tree.createAndAddParameter("attack", "Attack", "AtSpeed", attackRange, 100000.0f, valueToTextFunction, nullptr);
    
    NormalisableRange<float> decayRange (100.0f, 2000000.0f);
    tree.createAndAddParameter("decay", "Decay", "DeSpeed", decayRange, 1000000.0f, valueToTextFunction, nullptr);

    NormalisableRange<float> sustainRange (0.00f, 1.0f);
    tree.createAndAddParameter("sustain", "Sustain", "Amplitude", sustainRange, 1.0f, nullptr, nullptr);

    NormalisableRange<float> releaseRange (100.0f, 2000000.0f);
    tree.createAndAddParameter("release", "Release", "ReSpeed", releaseRange, 200000.0f, valueToTextFunction, nullptr);
    

    
    //== S E C O N D == E N V E L O P E ==
    NormalisableRange<float> attShapeRange_2 (0.000000001, 0.999999999);
    tree.createAndAddParameter("attackshape_2", "AttackShape_2", "A_shape_2", attShapeRange_2, 0.55f, nullptr, nullptr);
    
    NormalisableRange<float> decShapeRange_2 (0.000000001, 0.999999999);
    tree.createAndAddParameter("decayshape_2", "DecayShape_2", "D_shape_2", decShapeRange_2, 0.55f, nullptr, nullptr);
    
    NormalisableRange<float> relShapeRange_2 (0.000000001, 0.999999999);
    tree.createAndAddParameter("releaseshape_2", "ReleaseShape_2", "R_shape_2", relShapeRange_2, 0.55f, nullptr, nullptr);
    
    
    NormalisableRange<float> attackRange_2 (10.0f, 2000000.0f);
    tree.createAndAddParameter("attack_2", "Attack_2", "AtSpeed_2", attackRange_2, 100000.0f, valueToTextFunction, nullptr);
    
    NormalisableRange<float> decayRange_2 (10.0f, 2000000.0f);
    tree.createAndAddParameter("decay_2", "Decay_2", "DeSpeed_2", decayRange_2, 1000000.0f, valueToTextFunction, nullptr);
    
    NormalisableRange<float> sustainRange_2 (0.00f, 1.0f);
    tree.createAndAddParameter("sustain_2", "Sustain_2", "Amplitude_2", sustainRange_2, 1.0f, nullptr, nullptr);
    
    NormalisableRange<float> releaseRange_2 (10.0f, 2000000.0f);
    tree.createAndAddParameter("release_2", "Release_2", "ReSpeed_2", releaseRange_2, 200000.0f, valueToTextFunction, nullptr);
    
    NormalisableRange<float> env2AmounRange (0.0f, 1.0f, 0.01f);
    tree.createAndAddParameter("env2amount", "Env2Amount", "Env2Amount", env2AmounRange, 0.0f, valueToTextFunction, nullptr);
    
    
    
    //== E N V == C H O O S E R ==
    NormalisableRange<float> EnvSwitchRange(0.0f, 1.0f, 1.0f);
    tree.createAndAddParameter("envswitch", "EnvSwitch", "EnvSwitch", EnvSwitchRange, 1.0f, valueToTextFunction, nullptr);
    
    
    
    //== G A I N == S L I D E R ==
    NormalisableRange<float> gainRange(-66.0f, 0.0f);
    tree.createAndAddParameter("gain", "Gain", "Gain", gainRange, -10.0f, valueToTextFunction, nullptr);
    
    
    
    //== F I L T E R == S L I D E R S ==
    NormalisableRange<float> lowCutRange_a1(-1.0f, 1.0f);
    tree.createAndAddParameter("lowcut_a1", "LowCut_a1", "LowCut_a1", lowCutRange_a1, 1.0f, valueToTextFunction, nullptr);
    
    NormalisableRange<float> lowCutRange_a0(-1.0f, 1.0f);
    tree.createAndAddParameter("lowcut_a0", "LowCut_a0", "LowCut_a0", lowCutRange_a0, 0.0f, valueToTextFunction, nullptr);
    

    
    tree.state = ValueTree("SavedParameters");

    
    
    setPolyphonic(1);
    mojSynt.clearSounds();
    mojSynt.addSound(new WojtekSynthSound());
    

}

WojtekSynthAudioProcessor::~WojtekSynthAudioProcessor()
{
}

//==============================================================================
const String WojtekSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WojtekSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WojtekSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WojtekSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WojtekSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WojtekSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WojtekSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WojtekSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String WojtekSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void WojtekSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WojtekSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mojSynt.setCurrentPlaybackSampleRate(lastSampleRate);
    mojVoice->wBufferSize = samplesPerBlock;

    for (int i = 0; i < mojSynt.getNumVoices(); i++)
    {
        if ((mojVoice = dynamic_cast<WojtekSynthVoice*>(mojSynt.getVoice(i))))
        {
            mojVoice->wojtekSetSampleRate(sampleRate);
        }
    }
    
}

void WojtekSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WojtekSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WojtekSynthAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    if(mojVoice->wBufferSize != buffer.getNumSamples()) mojVoice->wBufferSize = buffer.getNumSamples();
    
    buffer.clear();
    
    mojSynt.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    if (wParamIsChanged == true) {
        for (int i = 0; i < mojSynt.getNumVoices(); i++)
        {
            if ((mojVoice = dynamic_cast<WojtekSynthVoice*>(mojSynt.getVoice(i))))
            {                
                
                //== O S C I L L A T O R == M I X E R ==
                mojVoice->setWaveType1(tree.getRawParameterValue("wavetype1"));
                mojVoice->setWaveType2(tree.getRawParameterValue("wavetype2"));
                mojVoice->wSetOscMix(tree.getRawParameterValue("oscmix"));
                
                
                //== O S C == 2 == S E M I == P I T C H ==
                mojVoice->wSetOsc2Pitch(tree.getRawParameterValue("osc2pitch"));
                
                
                //== V O I C E == E N V E L O P E ==
                mojVoice->setWAttackShape(tree.getRawParameterValue("attackshape"));
                mojVoice->setWDecayShape(tree.getRawParameterValue("decayshape"));
                mojVoice->setWReleaseShape(tree.getRawParameterValue("releaseshape"));
                
                mojVoice->setWAttack(tree.getRawParameterValue("attack"));
                mojVoice->setWDecay(tree.getRawParameterValue("decay"));
                mojVoice->setWSustain(tree.getRawParameterValue("sustain"));
                mojVoice->setWRelease(tree.getRawParameterValue("release"));
                
                
                //== S E C O N D == E N V E L O P E ==
                mojVoice->setWAttackShape_2(tree.getRawParameterValue("attackshape_2"));
                mojVoice->setWDecayShape_2(tree.getRawParameterValue("decayshape_2"));
                mojVoice->setWReleaseShape_2(tree.getRawParameterValue("releaseshape_2"));
                
                mojVoice->setWAttack_2(tree.getRawParameterValue("attack_2"));
                mojVoice->setWDecay_2(tree.getRawParameterValue("decay_2"));
                mojVoice->setWSustain_2(tree.getRawParameterValue("sustain_2"));
                mojVoice->setWRelease_2(tree.getRawParameterValue("release_2"));
                
                mojVoice->setWEnv_2Amount(tree.getRawParameterValue("env2amount"));
                
                //== E N V == C H O O S E R ==
                
                
                
                //== G A I N == S L I D E R ==
                mojVoice->setWGain(tree.getRawParameterValue("gain"));
                
                
                
                //== F I L T E R == S L I D E R S ==
                mojVoice->feedForward_Filter_a1(tree.getRawParameterValue("lowcut_a1"));
                mojVoice->feedForward_Filter_a0(tree.getRawParameterValue("lowcut_a0"));

            }
        }
    }
    if (wParamIsChanged == true) wParamIsChanged = false;
}

//==============================================================================
bool WojtekSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WojtekSynthAudioProcessor::createEditor()
{
    return new WojtekSynthAudioProcessorEditor (*this);
}

void WojtekSynthAudioProcessor::setPolyphonic(int poly)
{
    mojSynt.clearVoices();
    for (int i=0; i < poly; i++)
    {
        mojSynt.addVoice(new WojtekSynthVoice());
    }
    
    for (int i = 0; i < mojSynt.getNumVoices(); i++)
    {
        if ((mojVoice = dynamic_cast<WojtekSynthVoice*>(mojSynt.getVoice(i))))
        {
            mojVoice->wojtekSetSampleRate(lastSampleRate);
        }
    }

}



//==============================================================================
void WojtekSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    ScopedPointer<XmlElement> saveToXml (tree.state.createXml());
    copyXmlToBinary(*saveToXml, destData);
    
}

void WojtekSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    ScopedPointer<XmlElement> setFromXml (getXmlFromBinary(data, sizeInBytes));
    
    if (setFromXml != nullptr) {
        if (setFromXml -> hasTagName(tree.state.getType())) {
            tree.state = ValueTree::fromXml(*setFromXml);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WojtekSynthAudioProcessor();
}


