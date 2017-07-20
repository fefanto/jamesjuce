#pragma once


class AudioProcessorParameterCarouselButton : public TextButton,  private Button::Listener
{
public:
    AudioProcessorParameterCarouselButton();
    AudioProcessorParameterCarouselButton(const juce::String &componentName);
    
    float getCurrentStep();
    void setCurrentStep(float cs);
    void setNumberOfSteps(float cs);
    void stepAhead();
    void updateTextFromParameter();
    
    void buttonClicked (Button* b) override;
    
    AudioProcessorParameterCarouselButton(AudioProcessorParameter*);
    
    const AudioProcessorParameter* getParameter();

    void setParameter (const AudioProcessorParameter*);

    
    /* 
        CarouselButtonAttachment - To allow for a new type of attachment 
        this must replicate the
        AudioProcessorValueTreeState::ButtonAttachment::Pimpl 
        and 
        AudioProcessorValueTreeState::AttachedcontrolBase 
        Behaviours, which are currently untouchable in cpp files.
     */
    class CarouselButtonAttachment :    public AudioProcessorValueTreeState::Listener,
                                        public AsyncUpdater,
                                        private Button::Listener
    {
    public:
        
        CarouselButtonAttachment (AudioProcessorValueTreeState& stateToControl,
                          const String& parameterID,
                          AudioProcessorParameterCarouselButton& buttonToControl)
        : state (stateToControl), paramID (parameterID), button (buttonToControl), lastValue (0), ignoreCallbacks(false)
        {
            button.setNumberOfSteps((int)state.getParameterRange (parameterID).end);
            
            // from attachedcontrolbase
            state.addParameterListener (paramID, this);
            
            
            // extra bit to allow lambda "travel" to the control text
            buttonToControl.setParameter(stateToControl.getParameter(parameterID));
            buttonToControl.addListener (this);
            

            //ButtonAttachment::Pimpl
            sendInitialUpdate();
            
        }
 
        virtual ~CarouselButtonAttachment()
        {
            // this comes from ButtonAttachment::Pimpl
            button.removeListener (this);
            removeListener();
        }
        
        
        // Methods from AttachedControlBase
        
        void removeListener()
        {
            state.removeParameterListener (paramID, this);
        }
        
        void setNewUnnormalisedValue (float newUnnormalisedValue)
        {
            if (AudioProcessorParameter* p = state.getParameter (paramID))
            {
                const float newValue = state.getParameterRange (paramID)
                .convertTo0to1 (newUnnormalisedValue);
                
                if (p->getValue() != newValue)
                    p->setValueNotifyingHost (newValue);
            }
        }
        
        void sendInitialUpdate()
        {
            if (float* v = state.getRawParameterValue (paramID))
                parameterChanged (paramID, *v);
        }
        
        void parameterChanged (const String&, float newValue) override
        {
            lastValue = newValue;
            
            if (MessageManager::getInstance()->isThisTheMessageThread())
            {
                cancelPendingUpdate();
                setValue (newValue);
            }
            else
            {
                triggerAsyncUpdate();
            }
        }
        
        void beginParameterChange()
        {
            if (AudioProcessorParameter* p = state.getParameter (paramID))
                p->beginChangeGesture();
        }
        
        void endParameterChange()
        {
            if (AudioProcessorParameter* p = state.getParameter (paramID))
                p->endChangeGesture();
        }
        
        void handleAsyncUpdate() override
        {
            setValue (lastValue);
        }
        
        // methods from ButtonAttachment::pimpl (was Marked "override")
        void setValue (float newValue)
        {
            const ScopedLock selfCallbackLock (selfCallbackMutex);
            
            {
                ScopedValueSetter<bool> svs (ignoreCallbacks, true);
                button.setCurrentStep(newValue);
            }
        }
        
        void buttonClicked (Button* b) override
        {
            const ScopedLock selfCallbackLock (selfCallbackMutex);
            
            if (! ignoreCallbacks)
            {
                beginParameterChange();
                button.stepAhead();
                DBG("AudioProcessorParameterCarouselButton::CarouselButtonAttachment : currentStep = " << button.getCurrentStep() );
                setNewUnnormalisedValue (button.getCurrentStep());
                endParameterChange();
            }
        }
        
        
        //Attached ControlBase Members
        AudioProcessorValueTreeState& state;
        String paramID;
        float lastValue;
        
        //BUtton Attachment Members
        AudioProcessorParameterCarouselButton& button;
        bool ignoreCallbacks;
        CriticalSection selfCallbackMutex;
        
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CarouselButtonAttachment)
        
        
    };



    String getTextFromValue (double value);
    double getValueFromText (const juce::String& text);

    protected:
    const AudioProcessorParameter* parameter;

private:
    void initParameter(const AudioProcessorParameter*);
    
    int numberOfSteps;
    int currentStep;

};


