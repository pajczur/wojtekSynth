/*
  ==============================================================================

    WojtekSynthEnvelope.cpp
    Created: 7 Jan 2018 5:34:29pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/
#include <iostream>
#include "WojtekSynthEnvelope.h"

//==============================================================================

float WojtekEnvelope::wojtekADSR(float input, int trig)
{
    if(wAttack==0) wAttack=1;
    if(wRelease==0) wRelease=1;
    if(wDecay==0) wDecay=1;
    
    if(trig == 1) {
        
        // ===== ATTACK ==================================== DUPEX FALALALALA I HAHAHAHAHAHA
        if ((fazaA/wAttack)<1.0f && wAttackTrig==0) {
            amplitudaA = fazaA/wAttack;
            fazaA++;
            fazaR += (wRelease/wAttack); if (fazaR > wRelease) fazaR = wRelease;
            if (fazaD != 0) fazaD = 0;
            if (amplitudaD!=1) amplitudaD=1;
            
            
            return amplitudaA * input;
        } else {
        
        // ===== DECAY & SUSTAIN ===========================
            
            if (wAttackTrig == 0) wAttackTrig = 1;
            
            if (fazaD < wDecay ) {
                amplitudaD -= ((1-wSustain)/wDecay);
                fazaD++;
                fazaR -= ((wRelease/wDecay) * (1 - wSustain));
                fazaA -= ((wAttack/wDecay) * (1 - wSustain));
                return amplitudaD * input;
            } else {
                return wSustain * input;
            }
        }
    } else {
        
        // ===== RELEASE ====================================
        
        if (wAttackTrig == 1) wAttackTrig=0;
        if (fazaR > 0) {
            amplitudaR = fazaR/wRelease;
            
            fazaR--;
            fazaA -= (wAttack/wRelease);
        } else {
            fazaA=0;
            amplitudaR = 0;
        }
        
        return amplitudaR * input;
    }
}


//==============================================================================


void WojtekEnvelope::setTrigger(int trig)
{
    trigger = trig;
}

//==============================================================================

void WojtekEnvelope::wojtekSetAttack(float attackInMicroSec)
{
    wAttack = attackInMicroSec * ((float)wSampleRate/1000000.0f);
}

//==============================================================================

void WojtekEnvelope::wojtekSetDecay(float decayInMicroSec)
{
    wDecay = decayInMicroSec * ((float)wSampleRate/1000000.0f);
}

void WojtekEnvelope::wojtekSetSustain(float sus)
{
    wSustain = sus;
}


//==============================================================================

void WojtekEnvelope::wojtekSetRelease(float releaseInMicroSec)
{
    wRelease = releaseInMicroSec * ((float)wSampleRate/1000000.0f);
}
