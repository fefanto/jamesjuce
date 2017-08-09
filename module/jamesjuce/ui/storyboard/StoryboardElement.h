#pragma once



enum widgetType{
    wtRotarySlider,
    wtBarSlider,
    wtIncDecSlider,
    wtButton,
    wtCarouselButton,
};

struct ElementPosition
{
    ElementPosition() noexcept
        :xPosPercent(0.0f),
         yPosPercent(0.0f),
         xSizePercent(0.0f),
         aspectRatio(1.0f)
    {};
    
    ElementPosition(const ElementPosition& other) noexcept
    :xPosPercent(other.xPosPercent),
    yPosPercent(other.yPosPercent),
    xSizePercent(other.xSizePercent),
    aspectRatio(other.aspectRatio)
    {};
    
    ElementPosition(float x, float y, float w, float ar) noexcept
    :xPosPercent(x),
    yPosPercent(y),
    xSizePercent(w),
    aspectRatio(ar)
    {};


    ~ElementPosition(){};
    
    float xPosPercent;
    float yPosPercent;
    float xSizePercent;
    float aspectRatio;
    
   
};


struct StoryboardElement{
    
    StoryboardElement(
                          widgetType w,
                          float xpos,
                          float ypos,
                          float xsize,
                          float ar,
                          String pid,
                          String pname,
                          String pLabel,
                          bool at = false,
                          bool sl=true,
                          int sid = 0,
                          bool ts = false,
                          LookAndFeel* lf = nullptr,
                          LookAndFeel* lbllf = nullptr
                      )
    :wType(w),
    pos(xpos,ypos,xsize,ar),
    sceneId(sid),
    autoToggle(at),
    paramId(pid),
    paramName(pname),
    paramLabel(pLabel),
    showLabel(sl),
    timesyncable(ts),
    lookAndfeel(lf),
    labelLookAndfeel(lbllf),
    widget(nullptr),
    label(nullptr)
    {};
    
    
    ~StoryboardElement()
    {};
 
 
    widgetType wType;
    ElementPosition pos;
    
    int sceneId;
    
    String paramId;
    String paramName;
    String paramLabel;
    
    bool showLabel;
    bool timesyncable;
    bool autoToggle;
    LookAndFeel* lookAndfeel;
    LookAndFeel* labelLookAndfeel;
    
    
    Component* widget;
    Label* label;
    
    void setWidget(Component* w){
        widget = w;
        
        if(lookAndfeel!=nullptr)
            widget->setLookAndFeel(lookAndfeel);
    };
    
    void setLabel(Label* l){
        label = l;
        if(labelLookAndfeel!=nullptr)
            label->setLookAndFeel(labelLookAndfeel);
    }
    
    void sceneChanged(int newSceneNumber)
    {
        jassert(widget!=nullptr);
        if(widget!=nullptr)
            widget->setVisible( ( sceneId == newSceneNumber ) || (sceneId == 0) );
       
        if(label!=nullptr)
            label->setVisible( ( sceneId == newSceneNumber ) || (sceneId == 0) );
        
        
    }
    
    
};


