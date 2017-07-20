

AudioProcessorParameterToggleButton::AudioProcessorParameterToggleButton()
{
    initParameter(nullptr);
}

AudioProcessorParameterToggleButton::AudioProcessorParameterToggleButton (const AudioProcessorParameter* p)
{
    initParameter(p);
}

AudioProcessorParameterToggleButton::AudioProcessorParameterToggleButton (const String &componentName)
{
    setName(componentName);
    initParameter(nullptr);
}

void AudioProcessorParameterToggleButton::initParameter (const AudioProcessorParameter* p)
{
    parameter = p;
    //textSuffixEnabled = true;
}

//void AudioProcessorParameterToggleButton::setTextSuffixEnabled (bool v)
//{
//    textSuffixEnabled = v;
//}

const AudioProcessorParameter* AudioProcessorParameterToggleButton::getParameter()
{
    jassert(parameter!=nullptr);
    return parameter;
}

void AudioProcessorParameterToggleButton::setParameter (const AudioProcessorParameter* p)
{
    if (parameter == p)
        return;
    
    parameter = p;
    /* 
     this might be a togglebutton (already with click toggling state)
     or a Text/Drawable/Image button, in which case i need to make sure that
     setClickingTogglesState(true) @see also: AudioProcessorValueTreeState::ButtonAttachment::Pimpl::ButtonClicked
     */
    setClickingTogglesState(true);
    float value = parameter->getValue();
    String buttonText = getTextFromValue(parameter->getValue());
    bool toggleState = (int)value!=0;
//    DBG("AudioProcessorParameterToggleButton::setParameter - value = " << value << " - text " << buttonText << " - toggle = " << toggleState);
    setToggleState(toggleState,sendNotification);
    
    setButtonText(buttonText);
    
    repaint();
    
    /*
     will get click info to update button text
     */
    addListener(this);
}

void AudioProcessorParameterToggleButton::buttonClicked (Button* b)
{
    String buttonText = getTextFromValue(parameter->getValue());
    setButtonText(buttonText);
}

//#if JUCE_COMPILER_SUPPORTS_LAMBDAS || defined (DOXYGEN)
// wraps ButtonAttachment to link with the button
AudioProcessorParameterToggleButton::ButtonAttachment::ButtonAttachment (AudioProcessorValueTreeState& stateToControl, const String& parameterID, AudioProcessorParameterToggleButton& buttonToControl)
: AudioProcessorValueTreeState::ButtonAttachment (stateToControl, parameterID, buttonToControl)
{
    buttonToControl.setParameter(stateToControl.getParameter(parameterID));
}
//#endif

String AudioProcessorParameterToggleButton::getTextFromValue (double value)
{
    if (parameter == nullptr)
        return String (value);

    // assuming createAndAddParamter was issued with a 0/1 range!
    const NormalisableRange<double> range (0.0f, 1.0f);
    const float normalizedVal = (float) range.convertTo0to1 (value);

    String result = parameter->getText (normalizedVal, 1);
    
    return result;
  
}
    
    

double AudioProcessorParameterToggleButton::getValueFromText (const String& text)
{
    if (parameter == nullptr)
        return 0.0;/*ONLY SLIDER WHAT NOW WITH BUTTON ???*/ //Slider::getValueFromText (text);
    return parameter->getValueForText (text);
}
    
    
//void AudioProcessorParameterToggleButton::setLabel(const String& label){
//    parameterLabel = label;
//}
//    
//String AudioProcessorParameterToggleButton::getLabel() const{
//        return parameterLabel;
//}




