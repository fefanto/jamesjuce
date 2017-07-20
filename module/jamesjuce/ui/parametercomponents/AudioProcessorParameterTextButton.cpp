

AudioProcessorParameterTextButton::AudioProcessorParameterTextButton()
{
    initParameter(nullptr);
}

AudioProcessorParameterTextButton::AudioProcessorParameterTextButton (AudioProcessorParameter* p)
{
    initParameter(p);
}

AudioProcessorParameterTextButton::AudioProcessorParameterTextButton (const String &componentName)
{
    setName(componentName);
    initParameter(nullptr);
}

void AudioProcessorParameterTextButton::initParameter (const AudioProcessorParameter* p)
{
    parameter = p;
    autotoggle_ = false;
    //textSuffixEnabled = true;
}

//void AudioProcessorParameterTextButton::setTextSuffixEnabled (bool v)
//{
//    textSuffixEnabled = v;
//}

const AudioProcessorParameter* AudioProcessorParameterTextButton::getParameter()
{
    jassert(parameter!=nullptr);
    return parameter;
}

void AudioProcessorParameterTextButton::setParameter (const AudioProcessorParameter* p,bool autotoggle)
{
    if (parameter == p)
        return;
    
    parameter = p;
    autotoggle_ = autotoggle;
    /* 
     this might be a togglebutton (already with click toggling state)
     or a Text/Drawable/Image button, in which case i need to make sure that
     setClickingTogglesState(true) @see also: AudioProcessorValueTreeState::ButtonAttachment::Pimpl::ButtonClicked
     */
    setClickingTogglesState(true);
    setTriggeredOnMouseDown (true);
    
//    if(!clickingTogglesState){
//        addMouseListener(this, false);
//    }
    
    float value = parameter->getValue();
    String buttonText = getTextFromValue(parameter->getValue());
    bool toggleState = (int)value!=0;
//    DBG("AudioProcessorParameterTextButton::setParameter - value = " << value << " - text " << buttonText << " - toggle = " << toggleState);
    setToggleState(toggleState,sendNotification);
    
    setButtonText(buttonText);
    
    repaint();
    
    /*
     will get click info to update button text
     */
    addListener(this);
}

void AudioProcessorParameterTextButton::mouseUp (const MouseEvent& event){
    
    if(autotoggle_){
        DBG("AudioProcessorParameterTextButton::mouseUp --> Triggering Click");
        this->triggerClick();
    }
}

void AudioProcessorParameterTextButton::buttonClicked (Button* b)
{
 
//    if(!getClickingTogglesState()) // managing parameter toggle on mouse down/up internally e.g. panic button
//    {
//        if(parameter!=nullptr){
//            float val = parameter->getValue();
//            jassert(val == 0.0f || val == 1.0f);
//  //          parameter->setValueNotifyingHost(val==0.0f ? 1.0f : 0.0f);
//            
//        }
//        
//        if(isDown()){
//            DBG("AudioProcessorParameterTextButton::buttonStateChanged --> IsDown");
//        }
//        
//    }
    
    String buttonText = getTextFromValue(parameter->getValue());
    setButtonText(buttonText);
    DBG("AudioProcessorParameterTextButton::buttonClicked");
}

void AudioProcessorParameterTextButton::buttonStateChanged (Button*)  {
    //DBG("AudioProcessorParameterTextButton::buttonStateChanged");

}


//#if JUCE_COMPILER_SUPPORTS_LAMBDAS || defined (DOXYGEN)
// wraps ButtonAttachment to link with the button
AudioProcessorParameterTextButton::ButtonAttachment::ButtonAttachment (AudioProcessorValueTreeState& stateToControl, const String& parameterID, AudioProcessorParameterTextButton& buttonToControl)
: AudioProcessorValueTreeState::ButtonAttachment (stateToControl, parameterID, buttonToControl)
{
    buttonToControl.setParameter(stateToControl.getParameter(parameterID));
}
//#endif

String AudioProcessorParameterTextButton::getTextFromValue (double value)
{
    if (parameter == nullptr)
        return String (value);

    // assuming createAndAddParamter was issued with a 0/1 range!
    const NormalisableRange<double> range (0.0f, 1.0f);
    const float normalizedVal = (float) range.convertTo0to1 (value);

    String result = parameter->getText (normalizedVal, 1);
    
    return result;
  
}
    
    

double AudioProcessorParameterTextButton::getValueFromText (const String& text)
{
    if (parameter == nullptr)
        return 0.0;/*ONLY SLIDER WHAT NOW WITH BUTTON ???*/ //Slider::getValueFromText (text);
    return parameter->getValueForText (text);
}
    
    
//void AudioProcessorParameterTextButton::setLabel(const String& label){
//    parameterLabel = label;
//}
//    
//String AudioProcessorParameterTextButton::getLabel() const{
//        return parameterLabel;
//}




