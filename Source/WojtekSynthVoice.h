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
        env1.setAttack((double)*atak);
        env2.wojtekSetAttack(*atak);
    }
    
    void setWDecay (float* decay)
    {
        env1.setDecay((double)*decay);
        env2.wojtekSetDecay(*decay);
    }

    void setWSustain (float* sustain)
    {
        env1.setSustain((double)*sustain);
        env2.wojtekSetSustain(*sustain);
    }

    void setWRelease (float* release)
    {
        env1.setRelease((double)*release);
        env2.wojtekSetRelease(*release);
    }
    
    void setWaveType (float* waveType)
    {
        theWaveType = *waveType;
    }
    
    double oscWaveType()
    {
        if (theWaveType == 0) return osc1.sinewave(frequency);
        if (theWaveType == 1) return osc1.saw(frequency);
        if (theWaveType == 2) return osc1.sawn(frequency);
        if (theWaveType == 3) return osc1.square(frequency);
        if (theWaveType == 4) return osc1.triangle(frequency);
        if (theWaveType == 5) return osc1.phasor(frequency);
        if (theWaveType == 6) return osc1.noise();
        
        else return 0.0f;
        
    }
    
    //==============================================================================

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override
    {
        level = velocity;
        env2.setTrigger(1);
        env1.trigger = 1;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
//        std::cout << maxiSettings::sampleRate << std::endl;
    }
    
    //==============================================================================

    void stopNote (float velocity, bool allowTailOff) override
    {
        env1.trigger = 0;
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

//        env1.setAttack(100.0);
//        env1.setDecay(1000.0);
//        env1.setSustain(0.8);
//        env1.setRelease(50.0);
        
        

        for (int sample=0; sample < numSamples; ++sample)
        {
//            double theSinus = osc1.sinewave(frequency);
//            double theSquere = osc2.square(frequency);

//            double theSinSound = env1.adsr(theSinus, env1.trigger) * level;
//            outputBuffer.addSample(0, startSample, theSinSound);

//            double theSquSound = env1.adsr(theSquere, env1.trigger) * level;
//            outputBuffer.addSample(0, startSample, theSquSound);
   
//            if (dupa == 0) { dupa = 1; std::cout << " SZAMBO " << std::endl; }
            float wojtekSound = env2.wojtekADSR((float)oscWaveType(), env2.getTrigger());
            outputBuffer.addSample(0, startSample, wojtekSound);
            

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
    
    maxiEnv env1;
    WojtekEnvelope env2;
//    WojtekSynthOscillators 
private:
    double level;
    double frequency;
    int theWaveType;

    maxiOsc osc1;
    maxiOsc osc2;
    int dupa = 0;
};
