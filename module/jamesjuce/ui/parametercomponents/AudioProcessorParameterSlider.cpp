

AudioProcessorParameterSlider::AudioProcessorParameterSlider()
{
    initParameter(nullptr);

}

AudioProcessorParameterSlider::AudioProcessorParameterSlider (const AudioProcessorParameter* p)
{
    initParameter(p);
}

AudioProcessorParameterSlider::AudioProcessorParameterSlider (const String &componentName, SliderStyle style, TextEntryBoxPosition textBoxPos):
Slider (style,textBoxPos)
{
    setName(componentName);
    initParameter(nullptr);
}

void AudioProcessorParameterSlider::initParameter (const AudioProcessorParameter* p)
{
    parameter = p;
    textSuffixEnabled = true;
    syncable_ = false;
}

void AudioProcessorParameterSlider::setTextSuffixEnabled (bool v)
{
    textSuffixEnabled = v;
}

const AudioProcessorParameter* AudioProcessorParameterSlider::getParameter()
{
    // You're trying to get parameter which isn't initialized yet!
//    SRSoftAssert (parameter!=nullptr);
    jassert(parameter!=nullptr);
    return parameter;
}

void AudioProcessorParameterSlider::setParameter (const AudioProcessorParameter* p)
{
    if (parameter == p)
        return;
    parameter = p;
    // Repaint because text may change.
    updateText();
    repaint();
}

//#if JUCE_COMPILER_SUPPORTS_LAMBDAS || defined (DOXYGEN)
// wraps SliderAttachment to link with the slider
AudioProcessorParameterSlider::SliderAttachment::SliderAttachment (AudioProcessorValueTreeState& stateToControl, const String& parameterID, AudioProcessorParameterSlider& sliderToControl)
: AudioProcessorValueTreeState::SliderAttachment (stateToControl, parameterID, sliderToControl)
{
    sliderToControl.setParameter(stateToControl.getParameter(parameterID));
}
//#endif

String AudioProcessorParameterSlider::getTextFromValue (double value)
{
    if (parameter == nullptr)
        return Slider::getTextFromValue (value);
    
    // juce::AudioProcessorValueTreeState::SliderAttachment sets the slider minimum and maximum to custom values.
    // We map the range to a 0 to 1 range.
    // assumption : range interval & skew factor have been passed on to the slider when creating the sliderAttachment
    
    const NormalisableRange<double> range (getMinimum(), getMaximum(),getInterval(),getSkewFactor(),isSymmetricSkew());
    const float normalizedVal = (float) range.convertTo0to1 (value);
 
    String result;
    
    result = parameter->getText (normalizedVal, getNumDecimalPlacesToDisplay());
    
    
    if (! textSuffixEnabled)
    {
        String label = parameter->getLabel();
        if (! label.isEmpty() && result.endsWithIgnoreCase (parameter->getLabel()))
        {
            result = result.dropLastCharacters (label.length());
            result.trimEnd();
        }
    }
    
    
    return result;
}
    
    

double AudioProcessorParameterSlider::getValueFromText (const String& text)
{
    if (parameter == nullptr)
        return Slider::getValueFromText (text);
    
    float normalizedVal = parameter->getValueForText (text);
    
    if(!(normalizedVal==normalizedVal))normalizedVal=getMinimum();
    
    const NormalisableRange<double> range (getMinimum(), getMaximum(),getInterval(),getSkewFactor(),isSymmetricSkew());
    
    //double outputValue = jlimit(getMinimum(), getMaximum(), (double) range.convertFrom0to1 (normalizedVal) );
    double outputValue = (double) range.convertFrom0to1 (normalizedVal);
    return outputValue;
}
    
    
void AudioProcessorParameterSlider::setLabel(const String& label){
    parameterLabel = label;
}
    
String AudioProcessorParameterSlider::getLabel() const{
        return parameterLabel;
}




