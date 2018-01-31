/*
  ==============================================================================

    WojtekSynthEnvelope.cpp
    Created: 7 Jan 2018 5:34:29pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/
#include <iostream>
#include "WojtekSynthEnvelope.h"
#include <cmath>

//=== E N V E L O P E === A D S R ==============================================

float WojtekSynthEnvelope::wojtekADSR(float input, int trig)
{
    if(wAttack==0) wAttack=1;
    if(wRelease==0) wRelease=1;
    if(wDecay==0) wDecay=1;
    
    if(trig == 1) {
        
        // ===== ATTACK ====================================
        if (fazaA<wAttack && wAmplitude<=1 && wAttackTrig==1) {
            wAmplitude += 1.0f/wAttack;
            fazaA++;
            
            if(fazaD != 0) fazaD = 0;
            if(fazaR != 0) fazaR = 0;
            
            if (wAmplitudeR != 1.0f) wAmplitudeR = 1.0f;
            logAmpRelTemp = wLogAttack(wAmplitude);

            return wLogAttack(wAmplitude) * wGain * input;
        } else {
        
        // ===== DECAY & SUSTAIN ===========================
            
            if (wAttackTrig == 1) wAttackTrig = 0;
            
            if (fazaD < wDecay ) {
                wAmplitude -= 1.0f/wDecay;
                fazaD++;

                if(fazaA != 0) fazaA = 0;
                if(fazaR != 0) fazaR = 0;
                
                if (wAmplitudeR != 1.0f) wAmplitudeR = 1.0f;
                logAmpRelTemp = (1.0f - (1.0f-wSustain)*(1.0f-wLogDecay(wAmplitude)));

                return (1.0f - (1.0f-wSustain)*(1.0f-wLogDecay(wAmplitude))) * wGain * input;
            } else {
                if (logAmpRelTemp != wLogDecay(wSustain)) logAmpRelTemp = wLogDecay(wSustain);
                if (wAmplitudeR != 1.0f) wAmplitudeR = 1.0f;
                
                if(fazaA != 0) fazaA = 0;
                if(fazaR != 0) fazaR = 0;

                return wSustain * wGain * input;
            }
        }
    } else {
        
        // ===== RELEASE ====================================
        
        if (wAttackTrig == 0) { wAttackTrig=1; }
        if (fazaR<wRelease && wAmplitudeR>0) {
            wAmplitudeR -= 1.0f/wRelease;
            wAmplitude = wAmplitudeR;
            
            if(fazaA != 0) fazaA = 0;
            fazaR++;
        } else {
            if(fazaA != 0) fazaA = 0;
            wAmplitude = 0;
            wAmplitudeR = 0;
        }
        if (wAmplitude <= 0.0f) wAmplitude = 0.0f;
        
        return wLogRelease(wAmplitudeR) * logAmpRelTemp * wGain * input;
    }
}


//=== E X T E R N A L = S E T T I N G S ======================================

void WojtekSynthEnvelope::setTrigger(int trig)
{
    trigger = trig;
}

//=== A T T A C K =============================================================

void WojtekSynthEnvelope::wojtekSetAttack(float attackInMicroSec)
{
    wAttack = attackInMicroSec * ((float)wSampleRate/1000000.0f);
}

float WojtekSynthEnvelope::wLogAttack(float amp0to1)
{
    float amp;
    if(amp0to1>0 && amp0to1<1) {
        amp = ((-exp( (log(wAttackCurveParam)) / (1-amp0to1))) / wAttackCurveParam) + 1;
        return amp;
    } else if (amp0to1 >= 1) {
        return 1.0f;
    }
    else return 0.0f;
}

void WojtekSynthEnvelope::wLogAttackManip (float curve)
{
    if (curve>=0.000000001 && curve<=0.999999999) {
        wAttackCurveParam = curve;
    } else if (curve>0.999) {
        wAttackCurveParam = 0.999999999;
    } else {
        wAttackCurveParam = 0.000000001;
    }
}

//=== D E C A Y ===============================================================

void WojtekSynthEnvelope::wojtekSetDecay(float decayInMicroSec)
{
    wDecay = decayInMicroSec * ((float)wSampleRate/1000000.0f);
}

void WojtekSynthEnvelope::wojtekSetSustain(float sus)
{
    if (sus>0 && sus<1) {
        wSustain = sus;
    } else if (sus>=1) {
        wSustain = 1;
    } else wSustain = 0;

    
//    if (sus>0 && sus<1) {
//        float toLog = -65.7303 * (1 - sus);
//        wSustain = powf(10.0f, toLog/20.0f);
//    } else if (sus>=1) {
//        wSustain = 1;
//    } else wSustain = 0;
}

float WojtekSynthEnvelope::wLogDecay(float amp0to1)
{
    float amp;
    if(amp0to1>0 && amp0to1<1) {
        amp = ((-exp( (log(wDecayCurveParam)) / (1-amp0to1))) / wDecayCurveParam) + 1;
        return amp;
    } else if (amp0to1 >= 1) {
        return 1.0f;
    }
    else return 0.0f;
}

void WojtekSynthEnvelope::wLogDecayManip (float curve)
{
    if (curve>=0.000000001 && curve<=0.999999999) {
        wDecayCurveParam = curve;
    } else if (curve>0.999) {
        wDecayCurveParam = 0.999999999;
    } else {
        wDecayCurveParam = 0.000000001;
    }
}


//=== R E L E A S E =============================================================

void WojtekSynthEnvelope::wojtekSetRelease(float releaseInMicroSec)
{
    wRelease = releaseInMicroSec * ((float)wSampleRate/1000000.0f);
}

float WojtekSynthEnvelope::wLogRelease(float amp0to1)
{
    float amp;
    if(amp0to1>0 && amp0to1<1) {
        amp = ((-exp( (log(wReleaseCurveParam)) / (1.0-amp0to1))) / wReleaseCurveParam) + 1;
        return amp;
    } else if (amp0to1 >= 1) {
        return 1.0f;
    }
    else return 0.0f;
}

void WojtekSynthEnvelope::wLogReleaseManip (float curve)
{
    if (curve>=0.000000001 && curve<=0.999999999) {
        wReleaseCurveParam = curve;
    } else if (curve>0.999) {
        wReleaseCurveParam = 0.999999999;
    } else {
        wReleaseCurveParam = 0.000000001;
    }
}





//=== G A I N =================================================================
void WojtekSynthEnvelope::wojtekSetGain(float gain)
{
    if(gain>-65.0f) {
        wGain = pow(10.0f, gain/20.0f);
    } else {
        wGain = pow(10.0f, -65.0f/20.0f)*(gain + 66.0f);
    }
}
