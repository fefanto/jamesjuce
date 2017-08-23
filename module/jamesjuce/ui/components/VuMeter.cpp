

VuMeter::VuMeter(float leftPeak/*=0.0f*/, float rightPeak/*=0.0f*/, Type t /*= MonoHorizontal*/) :
type(t),
left_(leftPeak),
right_(rightPeak),
previousValue(0.0f),
minDb_(48.0f),
warnDb_(18.0f),
errDb_(2.0f)
{
 	setOpaque(false);

	colours[outlineColour] = Colours::transparentBlack;
	colours[backgroundColour] = Colours::transparentBlack;
	colours[ledColour] = Colours::lightgreen;
    colours[warnColour] = Colours::yellowgreen;
    colours[errColour] = Colours::orangered;
    colours[ledOffColour] = Colours::lightgrey.withAlpha(0.4f);
    
//    left_=-12.0f;
//    right_=-12.0f;
    DBG("VUMeter::ctor - left=" << String(left_) << " right=" << String(right_));

    
}

void VuMeter::paint(Graphics &g)
{
	switch (type)
	{
	case MonoHorizontal:	drawMonoMeter(g); break;
	case MonoVertical:		drawMonoMeter(g); break;
	case StereoHorizontal:	drawStereoMeter(g); break;
	case StereoVertical:	drawStereoMeter(g); break;
    case MultiChannelVertical:
    case MultiChannelHorizontal:
	case numTypes:          break;
	}
}

void VuMeter::setType(Type newType)
{

	type = newType;
	if (type == StereoHorizontal || type == StereoVertical)
	{
		left_ = -minDb_;
		right_ = -minDb_;
	}
}

void VuMeter::setPeak(float left, float right/*=0.0f*/)
{
    
	if (type == StereoHorizontal || type == StereoVertical)
	{
		left_  -= 3.0f;
		right_ -= 3.0f;
		left_  = jmax(left_, Decibels::gainToDecibels(left));
		right_ = jmax(right_, Decibels::gainToDecibels(right));
		repaint();
	}
	else
	{
        left_  -= 3.0f;
        left_  = jmax(left_, Decibels::gainToDecibels(left));
        repaint();
    }
}



void VuMeter::drawStereoMeter(Graphics &g)
{
    Rectangle<float> bounds = getLocalBounds().toFloat();

    const float ledNumber = 16.0f;

    const float vL    =  roundToInt( ledNumber * jmin(1.0f, (left_ + minDb_) / minDb_));
    const float vR    =  roundToInt( ledNumber * jmin(1.0f, (right_ + minDb_) / minDb_));
    const float vWarn =  roundToInt( ledNumber * jmin(1.0f, (-warnDb_ + minDb_) / minDb_));
    const float vErr  =  roundToInt( ledNumber * jmin(1.0f, (-errDb_ + minDb_) / minDb_));

    const float width = bounds.getWidth();
    const float height = bounds.getHeight();
    
    if (type == StereoHorizontal)
    {
        const float vUnit = height/16.0f ;
        const float hUnit = width/(ledNumber*4.0f + (ledNumber+1)*2.0f) ; // I want to draw 16 leds whatsoever...
        const float minUnit = jmin(vUnit,hUnit);
        
        // Outline - Background & channel Background
        
        g.setColour(colours[backgroundColour]);
        g.fillRoundedRectangle(bounds, minUnit);
        
        g.setColour(colours[outlineColour]);
        g.drawRoundedRectangle(bounds, minUnit, 0.5f);
        
        g.setColour(colours[ledOffColour]);

        for(int i = jmax<float>(vL,0); i < ledNumber; i++){
            g.fillRoundedRectangle(2*hUnit + i*6*hUnit,2*vUnit,  4*hUnit, 4*vUnit, minUnit);
        }
       
        for(int i = 0; i < vL; i++){
            if(i>=vErr)g.setColour(colours[errColour]);
            else if (i<vErr && i>= vWarn)g.setColour(colours[warnColour]);
            else g.setColour(colours[ledColour]);
            g.fillRoundedRectangle(2*hUnit + i*6*hUnit,2*vUnit,  4*hUnit, 4*vUnit, minUnit);
        }

        
        g.setColour(colours[ledOffColour]);
        for(int i = jmax<float>(vR,0); i < ledNumber; i++){
            g.fillRoundedRectangle(2*hUnit + i*6*hUnit,10*vUnit,  4*hUnit, 4*vUnit, minUnit);
        }
        
        for(int i = 0; i < vR; i++){
            if(i>=vErr)g.setColour(colours[errColour]);
            else if (i<vErr && i>= vWarn)g.setColour(colours[warnColour]);
            else g.setColour(colours[ledColour]);
            g.fillRoundedRectangle(2*hUnit + i*6*hUnit,10*vUnit,  4*hUnit, 4*vUnit, minUnit);
        }
        
        
        
        
        
    }
    else if(type == StereoVertical)
    {
    
        const float vUnit = height/(ledNumber*4.0f + (ledNumber+1)*2.0f) ; // I want to draw 16 leds whatsoever...
        const float hUnit = width/16.0f ;
        const float minUnit = jmin(vUnit,hUnit);

        // Outline - Background & channel Background

        g.setColour(colours[backgroundColour]);
        g.fillRoundedRectangle(bounds, minUnit);

        g.setColour(colours[outlineColour]);
        g.drawRoundedRectangle(bounds, minUnit, 0.5f);

        g.setColour(colours[ledOffColour]);
        for(int i = jmax<float>(vL,0); i < ledNumber; i++){
            g.fillRoundedRectangle(2*hUnit, height - (i+1)*6*vUnit , 4*hUnit, 4*vUnit, minUnit);
        }

        for(int i = 0; i < vL; i++){
            if(i>=vErr)g.setColour(colours[errColour]);
            else if (i<vErr && i>= vWarn)g.setColour(colours[warnColour]);
            else g.setColour(colours[ledColour]);
            g.fillRoundedRectangle(2*hUnit, height - (i+1)*6*vUnit , 4*hUnit, 4*vUnit, minUnit);
        }

        g.setColour(colours[ledOffColour]);
        for(int i = jmax<float>(vR,0); i < ledNumber; i++){
            g.fillRoundedRectangle(10*hUnit, height - (i+1)*6*vUnit , 4*hUnit, 4*vUnit, minUnit);
        }

        for(int i = 0; i < vR; i++){
            if(i>=vErr)g.setColour(colours[errColour]);
            else if (i<vErr && i>= vWarn)g.setColour(colours[warnColour]);
            else g.setColour(colours[ledColour]);
            g.fillRoundedRectangle(10*hUnit, height - (i+1)*6*vUnit , 4*hUnit, 4*vUnit, minUnit);
        }
        
        
        
    }
    else{
        jassert(false);
    }

    
    
    return;

}


void VuMeter::drawMonoMeter(Graphics &g)
{
    Rectangle<float> bounds = getLocalBounds().toFloat();
    
    const float ledNumber = 16.0f;
    
    const float vL    =  roundToInt( ledNumber * jmin(1.0f, (left_ + minDb_) / minDb_));
    const float vWarn =  roundToInt( ledNumber * jmin(1.0f, (-warnDb_ + minDb_) / minDb_));
    const float vErr  =  roundToInt( ledNumber * jmin(1.0f, (-errDb_ + minDb_) / minDb_));
    
    const float width = bounds.getWidth();
    const float height = bounds.getHeight();
    
    
    if (type == MonoHorizontal)
    {
        
        
        const float vUnit = height/16.0f ;
        const float hUnit = width/(ledNumber*4.0f + (ledNumber+1)*2.0f) ; // I want to draw 16 leds whatsoever...
        const float minUnit = jmin(vUnit,hUnit);
        
        // Outline - Background & channel Background
        
        g.setColour(colours[backgroundColour]);
        g.fillRoundedRectangle(bounds, minUnit);
        
        g.setColour(colours[outlineColour]);
        g.drawRoundedRectangle(bounds, minUnit, 0.5f);
        
//        g.setGradientFill(ColourGradient(colours[ledOffColour].withAlpha(0.05f),
//                                         0.0f, 0.0f,
//                                         colours[ledOffColour].withAlpha(0.3f),
//                                         0.0f, width, false));
//        
//        g.fillRoundedRectangle(hUnit, vUnit, width  - 2*hUnit , height - 2*vUnit,minUnit);
        
        
        g.setColour(colours[ledOffColour]);
        
        for(int i = jmax<float>(vL,0); i < ledNumber; i++){
            g.fillRoundedRectangle(2*hUnit + i*6*hUnit,2*vUnit,  4*hUnit, 12*vUnit, minUnit);
        }
        
        for(int i = 0; i < vL; i++){
            if(i>=vErr)g.setColour(colours[errColour]);
            else if (i<vErr && i>= vWarn)g.setColour(colours[warnColour]);
            else g.setColour(colours[ledColour]);
            g.fillRoundedRectangle(2*hUnit + i*6*hUnit,2*vUnit,  4*hUnit, 12*vUnit, minUnit);
        }
        
        
        
        
        
        
        
    }
    else if (type == MonoVertical)
    {
        
        const float vUnit = height/(ledNumber*4.0f + (ledNumber+1)*2.0f) ; // I want to draw 16 leds whatsoever...
        const float hUnit = width/16.0f ;
        const float minUnit = jmin(vUnit,hUnit);
        
        
        // Outline - Background & channel Background
        
        g.setColour(colours[backgroundColour]);
        g.fillRoundedRectangle(bounds, minUnit);
        
        g.setColour(colours[outlineColour]);
        g.drawRoundedRectangle(bounds, minUnit, 0.5f);
        
//        g.setGradientFill(ColourGradient(colours[ledOffColour].withAlpha(0.05f),
//                                         0.0f, 0.0f,
//                                         colours[ledOffColour].withAlpha(0.3f),
//                                         0.0f, height, false));
//        
//        
//        // TBD: this is where a mono channel outline occupies most of the background
//        
//        g.fillRoundedRectangle(hUnit, vUnit, width - 2*hUnit , height - 2*vUnit,minUnit);
        

        g.setColour(colours[ledOffColour]);
        for(int i = jmax<float>(vL,0); i < ledNumber; i++){
            g.fillRoundedRectangle(2*hUnit, height - (i+1)*6*vUnit , 12*hUnit, 4*vUnit, minUnit);
        }
        
        for(int i = 0; i < vL; i++){
            if(i>=vErr)g.setColour(colours[errColour]);
            else if (i<vErr && i>= vWarn)g.setColour(colours[warnColour]);
            else g.setColour(colours[ledColour]);
            g.fillRoundedRectangle(2*hUnit, height - (i+1)*6*vUnit , 12*hUnit, 4*vUnit, minUnit);
        }
        
       
        
    }
    else{
        jassert(false);
        
    }
    
    return;
    
    
    
    const float w = (float)getWidth();
    const float h = (float)getHeight();
    
    float v = jlimit<float>(0.0f, 1.0f, left_);
    
    
    
    g.setColour(colours[backgroundColour]);
    g.fillAll();
    
    g.setColour(colours[outlineColour]);
    g.drawRect(getLocalBounds());
    
    if (type == MonoHorizontal)
    {
        const float value = (w - 4.0f) * v;
        
        
        
        
        g.setGradientFill(ColourGradient(colours[ledColour].withMultipliedAlpha(.5f),
                                         0.0f, 0.0f,
                                         colours[ledColour].withMultipliedAlpha(0.2f),
                                         0.0f, h, false));
        
        g.fillRect(2.0f, 2.0f, value, h - 4.0f);
        
        previousValue = value;
        
    }
    
    if (type == MonoVertical)
    {
        g.setGradientFill(ColourGradient(colours[ledColour].withAlpha(0.2f),
                                         0.0f, 0.0f,
                                         colours[ledColour].withAlpha(0.05f),
                                         w, 0.0f, false));
        
        //g.fillRect(2.0f, 2.0f,		  w -4.0f, h - 4.0f);
        
        const float value = h * v;
        const float offset = h * (1.0f - v);
        
        g.setGradientFill(ColourGradient(colours[ledColour],
                                         0.0f, 0.0f,
                                         colours[ledColour].withMultipliedAlpha(0.5f),
                                         0.0f, h, false));
        
        
        Rectangle<int> a((int)2.0f, (int)offset, (int)w - 4, (int)value);
        
        if (w >= 16.0)
        {
            DropShadow d(Colours::white.withAlpha(0.2f), 5, Point<int>());
            
            d.drawForRectangle(g, a);
        }
        
        g.fillRect(a);
        
    }
}

void WaveformComponent::paint(Graphics &g)
{
    Path path;
    
	switch (type)
	{
	case Sine:
	{
		static const unsigned char pathData[] = { 110, 109, 0, 0, 37, 67, 92, 46, 171, 67, 98, 0, 0, 37, 67, 92, 46, 171, 67, 0, 0, 42, 67, 92, 174, 163, 67, 0, 0, 47, 67, 92, 174, 163, 67, 98, 0, 0, 52, 67, 92, 174, 163, 67, 0, 0, 57, 67, 92, 46, 171, 67, 0, 0, 57, 67, 92, 46, 171, 67, 98, 0, 0, 57, 67, 92, 46, 171, 67, 0, 0, 62, 67, 92, 174, 178, 67, 0, 0, 67, 67, 92, 174, 178, 67,
			98, 0, 0, 72, 67, 92, 174, 178, 67, 0, 0, 77, 67, 92, 46, 171, 67, 0, 0, 77, 67, 92, 46, 171, 67, 99, 101, 0, 0 };

		path.loadPathFromData(pathData, sizeof(pathData));

		break;
	}
	case Triangle:
	{
		static const unsigned char pathData[] = { 110, 109, 0, 0, 32, 67, 92, 46, 186, 67, 108, 0, 0, 42, 67, 92, 174, 178, 67, 108, 0, 0, 52, 67, 92, 46, 186, 67, 108, 0, 0, 62, 67, 92, 174, 193, 67, 108, 0, 0, 72, 67, 92, 46, 186, 67, 99, 101, 0, 0 };

		path.loadPathFromData(pathData, sizeof(pathData));

		break;

	}
	case Saw:
	{
		static const unsigned char pathData[] = { 110, 109, 0, 0, 37, 67, 92, 174, 203, 67, 108, 0, 0, 37, 67, 92, 46, 196, 67, 108, 0, 0, 57, 67, 92, 174, 203, 67, 108, 0, 0, 77, 67, 92, 46, 211, 67, 108, 0, 0, 77, 67, 92, 174, 203, 67, 99, 101, 0, 0 };

		path.loadPathFromData(pathData, sizeof(pathData));

		break;

	}
	case Square:
	{
		static const unsigned char pathData[] = { 110, 109, 0, 0, 37, 67, 92, 174, 223, 67, 108, 0, 0, 37, 67, 92, 46, 216, 67, 108, 0, 0, 57, 67, 92, 46, 216, 67, 108, 0, 0, 57, 67, 92, 174, 223, 67, 108, 0, 0, 57, 67, 92, 46, 231, 67, 108, 0, 0, 77, 67, 92, 46, 231, 67, 108, 0, 0, 77, 67, 92, 174, 223, 67, 99, 101, 0, 0 };

		path.loadPathFromData(pathData, sizeof(pathData));
		break;

	}
	case Noise:
	{
		static const unsigned char pathData[] = { 110, 109, 0, 0, 92, 67, 92, 46, 211, 67, 108, 0, 0, 92, 67, 92, 174, 203, 67, 108, 0, 0, 97, 67, 92, 174, 203, 67, 108, 0, 0, 97, 67, 92, 46, 216, 67, 108, 0, 0, 102, 67, 92, 46, 216, 67, 108, 0, 0, 102, 67, 92, 174, 213, 67, 108, 0, 0, 107, 67, 92, 174, 213, 67, 108, 0, 0, 107, 67, 92, 46, 206, 67, 108, 0, 0, 112, 67, 92, 46, 206,
			67, 108, 0, 0, 112, 67, 92, 46, 216, 67, 108, 0, 0, 117, 67, 92, 46, 216, 67, 108, 0, 0, 117, 67, 92, 174, 208, 67, 108, 0, 0, 122, 67, 92, 174, 208, 67, 108, 0, 0, 122, 67, 92, 46, 206, 67, 108, 0, 0, 127, 67, 92, 46, 206, 67, 108, 0, 0, 127, 67, 92, 174, 218, 67, 108, 0, 0, 130, 67, 92, 174, 218, 67, 108, 0, 0, 130, 67, 92, 46,
			211, 67, 99, 101, 0, 0 };

		path.loadPathFromData(pathData, sizeof(pathData));
		break;

	}
	case Custom:
	case numWaveformTypes: break;

	}

	path.scaleToFit(2.0f, 2.0f, (float)getWidth() - 4.0f, (float)getHeight() - 4.0f, false);

	//KnobLookAndFeel::fillPathHiStyle(g, path, getWidth(), getHeight());
}


// FOR REFERENCE ...
//static void fillPathHiStyle(Graphics &g, const Path &p, int width, int height, bool drawBorders=true)
//{
//    
//    
//    if(drawBorders)
//    {
//        g.setColour(Colours::lightgrey.withAlpha(0.8f));
//        g.strokePath (p, PathStrokeType(1.0f));
//        
//        g.setColour(Colours::lightgrey.withAlpha(0.1f));
//        g.drawRect(0, 0, width, height, 1);
//    }
//    
//    g.setGradientFill (ColourGradient (Colour (0x88ffffff),
//                                       0.0f, 0.0f,
//                                       Colour (0x11ffffff),
//                                       0.0f, (float) height,
//                                       false));
//    
//    g.fillPath(p);
//    
//    DropShadow d(Colours::white.withAlpha(drawBorders ? 0.2f : 0.1f), 5, Point<int>());
//    
//    d.drawForPath(g, p);
//    
//};



