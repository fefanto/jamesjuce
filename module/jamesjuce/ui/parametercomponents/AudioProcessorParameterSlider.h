#pragma once

//#include <assert.h>

// A Slider for an audio plugin parameter that has
// * The same mapping of proportion-of-length to value as the parameter (same as automation).
// * The same text formatting as the parameter.
//
// Internally the value for the Slider is the parameter value in 0 to 1 range,
// but due to the text formatting it looks like user-readable values.

class PluginCore;

class AudioProcessorParameterSlider : public Slider
{
public:
    AudioProcessorParameterSlider();
    AudioProcessorParameterSlider(const juce::String &componentName,SliderStyle style, TextEntryBoxPosition textBoxPos);
    
    
    AudioProcessorParameterSlider(const AudioProcessorParameter*);
    const AudioProcessorParameter* getParameter();
    void setParameter (const AudioProcessorParameter*);
    void setLabel(const String& label);
    String getLabel() const;
    void setTextSuffixEnabled (bool);
    
    void setSyncable(bool syncable,PluginTempoSync::SyncUnit syncunit){syncable_ = syncable;syncunit_ = syncunit;};
    
    

//#if JUCE_COMPILER_SUPPORTS_LAMBDAS || defined (DOXYGEN)
    // SliderAttachment
    class SliderAttachment : public AudioProcessorValueTreeState::SliderAttachment
    {
    public:
        SliderAttachment (AudioProcessorValueTreeState& stateToControl,
                          const String& parameterID,
                          AudioProcessorParameterSlider& sliderToControl);
        virtual ~SliderAttachment() = default;
        
        
    };
//#endif

    String getTextFromValue (double value) override;
    double getValueFromText (const juce::String& text) override;

    
public:
    String maxLabel;
    String medLabel;
    String minLabel;
protected:
    const AudioProcessorParameter* parameter;

private:
    void initParameter(const AudioProcessorParameter*);

    bool textSuffixEnabled;
    
    String parameterLabel;
    
    PluginTempoSync tempoSyncUtil;
    bool syncable_;
    PluginTempoSync::SyncUnit syncunit_;
    
};

