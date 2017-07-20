/*
  ==============================================================================

   This file is based on juce::linearSmoothedValue
  ==============================================================================
*/

#pragma once

//==============================================================================
/**
    Utility class for linearly smoothed values like volume etc. that should
    not change abruptly but as a linear ramp, to avoid audio glitches.
*/

//==============================================================================
template <typename FloatType>
class LowpassSmoothedValue
{
public:
    /** Constructor. */
    LowpassSmoothedValue() noexcept
        : currentValue (0), target (0), A0 (1), B1 (1), xv(0), yv(0), fGControlCf (16)
    {
        reset(44100.0,0.01);
        
    }

    /** Constructor. */
    LowpassSmoothedValue (FloatType initialValue) noexcept
    : currentValue (0), target (initialValue), A0 (1), B1 (1), xv(0), yv(0), fGControlCf (16)
    {
        reset(44100.0,0.01);
        setValue(initialValue);
    }
    
    /** Constructor. */
    LowpassSmoothedValue (FloatType initialValue, double sampleRate, double filterTimeInSeconds ) noexcept
    : currentValue (0), target (initialValue), A0 (1), B1 (1), xv(0), yv(0), fGControlCf (16)
    {
        reset(sampleRate,filterTimeInSeconds);
        setValue(initialValue);
    }


    //==============================================================================
    /** Reset to a new sample rate and ramp length. */
    void reset (double sampleRate, double filterTimeInSeconds) noexcept
    {
        // sanity check: 0.00005 ms = 20kHz cutoff ≈ 99% of target in double of this time ≈ 4 samples at 44100
        // if you use this setting you won't get a divbyzero below, but you may get the clicks you were trying to avoid.
        jassert (sampleRate > 0 && filterTimeInSeconds >= 0.00005);
        
        double lowpassCutoffFreq = 1/filterTimeInSeconds;
        
        double cosf = 2.0 - cos (2* double_Pi * (lowpassCutoffFreq / 2.0) / sampleRate);
        double cb1  = cosf - sqrt(cosf * cosf - 1.0);
        
        B1 = (FloatType)cb1;
        A0 = (FloatType)(1.0 - cb1);
        
        setValue (target);
       
    }

    /** Set a new target value. */
    void setValue (FloatType newValue) noexcept
    {
        // TBD: approximate (maybe)
        target = newValue;
        xv = A0 * newValue;
        //yv = xv;
    }

    /** Compute the next value. */
    FloatType getNextValue() noexcept
    {
        //TBD no optimization if smoothing or not.
        return currentValue = yv = xv + B1 * yv; // TBD: remove yv and use current value
    }
    
    /** Do not Compute the next value. */
    FloatType getCurrentValue() noexcept
    {
        return currentValue;
    }

    /** Returns true if the current value is currently being interpolated. */
    bool isSmoothing() const noexcept
    {
        return approximates(currentValue,target);
    }

    /** Returns the target value towards which the smoothed value is currently moving. */
    FloatType getTargetValue() const noexcept
    {
        return target;
    }
    
    
    /** May use this to not smooth always. Probably not worth is, since getNexValue is one * **/
    bool approximates (FloatType value, FloatType target, FloatType precision = 0.00001)
    {
        if (fabs (value - target) < precision)
            return true;
        else
            return false;
    }

private:
    
    
    FloatType currentValue, target;
    FloatType A0;
    FloatType B1;
    FloatType xv;
    FloatType yv;
    FloatType fGControlCf;
    
};

