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
    
    void wojtekSetSampleRate (double extSampleRate)
    {
        wVoiceEnv.wSampleRate = extSampleRate;
        wEnvelope_2.wSampleRate = extSampleRate;
    }
    
    int wSetPoly (int voicesQ)
    {
        return voicesQ;
    }
    
    
    
    
    //=== W A V E == O S C I L L A T O R == 1 ===
    void setWaveType1 (float* waveType)
    {
        wVoiceWaveType1 = *waveType;
    }
    
    double oscWaveType1()
    {
        
        
        if (wVoiceWaveType1 == 0) return (double)wVoiceOsc1Mix*mOsc1.sinewave(wVoiceFreq * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType1 == 1) return (double)wVoiceOsc1Mix*mOsc1.saw(wVoiceFreq * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType1 == 2) return (double)wVoiceOsc1Mix*mOsc1.square(wVoiceFreq * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType1 == 3) return (double)wVoiceOsc1Mix*mOsc1.triangle(wVoiceFreq * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType1 == 4) return (double)wVoiceOsc1Mix*mOsc1.phasor(wVoiceFreq * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType1 == 5) return (double)wVoiceOsc1Mix*mOsc1.noise();
        if (wVoiceWaveType1 == 6) return mOsc1.impulse(wBufferSize);
        
        else return 0.0f;
    }
    
    
    //=== W A V E == O S C I L L A T O R == 2 ===
    void setWaveType2 (float* waveType)
    {
        wVoiceWaveType2 = *waveType;
    }
    
    double oscWaveType2()
    {
        
        if (wVoiceWaveType2 == 0) return (double)wVoiceOsc2Mix*mOsc2.sinewave(wVoiceFreq * wOsc2Pitch * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType2 == 1) return (double)wVoiceOsc2Mix*mOsc2.saw(wVoiceFreq * wOsc2Pitch * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType2 == 2) return (double)wVoiceOsc2Mix*mOsc2.square(wVoiceFreq * wOsc2Pitch * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType2 == 3) return (double)wVoiceOsc2Mix*mOsc2.triangle(wVoiceFreq * wOsc2Pitch * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType2 == 4) return (double)wVoiceOsc2Mix*mOsc2.phasor(wVoiceFreq * wOsc2Pitch * (1+(7*wojtekEnvelope_2)));
        if (wVoiceWaveType2 == 5) return (double)wVoiceOsc2Mix*mOsc2.noise();
        if (wVoiceWaveType2 == 6) return mOsc1.impulse(wBufferSize);
        
        else return 0.0f;
    }
    
    
    //=== O S C I L L A T O R S =====================================================
    //===  M I X E R ===
    void wSetOscMix (float* mix)
    {
        if (*mix>=(-1) && *mix<=1) {
            wVoiceOsc1Mix = 1 - (1 + *mix)/2;
            wVoiceOsc2Mix = 1 + (*mix - 1)/2;
        } else if (*mix<(-1)) {
            wVoiceOsc1Mix = 1;
            wVoiceOsc2Mix = 0;
        } else {
            wVoiceOsc1Mix = 0;
            wVoiceOsc2Mix = 1;
        }
    }
    
    
    
    
    //== O S C == 2 == S E M I == P I T C H ========================================
    void wSetOsc2Pitch (float* wPitch)
    {

//        wOsc2Pitch = 1 * pow(466.16377/440.0, *wPitch);
        
        if(*wPitch >= 0) {
            wOsc2Pitch = 1.0 + (3.0 * *wPitch);
        } else {
            wOsc2Pitch = 1.0 + (0.75 * *wPitch);
        }
    }
    
    
    

    
    //===  S E T == V O I C E == E N V E L O P E ====================================
    //===  A T T A C K ===
    
    void setWAttack (float* atak)
    {
        wVoiceEnv.wojtekSetAttack(*atak);
    }
    
    void setWAttackShape(float* curveParam)
    {
        wVoiceEnv.wLogAttackManip(*curveParam);
    }
    
    //===  D E C A Y ===
    
    
    void setWDecay (float* decay)
    {
        wVoiceEnv.wojtekSetDecay(*decay);
    }

    void setWSustain (float* sustain)
    {
        wVoiceEnv.wojtekSetSustain(*sustain);
    }
    
    void setWDecayShape(float* curveParam)
    {
        wVoiceEnv.wLogDecayManip(*curveParam);
    }
    
    //===  R E L E A S E ===

    void setWRelease (float* release)
    {
        wVoiceEnv.wojtekSetRelease(*release);
    }
    
    void setWReleaseShape(float* curveParam)
    {
        wVoiceEnv.wLogReleaseManip(*curveParam);
    }
    
    
    //===  S E T == E N V E L O P E == 2 ==================================
    //=== A T T A C K == _2 ===
    void setWAttack_2 (float* atak)
    {
        wEnvelope_2.wojtekSetAttack(*atak);
    }

    void setWAttackShape_2(float* curveParam)
    {
        wEnvelope_2.wLogAttackManip(*curveParam);
    }

    //=== D E C A Y == _2 ===
    void setWDecay_2 (float* decay)
    {
        wEnvelope_2.wojtekSetDecay(*decay);
    }

    void setWSustain_2 (float* sustain)
    {
        wEnvelope_2.wojtekSetSustain(*sustain);
    }

    void setWDecayShape_2(float* curveParam)
    {
        wEnvelope_2.wLogDecayManip(*curveParam);
    }

    //=== R E L E A S E == _2 ===

    void setWRelease_2 (float* release)
    {
        wEnvelope_2.wojtekSetRelease(*release);
    }

    void setWReleaseShape_2(float* curveParam)
    {
        wEnvelope_2.wLogReleaseManip(*curveParam);
    }
    
    void setWEnv_2Amount (float* gain)
    {
        wEnvelope_2.wojtekSetLinearGain(*gain);
    }
    
    

    

    
    
    //==== G A I N =================================================================
    
    void setWGain (float* gain)
    {
        wVoiceEnv.wojtekSetGain(*gain);
    }
    
    
    //=== L O W == C U T == F I L T E R ============================================
    //=== FEED-FORWARD ====================
    //=== FEED-FORWARD I ===
//    void feedForward_Filter_a1 (float* filterFF)
//    {
//        a1_left = *filterFF;
//        a0_left = a1_left - 1.0f;
//    }
    
    //=== FEED-FORWARD II ===
    void feedForward_Filter_a1 (float* filterFF_a1_Slider)
    {
        a1_left = *filterFF_a1_Slider;
    }

    void feedForward_Filter_a0 (float* filterFF_a0_Slider)
    {
        a0_left = *filterFF_a0_Slider;
    }
    
    //=== FEED-BACKWARD ====================
    
    
    
    
    
    //==============================================================================

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override
    {
        wVoiceLevel = velocity;
        wVoiceEnv.setTrigger(1);
        wVoiceFreq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    
    //==============================================================================

    void stopNote (float velocity, bool allowTailOff) override
    {
        wVoiceEnv.setTrigger(0);
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
            wojtekEnvelope_2 = wEnvelope_2.wojtekADSR(1.0f, wVoiceEnv.getTrigger());

            float wojtekSound = wVoiceEnv.wojtekADSR((float)oscWaveType1()+(float)oscWaveType2(), wVoiceEnv.getTrigger());
            float xn_left = wojtekSound;
            
            float xn_1_left = z1_left;
            
            float yn_left;
//            float xn_1 = xn;

            yn_left = a0_left*xn_left + a1_left*xn_1_left;

            z1_left = xn_left;

//            for(int channel = 0; channel<outputBuffer.getNumChannels(); ++channel) {
//                outputBuffer.addSample(0, startSample, yn_left);
                outputBuffer.addSample(0, startSample, wojtekSound);
//            }

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
    
    int wBufferSize;

private:
    double extSampRat;
    double level;
    double frequency;
    int theWaveType1;
    int theWaveType2;
    double osc1Mix;
    double osc2Mix;
    WojtekSynthEnvelope wVoiceEnv;
    WojtekSynthEnvelope wEnvelope_2;
    float wojtekEnvelope_2;
    
    double wVoiceLevel;
    double wVoicePitch;
    double wOsc2Pitch;
    double wVoiceFreq;
    int wVoiceWaveType1;
    int wVoiceWaveType2;
    double wVoiceOsc1Mix;
    double wVoiceOsc2Mix;
    
    float a0_left;
    float a1_left;
    
    float z1_left;

    maxiOsc mOsc1;
    maxiOsc mOsc2;
};
