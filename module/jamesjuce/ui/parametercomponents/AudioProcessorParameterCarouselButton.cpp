

AudioProcessorParameterCarouselButton::AudioProcessorParameterCarouselButton()
: numberOfSteps(1),currentStep(1)
{
    initParameter(nullptr);
}

AudioProcessorParameterCarouselButton::AudioProcessorParameterCarouselButton (AudioProcessorParameter* p)
{
    initParameter(p);
}

AudioProcessorParameterCarouselButton::AudioProcessorParameterCarouselButton (const String &componentName)
{
    setName(componentName);
    initParameter(nullptr);
}

void AudioProcessorParameterCarouselButton::initParameter (const AudioProcessorParameter* p)
{
    parameter = p;
}

const AudioProcessorParameter* AudioProcessorParameterCarouselButton::getParameter()
{
    jassert(parameter!=nullptr);
    return parameter;
}

void AudioProcessorParameterCarouselButton::setParameter (const AudioProcessorParameter* p)
{
    if (parameter == p)
        return;
    
    parameter = p;
    /*
     This button does not use the toggle state to manage its value
     */
    setClickingTogglesState(false);
    setTriggeredOnMouseDown (true);
    
    float value = parameter->getValue();
    String buttonText = getTextFromValue(parameter->getValue());

    setButtonText(buttonText);
    
    //repaint();
    
    /*
     will get click info to update button text
     */
    addListener(this);
}

float AudioProcessorParameterCarouselButton::getCurrentStep(){
    return (float)currentStep;
}

void AudioProcessorParameterCarouselButton::setCurrentStep(float cs){
    jassert(cs>=0 && cs <= numberOfSteps);
    bool dirty = cs !=currentStep;
    currentStep = cs;
    if(dirty)updateTextFromParameter();
}

void AudioProcessorParameterCarouselButton::setNumberOfSteps(float ns){
    jassert(ns>=1);
    numberOfSteps = ns;
}

void AudioProcessorParameterCarouselButton::stepAhead(){
    currentStep = currentStep+1;
    currentStep = currentStep % (numberOfSteps+1);
}

void AudioProcessorParameterCarouselButton::updateTextFromParameter()
{
    String buttonText = getTextFromValue(parameter->getValue());
    setButtonText(buttonText);
    
}


void AudioProcessorParameterCarouselButton::buttonClicked (Button* b)
{
    //stepAhead();
    DBG("AudioProcessorParameterCarouselButton::buttonClicked : currentStep = " << currentStep << " - numberOfSteps = "<< numberOfSteps );
    updateTextFromParameter();
    
}



String AudioProcessorParameterCarouselButton::getTextFromValue (double value)
{
    if (parameter == nullptr)
        return String (value);

    // assuming createAndAddParamter was issued with a 0/1 range!
    const NormalisableRange<double> range (0.0f, 1.0f);
    const float normalizedVal = (float) range.convertTo0to1 (value);

    String result = parameter->getText (normalizedVal, 1);
    
    return result;
  
}
    
    

double AudioProcessorParameterCarouselButton::getValueFromText (const String& text)
{
    if (parameter == nullptr)
        return 0.0;/*ONLY SLIDER WHAT NOW WITH BUTTON ???*/ //Slider::getValueFromText (text);
    return parameter->getValueForText (text);
}

