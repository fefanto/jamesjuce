/*
 ==============================================================================
 
 DSPProcessor.h
 Created: 14 Mar 2017 6:16:11pm
 Author:  Michelangelo Nottoli
 
 ==============================================================================
 */


AudioMixer::AudioMixer():
samplesPerBlock_(AudioMixer::defaultSamplesPerBlock)
{
    wetAudio = new AudioSampleBuffer(AudioMixer::channelCount,samplesPerBlock_);
    interleavedAudio = new AudioSampleBuffer(1,samplesPerBlock_*2);
    wetSmoother = new LowpassSmoothedValue<float>(0.5f);
    inLevelSmoother = new LowpassSmoothedValue<float>(0.5f);
    wetLevelSmoother = new LowpassSmoothedValue<float>(0.5f);
    
}

AudioMixer::~AudioMixer(){
    
}

void AudioMixer::setWetAmount(const float & newVal){
    jassert(newVal >=0.0f && newVal <= 1.0f);
    float val = jlimit(0.0f,1.0f, newVal);
    wetSmoother->setValue(val);
}

void AudioMixer::setInLevelAmount(const float & newVal){
    jassert(newVal >=0.0f && newVal <= 16.0f);
    float val = jlimit(0.0f,1.0f, newVal);
    inLevelSmoother->setValue(val);
}

void AudioMixer::setWetLevelAmount(const float & newVal){
    jassert(newVal >=0.0f && newVal <= 16.0f);
    float val = jlimit(0.0f,1.0f, newVal);
    wetLevelSmoother->setValue(val);
}










