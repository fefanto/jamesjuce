#pragma once


struct SceneController{
    String name;
    int sceneNumber;
    ElementPosition pos;
    LookAndFeel* lookAndfeel;
    ScopedPointer<Button> sceneActivator;
    ScopedPointer<Drawable> sceneBackGround;

    
    SceneController(
                    String nm,
                    int sn,
                    float xpos,
                    float ypos,
                    float xsize,
                    float ar,
                    LookAndFeel* lf = nullptr,
                    Drawable* sb = nullptr
                    )
    :
    name(nm),
    sceneNumber(sn),
    pos(xpos,ypos,xsize,ar),
    lookAndfeel(lf),
    sceneBackGround(sb)
    {
        sceneActivator = new TextButton(name);
        if(lookAndfeel != nullptr){
            sceneActivator->setLookAndFeel(lookAndfeel);
        }
        sceneActivator->setClickingTogglesState(true);
        sceneActivator->setTriggeredOnMouseDown (true);
    
    };
    
    
    ~SceneController()
    {};
    
  
    
};


