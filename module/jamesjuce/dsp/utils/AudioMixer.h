/*
 ==============================================================================
 
 AudioMixer : wet/dry Audio Manager for plugin internal audio processing
  - internal "wet" buffer is always stereo
  - external "dry" buffer can be stereo or mono
 Created: 14 Mar 2017 6:16:11pm
 Author:  Michelangelo Nottoli
 
 ==============================================================================
 */

#pragma once



class AudioMixer {
private:
    static constexpr int  channelCount = 2;
    static constexpr double  smootherControlRateInSeconds = 0.0625;
    static constexpr int  defaultSamplesPerBlock = 1024;
    static constexpr double PI_1_2 = 1.5707963267948966192313216916398;
    
    int samplesPerBlock_;
 
    ScopedPointer < AudioBuffer<float> > wetAudio;
    ScopedPointer < AudioBuffer<float> > interleavedAudio;
    ScopedPointer < AudioBuffer<float> > interleavedAudioSidechain;
    
    ScopedPointer <LowpassSmoothedValue<float>> wetSmoother;
    ScopedPointer <LowpassSmoothedValue<float>> wetLevelSmoother;
    ScopedPointer <LowpassSmoothedValue<float>> inLevelSmoother;
    
    
    
public:
    AudioMixer();
    virtual ~AudioMixer();

    
    /**
     updates the dry/wet amount
     */
    void setWetAmount(const float & newVal);


    /**
     updates the in level amount (input level of the plugin)
     */
    void setInLevelAmount(const float & newVal);
    /**
     updates the wet level amount (output level of the plugin)
     */
    void setWetLevelAmount(const float & newVal);
    
    
    /**
     reference to internal audio buffers
    */
    //AudioSampleBuffer& getDryAudio();
    AudioSampleBuffer* getWetAudio();
    AudioSampleBuffer* getInterleavedAudio();
    AudioSampleBuffer* getInterleavedAudioSidechain();
    
    /**
     checks if internal wet audio buffer size is compatible with 
     samplesPerBlock and resizes it if needed - uses preparebuffer (also checke in process function for sanity check
    */
    void prepareToPlay(double newSampleRate,int samplesPerBlock);
    void prepareBuffer(int samplesPerBlock);
    
    /**
     copies the argument (mono or stereo) buffer in the
     internal (always stereo) buffer.
     */
    void mixIn(AudioSampleBuffer& inputAudio,const int & samples, const int & inputChannels, const int & outputChannnels);

    /**
     copies the internal  (always stereo) buffer in the
     argument buffer (mono or stereo), smoothing the amount of wet signal copied (dry/wet) and the output level LINEARLY
     */
    void mixOutLinear(AudioSampleBuffer& outputAudio,const int & samples, const int & inputChannels, const int & outputChannnels);
    
    /**
     copies the internal  (always stereo) buffer in the
     argument buffer (mono or stereo), smoothing the output level LINEARLY and the amount of wet signal USING SIN COS mapping, example : 

     static const double PI_1_2 = 1.5707963267948966192313216916398;
     double phase = dry_wet*PI_1_2;
     smpOut = sin(phase)*smpIn + cos(phase)*smpOut;
     */
    void mixOutSinCos(AudioSampleBuffer& outputAudio,const int & samples, const int & inputChannels, const int & outputChannnels);

    
};


inline AudioSampleBuffer* AudioMixer::getWetAudio(){
    return wetAudio.get();
}

inline AudioSampleBuffer* AudioMixer::getInterleavedAudio(){
    return interleavedAudio.get();
}

inline AudioSampleBuffer* AudioMixer::getInterleavedAudioSidechain(){
    return interleavedAudioSidechain.get();
}


inline void AudioMixer::prepareToPlay(double newSampleRate,int samplesPerBlock){
    prepareBuffer(samplesPerBlock);
    
    wetSmoother->reset(newSampleRate,smootherControlRateInSeconds);
    wetLevelSmoother->reset(newSampleRate,smootherControlRateInSeconds);
    
    
}

inline void AudioMixer::prepareBuffer(int samplesPerBlock){
    if(samplesPerBlock_<samplesPerBlock){
        samplesPerBlock_=samplesPerBlock;
        //dryAudio.setSize(AudioMixer::channelCount, samplesPerBlock_,true,true,true);
        wetAudio->setSize(AudioMixer::channelCount, samplesPerBlock_,true,true,true);
        interleavedAudio->setSize(1, samplesPerBlock_*2,true,true,true);
        interleavedAudioSidechain->setSize(1, samplesPerBlock_*2,true,true,true);
    }
    interleavedAudioSidechain->clear();
    interleavedAudio->clear();

}


inline void AudioMixer::mixIn(AudioSampleBuffer& inputAudio, const int & samples, const int & inputChannels, const int & outputChannnels)
{
    prepareBuffer(samples); // sanity check
    int numSamples = samples;
    auto* wl = wetAudio->getWritePointer(0);
    auto* wr = wetAudio->getWritePointer(1);
    float inputLevel = 1.0f;
    
    if(inputChannels==0){
        jassertfalse;
    }
    else if(inputChannels==1){
        auto* r = inputAudio.getReadPointer(0);
        
        while (--numSamples >= 0)
        {
            *wl++ = *wr++ = inLevelSmoother->getNextValue() * *r++;
        }

    }
    else if(inputChannels==2){
        auto* rl = inputAudio.getReadPointer(0);
        auto* rr = inputAudio.getReadPointer(1);
        while (--numSamples >= 0)
        {
            inputLevel = inLevelSmoother->getNextValue();
            *wl++ = inputLevel * *rl++;
            *wr++ = inputLevel * *rr++;
        }

    }
    else{
        jassertfalse;
    }
    
    
}

inline void AudioMixer::mixOutLinear(AudioSampleBuffer& dryAudio, const int & samples, const int & inputChannels, const int & outputChannnels)
{
    jassert (samples<=samplesPerBlock_);
    
    const float *wetL = wetAudio->getReadPointer(0);
    const float *wetR = wetAudio->getReadPointer(1);
    int counter = samples;
    
    if(outputChannnels==0){
        jassertfalse;
    }
    else if(outputChannnels==1){
        float* outDryMono = dryAudio.getWritePointer(0);
        float wet = 0.5f, wetLevel = 1.0f, dry = 0.5f;
        while (counter--){
            wet = wetSmoother->getNextValue();
            wetLevel = wetLevelSmoother->getNextValue();
            dry = 1.0f - wet;
            *outDryMono = *outDryMono * dry + (*wetL++ + *wetR++) * 0.5f * wet * wetLevel ;
            outDryMono++;
        }
    }
    else if(outputChannnels==2){
        
        float* outDryL = dryAudio.getWritePointer(0);
        float* outDryR = dryAudio.getWritePointer(1);
        float wet = 0.5f, wetLevel = 1.0f, dry = 0.5f;
        while (counter--){
            wet = wetSmoother->getNextValue();
            wetLevel = wetLevelSmoother->getNextValue();
            dry = 1.0f - wet;
            *outDryL = *outDryL * dry  + *wetL * wet * wetLevel   ;
            outDryL++;
            wetL++;
            *outDryR = *outDryR * dry  + *wetR * wet * wetLevel   ;
            outDryR++;
            wetR++;
        }
    }
    else{
        jassertfalse;
    }
    
}



inline void AudioMixer::mixOutSinCos(AudioSampleBuffer& dryAudio, const int & samples, const int & inputChannels, const int & outputChannnels)
{
    jassert (samples<=samplesPerBlock_);
    
    const float *wetL = wetAudio->getReadPointer(0);
    const float *wetR = wetAudio->getReadPointer(1);
    int counter = samples;
    
    if(outputChannnels==0){
        jassertfalse;
    }
    else if(outputChannnels==1){
        float* outDryMono = dryAudio.getWritePointer(0);
        float wetLevel = 1.0f;
        double phase = 0.0;
        while (counter--){
            phase = wetSmoother->getNextValue()*PI_1_2;
            wetLevel = wetLevelSmoother->getNextValue();
            *outDryMono = *outDryMono * cos(phase) + (*wetL++ + *wetR++) * 0.5f * sin(phase) * wetLevel ;
            outDryMono++;
        }
    }
    else if(outputChannnels==2){
        
        float* outDryL = dryAudio.getWritePointer(0);
        float* outDryR = dryAudio.getWritePointer(1);
        float wetLevel = 1.0f;
        double phase = 0.0;
        
        while (counter--){
            phase = wetSmoother->getNextValue()*PI_1_2;
            wetLevel = wetLevelSmoother->getNextValue();
            
            *outDryL = *outDryL * cos(phase)  + *wetL * sin(phase) * wetLevel   ;
            outDryL++;
            wetL++;
            *outDryR = *outDryR * cos(phase)  + *wetR * sin(phase) * wetLevel   ;
            outDryR++;
            wetR++;
        }
    }
    else{
        jassertfalse;
    }
    
}
