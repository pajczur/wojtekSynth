/*
  ==============================================================================

    WojtekSynthVoice.h
    Created: 3 Jan 2018 10:26:18pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "WojtekSynthSound.h"
#include "maximilian.h"
#include "WojtekSynthEnvelope.h"

class WojtekSynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound *sound) override
    {
        return dynamic_cast<WojtekSynthSound*>(sound) != nullptr;
    }
    
    //==============================================================================
    
    void setWAttack (float* atak)
    {
        env2.wojtekSetAttack(*atak);
    }
    
    void setWAttackShape(float* curveParam)
    {
        env2.wLogAttackManip(*curveParam);
    }
    
    //==============================================================================
    
    
    void setWDecay (float* decay)
    {
        env2.wojtekSetDecay(*decay);
    }

    void setWSustain (float* sustain)
    {
        env2.wojtekSetSustain(*sustain);
    }
    
    void setWDecayShape(float* curveParam)
    {
        env2.wLogDecayManip(*curveParam);
    }
    
    //==============================================================================

    void setWRelease (float* release)
    {
        env2.wojtekSetRelease(*release);
    }
    
    void setWReleaseShape(float* curveParam)
    {
        env2.wLogReleaseManip(*curveParam);
    }
    
    //==============================================================================
    
    void setMix (float* mix)
    {
        if (*mix>=(-1) && *mix<=1) {
            osc1Mix = 1 - (1 + *mix)/2;
            osc2Mix = 1 + (*mix - 1)/2;
        } else if (*mix<(-1)) {
            osc1Mix = 1;
            osc2Mix = 0;
        } else {
            osc1Mix = 0;
            osc2Mix = 1;
        }
    }
    
    void setWaveType1 (float* waveType)
    {
        theWaveType1 = *waveType;
    }
    
    double oscWaveType1()
    {
        if (theWaveType1 == 0) return (double)osc1Mix*osc1.sinewave(frequency);
        if (theWaveType1 == 1) return (double)osc1Mix*osc1.saw(frequency);
        if (theWaveType1 == 2) return (double)osc1Mix*osc1.square(frequency);
        if (theWaveType1 == 3) return (double)osc1Mix*osc1.triangle(frequency);
        if (theWaveType1 == 4) return (double)osc1Mix*osc1.phasor(frequency);
        if (theWaveType1 == 5) return (double)osc1Mix*osc1.noise();
        
        else return 0.0f;
    }
    
    
    void setWaveType2 (float* waveType)
    {
        theWaveType2 = *waveType;
    }
    
    double oscWaveType2()
    {
        if (theWaveType2 == 0) return (double)osc2Mix*osc2.sinewave(frequency);
        if (theWaveType2 == 1) return (double)osc2Mix*osc2.saw(frequency);
        if (theWaveType2 == 2) return (double)osc2Mix*osc2.square(frequency);
        if (theWaveType2 == 3) return (double)osc2Mix*osc2.triangle(frequency);
        if (theWaveType2 == 4) return (double)osc2Mix*osc2.phasor(frequency);
        if (theWaveType2 == 5) return (double)osc2Mix*osc2.noise();
        
        else return 0.0f;
    }
    
    //==============================================================================
    
    void setWGain (float* gain)
    {
        env2.wojtekSetGain(*gain);
    }
    
    //==============================================================================

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override
    {
        level = velocity;
        env2.setTrigger(1);
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    //==============================================================================

    void stopNote (float velocity, bool allowTailOff) override
    {
        env2.setTrigger(0);
        allowTailOff = true;

//        if (velocity == 0)
//        {
//            clearCurrentNote();
//        }
    }
    
    //==============================================================================
    
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override
    {

        for (int sample=0; sample < numSamples; ++sample)
        {

            float wojtekSound = env2.wojtekADSR((float)oscWaveType1()+(float)oscWaveType2(), env2.getTrigger());
           
            for(int channel = 0; channel<outputBuffer.getNumChannels(); ++channel) {
                outputBuffer.addSample(channel, startSample, wojtekSound);
            }

            ++startSample;
        }
        
    }
    
    //==============================================================================

    void pitchWheelMoved (int newPitchWheelValue) override
    {

    }
    
    //==============================================================================

    void controllerMoved (int controllerNumber, int newControllerValue) override
    {

    }
    
    //==============================================================================
    

private:
    WojtekSynthEnvelope env2;
    double extSampRat;
    double level;
    double frequency;
    int theWaveType1;
    int theWaveType2;
    double osc1Mix;
    double osc2Mix;

    maxiOsc osc1;
    maxiOsc osc2;
    int dupa = 0;
};
