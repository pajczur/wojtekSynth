/*
  ==============================================================================

    WojtekSynthEnvelope.h
    Created: 7 Jan 2018 5:34:29pm
    Author:  Wojtek Pilwinski A CO TO?

  ==============================================================================
*/

#pragma once

class WojtekEnvelope
{
public:
    WojtekEnvelope() {};
    ~WojtekEnvelope() {};
    float wojtekADSR(float input, int trig);
    void setTrigger(int trig);
    int getTrigger() { return trigger; };
    void wojtekSetAttack(float attackInMicroSec);
    void wojtekSetDecay(float decayInMicroSec);
    void wojtekSetSustain(float sus);
    void wojtekSetRelease(float releaseInMicroSec);
    
    float wAmpLogDown(float amp0to1);
    float wAmpLogUP(float amp0to1);
    float wAmpExp(float amp0to1);
    
private:
    int trigger = 0;
    int wSampleRate = 44100;
    int wBufferSize=512;
    
    float wInput;
    float wAmplitude;
    float amplitudaR;
    float amplitudaD;
    float ConstAmplitudaA;
    float ConstAmplitudaR;
    float ConstAmplitudaD;
    
    float wAttack=1.0f;
    float fazaA=0.0f;
    int wAttackTrig=1;
    
    float wDecay=1.0f;
    float wSustain=1.0f;
    float fazaD=0.0f;
    
    float wRelease=1.0f;
    float fazaR = 0.0f;
    float ampRelTemp;
};
