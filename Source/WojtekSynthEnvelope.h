/*
  ==============================================================================

    WojtekSynthEnvelope.h
    Created: 7 Jan 2018 5:34:29pm
    Author:  Wojtek Pilwinski

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
    
private:
    int trigger = 0;
    int wSampleRate = 44100;
    int wBufferSize=512;
    
    float wInput;
    float amplitudaA;
    float amplitudaR;
    float amplitudaD;
    
    float wAttack=1.0f;
    float wAttackConst;
    float fazaA=0.0f;
    int wAttackTrig=0;
    
    float wDecay=1.0f;
    float wDecayConst;
    float wSustain=1.0f;
    float fazaD=0.0f;
    
    float wRelease=1.0f;
    float wReleaseConst;
    float fazaR = 0.0f;
};
