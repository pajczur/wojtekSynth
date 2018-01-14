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
attackTree(*this, nullptr),
decayTree(*this, nullptr),
sustainTree(*this, nullptr),
releaseTree(*this, nullptr)
#endif
{
    NormalisableRange<float> attackRange (500.0f, 2000000.0f);
    attackTree.createAndAddParameter("attack", "Attack", "Speed", attackRange, 1000000.0f, nullptr, nullptr);
    
    NormalisableRange<float> decayRange (500.0f, 10000000.0f);
    decayTree.createAndAddParameter("decay", "Decay", "Speed", decayRange, 120000.0f, nullptr, nullptr);

    NormalisableRange<float> sustainRange (0.00f, 1.0f);
    sustainTree.createAndAddParameter("sustain", "Sustain", "Amplitude", sustainRange, 1.0f, nullptr, nullptr);

    NormalisableRange<float> releaseRange (500.0f, 2000000.0f);
    releaseTree.createAndAddParameter("release", "Release", "Speed", releaseRange, 1000000.0f, nullptr, nullptr);
    
    
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

    for (int i = 0; i < mojSynt.getNumVoices(); i++)
    {
        if ((mojVoice = dynamic_cast<WojtekSynthVoice*>(mojSynt.getVoice(i))))
        {
            mojVoice->setWAttack(attackTree.getRawParameterValue("attack"));
            mojVoice->setWDecay(decayTree.getRawParameterValue("decay"));
            mojVoice->setWSustain(sustainTree.getRawParameterValue("sustain"));
            mojVoice->setWRelease(releaseTree.getRawParameterValue("release"));
            
        }
    }

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
