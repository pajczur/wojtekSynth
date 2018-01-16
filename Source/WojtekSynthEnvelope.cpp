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

//==============================================================================

float WojtekEnvelope::wojtekADSR(float input, int trig)
{
    if(wAttack==0) wAttack=1;
    if(wRelease==0) wRelease=1;
    if(wDecay==0) wDecay=1;
    
    if(trig == 1) {
        
        // ===== ATTACK ====================================
        if (fazaA<wAttack && wAmplitude<=1 && wAttackTrig==1) {
            wAmplitude += 1/wAttack;
            ampRelTemp = wAmplitude;
            fazaA++;
            
            if(fazaD != 0) fazaD = 0;
            if(fazaR != 0) fazaR = 0;
            
            if (wAmplitudeR != 1) wAmplitudeR = 1;
            logAmpRelTemp = wLogShape(wAmplitude);
            
//            return wAmpLogDown(wAmplitude) * input;
            return wLogShape(wAmplitude) * input;
//            return wAmpLogUP(wAmplitude) * input;
//            return wAmpExp(wAmplitude) * input;
        } else {
        
        // ===== DECAY & SUSTAIN ===========================
            
            if (wAttackTrig == 1) wAttackTrig = 0;
            
            if (fazaD < wDecay ) {
                wAmplitude -= ((1-wSustain)/wDecay);
                ampRelTemp = wAmplitude;
                fazaD++;

                if(fazaA != 0) fazaA = 0;
                if(fazaR != 0) fazaR = 0;
                
                if (wAmplitudeR != 1) wAmplitudeR = 1;
                logAmpRelTemp = wAmpLogUP(wAmplitude);

//                return wAmpLogDown(wAmplitude) * input;
                return wAmpLogUP(wAmplitude) * input;
//                return wAmpLogDownDecay(wAmplitude, wSustain);
//                return wAmpExp(wAmplitude) * input;
            } else {
                if (wAmplitude != wSustain) { wAmplitude = wSustain; ampRelTemp = wSustain; }
                if (logAmpRelTemp != wAmpLogUP(wSustain)) logAmpRelTemp = wAmpLogUP(wSustain);
                if (wAmplitudeR != 1) wAmplitudeR = 1;
                
                if(fazaA != 0) fazaA = 0;
                if(fazaR != 0) fazaR = 0;

//                return wAmpLog(wAmplitude) * input;
                return wAmpLogUP(wSustain) * input;
//                return wAmpExp(wAmplitude) * input;
            }
        }
    } else {
        
        // ===== RELEASE ====================================
        
        if (wAttackTrig == 0) { wAttackTrig=1; }
        if (fazaR<wRelease && wAmplitudeR>0) {
            wAmplitudeR -= 1/wRelease;
            wAmplitude = wAmplitudeR;
            
            if(fazaA != 0) fazaA = 0;
            fazaR++;
        } else {
            if(fazaA != 0) fazaA = 0;
            wAmplitude = 0;
        }
        if (wAmplitude <= 0) wAmplitude = 0;
        
        
        return wAmpLogDown(wAmplitudeR) * logAmpRelTemp * input;
//        return wAmpLogUP(wAmplitude) * input;
//        return wAmpExp(wAmplitude) * input;
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


//==============================================================================

void WojtekEnvelope::wojtekSetRelease(float releaseInMicroSec)
{
    wRelease = releaseInMicroSec * ((float)wSampleRate/1000000.0f);
}


//==============================================================================

float WojtekEnvelope::wLogShape(float amp0to1)
{
    float amp;
    if(amp0to1>0 && amp0to1<1)
        amp = (exp( (log(0.55)) / amp0to1)) / 0.55;
    else if (amp0to1 >= 1) return 1.0f;
    else return 0.0f;
    
    return amp;
}


float WojtekEnvelope::wAmpLogDown(float amp0to1)
{
    if (amp0to1>0 && amp0to1<1) {
        float toLog = (-65.7303) * (1 - amp0to1);
        return powf(10.0f, (toLog)/20.0f);
    } else if (amp0to1>=1) {
        return 1.0f;
    } else return 0.0f;
}

float WojtekEnvelope::wAmpLogUP(float amp0to1)
{
    if (amp0to1>0 && amp0to1<1) {
        if((log10f(amp0to1))+1 <= 0) return 0.0f;
        else return (log10f(amp0to1))+1;
    } else if (amp0to1>=1) {
        return 1.0f;
    } else return 0.0f;
}

float WojtekEnvelope::wAmpLogDownDecay(float amp0to1, float sustain)
{
    float logDownDecay = exp((5*amp0to1)-5);
    if ((amp0to1>0 && amp0to1<=1) && logDownDecay>=sustain) {
        return logDownDecay;
    } else if (logDownDecay<sustain) {
        return sustain;
    } else return 0.0f;
}

float WojtekEnvelope::wAmpExp(float amp0to1)
{
    if (amp0to1>0 && amp0to1<1) {

        return (float)exp((-0.43415218*10)/(0.1*amp0to1*wSampleRate*0.001));
    } else if (amp0to1>=1) {
        return (float)exp((-0.43415218*10)/(0.1*wSampleRate*0.001));
    } else return 0.0f;
}
