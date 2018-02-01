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
    NormalisableRange<float> attackRange (2500.0f, 2000000.0f);
    tree.createAndAddParameter("attack", "Attack", "Speed", attackRange, 100000.0f, nullptr, nullptr);
    
    NormalisableRange<float> decayRange (2500.0f, 2000000.0f);
    tree.createAndAddParameter("decay", "Decay", "Speed", decayRange, 1000000.0f, nullptr, nullptr);

    NormalisableRange<float> sustainRange (0.00f, 1.0f);
    tree.createAndAddParameter("sustain", "Sustain", "Amplitude", sustainRange, 1.0f, nullptr, nullptr);

    NormalisableRange<float> releaseRange (2500.0f, 2000000.0f);
    tree.createAndAddParameter("release", "Release", "Speed", releaseRange, 200000.0f, nullptr, nullptr);
    
    NormalisableRange<float> attShapeRange(0.000000001, 0.999999999);
    tree.createAndAddParameter("attackshape", "AttackShape", "A_shape", attShapeRange, 0.55f, nullptr, nullptr);
    
    NormalisableRange<float> decShapeRange(0.000000001, 0.999999999);
    tree.createAndAddParameter("decayshape", "DecayShape", "D_shape", decShapeRange, 0.55f, nullptr, nullptr);
    
    NormalisableRange<float> relShapeRange(0.000000001, 0.999999999);
    tree.createAndAddParameter("releaseshape", "ReleaseShape", "R_shape", relShapeRange, 0.55f, nullptr, nullptr);
    
    NormalisableRange<float> oscChoices(0, 5);
    tree.createAndAddParameter("wavetype1", "WaveType1", "WaveTypes1", oscChoices, 0, nullptr, nullptr);
    tree.createAndAddParameter("wavetype2", "WaveType2", "WaveTypes2", oscChoices, 1, nullptr, nullptr);
    
    NormalisableRange<float> oscMixRange(-1.0f, 1.0f);
    tree.createAndAddParameter("oscmix", "OscMix", "OscMix", oscMixRange, 0, nullptr, nullptr);
    
    NormalisableRange<float> gainRange(-66.0f, 0.0f);
    tree.createAndAddParameter("gain", "Gain", "Gain", gainRange, -10.0f, nullptr, nullptr);
    
    NormalisableRange<float> lowCutRange_a1(-1.0f, 1.0f);
    tree.createAndAddParameter("lowcut_a1", "LowCut_a1", "LowCut_a1", lowCutRange_a1, 1.0f, nullptr, nullptr);
    
    NormalisableRange<float> lowCutRange_a0(-1.0f, 1.0f);
    tree.createAndAddParameter("lowcut_a0", "LowCut_a0", "LowCut_a0", lowCutRange_a0, 0.0f, nullptr, nullptr);
    
    NormalisableRange<float> osc2PitchRange(440.0f/466.16377f, 466.16377f/440.0f);
    tree.createAndAddParameter("osc2pitch", "Osc2Pitch", "Osc2Pitch", osc2PitchRange, 1.0f, nullptr, nullptr);
    
    mojSynt.clearVoices();
    
    for (int i=0; i < 20; i++)
    {
        mojSynt.addVoice(new WojtekSynthVoice());
    }
    
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
    buffer.clear();
    
    mojSynt.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    if (wParamIsChanged == true) {
        for (int i = 0; i < mojSynt.getNumVoices(); i++)
        {
            if ((mojVoice = dynamic_cast<WojtekSynthVoice*>(mojSynt.getVoice(i))))
            {
                mojVoice->wSetOsc2Pitch(tree.getRawParameterValue("osc2pitch"));
               
                mojVoice->feedForward_Filter_a1(tree.getRawParameterValue("lowcut_a1"));
                mojVoice->feedForward_Filter_a0(tree.getRawParameterValue("lowcut_a0"));
                
                mojVoice->setWAttack(tree.getRawParameterValue("attack"));
                mojVoice->setWDecay(tree.getRawParameterValue("decay"));
                mojVoice->setWSustain(tree.getRawParameterValue("sustain"));
                mojVoice->setWRelease(tree.getRawParameterValue("release"));
                
                mojVoice->wSetOscMix(tree.getRawParameterValue("oscmix"));
                
                mojVoice->setWaveType1(tree.getRawParameterValue("wavetype1"));
                mojVoice->setWaveType2(tree.getRawParameterValue("wavetype2"));
                mojVoice->setWAttackShape(tree.getRawParameterValue("attackshape"));
                mojVoice->setWDecayShape(tree.getRawParameterValue("decayshape"));
                mojVoice->setWReleaseShape(tree.getRawParameterValue("releaseshape"));
                
                mojVoice->setWGain(tree.getRawParameterValue("gain"));
            }
        }
    }
    if (wParamIsChanged != false) wParamIsChanged = false;
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

//==============================================================================
void WojtekSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WojtekSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WojtekSynthAudioProcessor();
}
