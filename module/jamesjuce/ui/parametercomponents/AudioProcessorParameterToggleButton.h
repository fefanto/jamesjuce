#pragma once


/**
 Use this class to bind a text button to an AudioProcessorParameter.
 When clicking (toggling is set on by default) the button text will
 follow your directives in the velueToText lambda you provided in 
 AudioProcessorValueTreeState::CreateAndAddParameter
 
 
 
*/


class AudioProcessorParameterToggleButton : public ToggleButton,  private Button::Listener
{
public:
    AudioProcessorParameterToggleButton();
    AudioProcessorParameterToggleButton(const juce::String &componentName);
    
    
    void buttonClicked (Button* b) override;
   
    
    AudioProcessorParameterToggleButton(const AudioProcessorParameter*);
    const AudioProcessorParameter* getParameter();
    void setParameter (const AudioProcessorParameter*);
//    void setLabel(const String& label);
//    String getLabel() const;
//    void setTextSuffixEnabled (bool);
    
    

//#if JUCE_COMPILER_SUPPORTS_LAMBDAS || defined (DOXYGEN)
    // ButtonAttachment
    class ButtonAttachment : public AudioProcessorValueTreeState::ButtonAttachment
    {
    public:
        ButtonAttachment (AudioProcessorValueTreeState& stateToControl,
                          const String& parameterID,
                          AudioProcessorParameterToggleButton& buttonToControl);
        virtual ~ButtonAttachment() = default;
        
        
    };
//#endif

    String getTextFromValue (double value);
    double getValueFromText (const juce::String& text) /*override*/;  // only slider has getValueFromText

    
public:
    //String parameterLabel;
protected:
    const AudioProcessorParameter* parameter;

private:
    void initParameter(const AudioProcessorParameter*);

    //bool textSuffixEnabled;
};


