#pragma once


/**
 Use this class to bind a text button to an AudioProcessorParameter.
 When clicking (toggling is set on by default) the button text will
 follow your directives in the velueToText lambda you provided in 
 AudioProcessorValueTreeState::CreateAndAddParameter
 
 
 
*/


class AudioProcessorParameterTextButton : public TextButton,  private Button::Listener
{
public:
    AudioProcessorParameterTextButton();
    AudioProcessorParameterTextButton(const juce::String &componentName);
    
    
    void buttonClicked (Button* b) override;
    void buttonStateChanged (Button*)  override;
    
    void mouseUp (const MouseEvent& event) override;
    
   
    
    AudioProcessorParameterTextButton(AudioProcessorParameter*);
    
    const AudioProcessorParameter* getParameter();

    void setParameter (const AudioProcessorParameter*,bool autotoggle=false);
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
                          AudioProcessorParameterTextButton& buttonToControl);
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
    
    bool autotoggle_;

    //bool textSuffixEnabled;
};


