#pragma once



typedef OwnedArray<SceneController> SceneControllers;
typedef OwnedArray<StoryboardElement> StoryboardElements;


class Storyboard : public Component, public ButtonListener
{
private:
    AudioProcessorValueTreeState& valueTreeState;
    StoryboardElements storyboardElements;
    SceneControllers sceneControllers;
    
    ScopedPointer<Drawable> background;
    int currentScene;

private:
  
    // containers to retain ownership of widgets and delete them...
    OwnedArray<Component> controls;
    OwnedArray<Label> labels;
    OwnedArray<AudioProcessorParameterSlider::SliderAttachment> paramSlidersAttachments;
    OwnedArray<AudioProcessorParameterTextButton::ButtonAttachment> paramTextButtonAttachments;
    OwnedArray<AudioProcessorParameterToggleButton::ButtonAttachment> paramToggleButtonAttachments;
    OwnedArray<AudioProcessorParameterCarouselButton::CarouselButtonAttachment> paramCarouselButtonAttachments;
    
    Array<AudioProcessorParameterSlider*> timeSyncableSliders;
    
public:
    
    Storyboard(AudioProcessorValueTreeState& vts)
    :valueTreeState(vts),
    currentScene(1),
    background(nullptr)
    {}
    
    
    
    virtual ~Storyboard(){};
    
    void updateTimeSyncableSliders(){
        for(auto s : timeSyncableSliders)
        {
            DBG("updating syncable slider : " << s->getName());
            s->updateText();
            s->repaint();
        }
    }
    
    void setBackground(Drawable* bckgnd){
        background = bckgnd;
    }
    
    void addElement(StoryboardElement* el){
        storyboardElements.add(el);
    }
    
    void addSceneController(SceneController* sc){
        // sanity check
        for(SceneController* existingSc : sceneControllers)
        {
            jassert(existingSc->sceneNumber != sc->sceneNumber);
        }
        
        
        sceneControllers.add(sc);
        
    }
    
    
    virtual void buttonClicked (Button* eventSource) override{
        
        for(SceneController* sc : sceneControllers)
        {
            if(eventSource == sc->sceneActivator){
                //DBG("changing scene to #" << sc->sceneNumber);
                sceneChanged(sc->sceneNumber);
                eventSource->setToggleState(true, dontSendNotification);

            }
            else{
                //DBG("untoggle scenecontroller #" << sc->sceneNumber);
                sc->sceneActivator->setToggleState(false, dontSendNotification);
            }
        }
        repaint();
        
    }
    
    void sceneChanged(int newSceneNumber){
        for(StoryboardElement* el : storyboardElements)
        {
            el->sceneChanged(newSceneNumber);
        }
        
        
        currentScene = newSceneNumber;
    }
    
    
    
    void init()
    {
        timeSyncableSliders.clear();
    
        // temporaries
        AudioProcessorParameterSlider* aSlider;
        AudioProcessorParameterSlider::SliderAttachment* aSliderAttach;

        
        AudioProcessorParameterTextButton* aTextButton;
        AudioProcessorParameterTextButton::ButtonAttachment* aTextButtonAttach;

        
        AudioProcessorParameterCarouselButton* aCarouselButton;
        AudioProcessorParameterCarouselButton::CarouselButtonAttachment* aCarouselButtonAttach;
        
        // TBD: for (StoryboardElement sel :  storyboardElements)
        for (int i = 0; i < storyboardElements.size(); ++i)
        {
            String paramId = storyboardElements[i]->paramId;
            String paramName = storyboardElements[i]->paramName;
            String paramLabel = storyboardElements[i]->paramLabel;
            bool paramAutoToggle = storyboardElements[i]->autoToggle;
            bool paramSyncable = storyboardElements[i]->timesyncable;
            
            bool showLabel = storyboardElements[i]->showLabel;
            AudioProcessorParameterWithID* param = valueTreeState.getParameter(paramId);
            
            if(showLabel)
            {
                Label* aLabel = new Label(paramId,paramLabel);
                aLabel->setJustificationType(Justification::centred);
                labels.add(aLabel);
                addAndMakeVisible(aLabel);
                storyboardElements[i]->setLabel(aLabel);
            }
            

            
            switch(storyboardElements[i]->wType){
                case wtRotarySlider:
                {
                   
                    addAndMakeVisible(aSlider = new AudioProcessorParameterSlider(paramName,Slider::RotaryVerticalDrag,Slider::TextBoxBelow));
                    aSlider->setParameter(param);
                    aSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 1, 1);
                    paramSlidersAttachments.add(aSliderAttach = new AudioProcessorParameterSlider::SliderAttachment (valueTreeState, paramId, *aSlider));
                    controls.add(aSlider);
                    
                    storyboardElements[i]->setWidget(aSlider);
                    
                    if(paramSyncable){
                        timeSyncableSliders.add(aSlider);
                    }
                    
                    // manca gestione param listener per dragEnded/undo
                    
                    break;
                }
                case wtBarSlider:
                {
                    
                    addAndMakeVisible(aSlider = new AudioProcessorParameterSlider(paramName,Slider::LinearBar,Slider::TextBoxBelow));
                    aSlider->setParameter(param);
                    aSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 1, 1);
                    paramSlidersAttachments.add(aSliderAttach = new AudioProcessorParameterSlider::SliderAttachment (valueTreeState, paramId, *aSlider));
                    controls.add(aSlider);
                    
                    storyboardElements[i]->setWidget(aSlider);
                    
                    if(paramSyncable){
                        timeSyncableSliders.add(aSlider);
                    }
                    
                    
                    // manca gestione param listener per dragEnded/undo
                    
                    break;
                }
                case wtButton:
                {
                    
                    addAndMakeVisible( aTextButton = new AudioProcessorParameterTextButton(paramName) );
                                      
                    aTextButton->setParameter(param,paramAutoToggle); // manca gestione autotoggle
                    
                    
                    paramTextButtonAttachments.add(aTextButtonAttach = new AudioProcessorParameterTextButton::ButtonAttachment (valueTreeState, paramId, *aTextButton));
                    
                    controls.add(aTextButton);
                    storyboardElements[i]->setWidget(aTextButton);
                   
                    break;
                }
                case wtCarouselButton:
                {
                    
                    addAndMakeVisible( aCarouselButton = new AudioProcessorParameterCarouselButton(paramName) );
                    
                    //aCarouselButton->setParameter(param); // manca gestione autotoggle
                    
                    
                    paramCarouselButtonAttachments.add(aCarouselButtonAttach = new AudioProcessorParameterCarouselButton::CarouselButtonAttachment (valueTreeState, paramId, *aCarouselButton));
                    
                    controls.add(aCarouselButton);
                    storyboardElements[i]->setWidget(aCarouselButton);
                    
                    break;
                }
                    
                default:
                {
                    jassertfalse;
                    break;
                }
                    
            }
            
        }
        
        
        for (int i = 0; i < sceneControllers.size(); ++i)
        {
            if(sceneControllers[i]->sceneActivator != nullptr)
            {
                addAndMakeVisible(sceneControllers[i]->sceneActivator);
                sceneControllers[i]->sceneActivator->addListener(this);
                sceneControllers[i]->sceneActivator->setClickingTogglesState(true);
                sceneControllers[i]->sceneActivator->setTriggeredOnMouseDown (true);

            }
            
        }
        
        
        sceneChanged(currentScene);
        
        
    
    };
    
    
    void paint (Graphics& g) override{
        Rectangle<float> bounds = getLocalBounds().toFloat();
        if(background!=nullptr){
            background->drawWithin(g, bounds, RectanglePlacement::Flags::stretchToFit, 1.0);
        }
        
        for(auto sc : sceneControllers)
        {
            Drawable* sb = sc->getSceneBackground();
            if( (sb!=nullptr) && (currentScene == sc->getSceneNumber()) )
                sb->drawWithin(g, bounds, RectanglePlacement::Flags::stretchToFit, 1.0);
        }
            


    }
    
    
    void resized() override
    {
        Rectangle<float> bounds = getLocalBounds().toFloat();
        Rectangle<float> widgetbounds;
        
        //jassert(storyboardElements.size()==controls.size());
        //jassert(controls.size()==labels.size());
        
        
        for (int i = 0; i < storyboardElements.size(); ++i)
        {
            widgetbounds.setPosition(bounds.getWidth()*storyboardElements[i]->pos.xPosPercent,
                                     bounds.getHeight()*storyboardElements[i]->pos.yPosPercent
                                     );
            widgetbounds.setSize(bounds.getWidth()*storyboardElements[i]->pos.xSizePercent,
                                 bounds.getWidth()*storyboardElements[i]->pos.xSizePercent*(1.0f/storyboardElements[i]->pos.aspectRatio)
                                 );
            
            Slider* tmpsl = dynamic_cast<Slider*>(controls[i]);
            if(tmpsl!= nullptr){
                tmpsl->setTextBoxStyle(Slider::TextBoxBelow, false, (int)(widgetbounds.getWidth()*0.9f), (int)(widgetbounds.getHeight()*0.15f) );
            }
            
            storyboardElements[i]->widget->setBounds(widgetbounds.toNearestInt());
 
            
            if(storyboardElements[i]->showLabel){
                jassert(storyboardElements[i]->label != nullptr);
                Rectangle<float> labelbounds = widgetbounds;
                float labelHeight = bounds.getWidth()*0.02f;
                labelbounds = labelbounds.withY(labelbounds.getY()-1.2f*labelHeight).withHeight(labelHeight);
                BorderSize<int> bs = storyboardElements[i]->label->getBorderSize();
                bs.setTop((int)(labelHeight/4.0f));
                bs.setBottom((int)(labelHeight/4.0f));
                storyboardElements[i]->label->setBorderSize(bs);
                storyboardElements[i]->label->setBounds(labelbounds.toNearestInt());
                storyboardElements[i]->label->setMinimumHorizontalScale(0.1f);
            }
            
        }
        
        
        for (int i = 0; i < sceneControllers.size(); ++i)
        {
            widgetbounds.setPosition(bounds.getWidth()*sceneControllers[i]->pos.xPosPercent,
                                     bounds.getHeight()*sceneControllers[i]->pos.yPosPercent
                                     );
            widgetbounds.setSize(bounds.getWidth()*sceneControllers[i]->pos.xSizePercent,
                                 bounds.getWidth()*sceneControllers[i]->pos.xSizePercent*(1.0f/sceneControllers[i]->pos.aspectRatio)
                                 );
            
            sceneControllers[i]->sceneActivator->setBounds(widgetbounds.toNearestInt());
        }
        
    }
    
    
    void invalidate()
    {
        for (int i = 0; i < controls.size(); ++i)
        {
            Slider* tmpsl = dynamic_cast<Slider*>(controls[i]);
            if(tmpsl!= nullptr){
                tmpsl->updateText();
            }
            controls[i]->repaint();
            
        }
        
    }
    


    
    
};
