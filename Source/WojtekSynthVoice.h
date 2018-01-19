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
    
    void setWAttackShape(float* curveParam)
    {
        env2.wLogAttackManip(*curveParam);
    }
    
    //==============================================================================
    
    
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
    
    void setWDecayShape(float* curveParam)
    {
        env2.wLogDecayManip(*curveParam);
    }
    
    //==============================================================================

    void setWRelease (float* release)
    {
        env1.setRelease((double)*release);
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
//        std::cout << "osc1: " << osc1Mix << ";    osc2: " << osc2Mix << std::endl;
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
            float wojtekSound = env2.wojtekADSR((float)oscWaveType1()+(float)oscWaveType2(), env2.getTrigger());
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
    int theWaveType1;
    int theWaveType2;
    double osc1Mix;
    double osc2Mix;

    maxiOsc osc1;
    maxiOsc osc2;
    int dupa = 0;
};
