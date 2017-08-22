

#pragma once



/** A Slider-style component that displays peak values.
*	@ingroup components
*
*	The best practice for using one of those is a Timer that regularly
*	calls setPeak() in its timerCallback().
*
*   started from HISE VUMeter class : https://github.com/christophhart/HISE
*
*
*/


static constexpr int const max_IO_Channels = 16;// ins & outs;


class VuMeter: public Component
                        //,public SettableTooltipClient
{
public:

	/** The Style of the vu meter. */
	enum Type
	{
		MonoHorizontal = 0, ///< a non segmented mono meter with linear range (0.0 - 1.0)
		MonoVertical, ///< a vertical version of the MonoHorizontal Style (not yet implemented)
		StereoHorizontal, ///< a segmented stereo meter with logarithmic range (-100dB - 0dB)
		StereoVertical, ///< a vertical version of StereoHorizontal
		MultiChannelVertical,
		MultiChannelHorizontal,
		numTypes
	};

	/** The ColourIds that can be changed with setColour. */
	enum ColourId
	{
		outlineColour = 0, ///< the outline colour
		ledColour, ///< the colour of the segmented leds or the mono-bar 
		backgroundColour, ///< the background colour
        warnColour,
        errColour,
        ledOffColour,
        numColours
    };

	/** Creates a new VuMeter. */
	VuMeter(float leftPeak=0.0f, float rightPeak=0.0f, Type t = StereoVertical);

	~VuMeter() {};

	/** Change the colour of the VuMeter. */
	void setColour(ColourId id, Colour newColour) {	colours[id] = newColour; };

	void paint(Graphics &g) override;;

	

	/** Change the Type of the VuMeter. */
	void setType(Type newType);;

	/** sets a new peak level. 
	*
	*	For stereo meters there is a peak logic with decibel conversion and decreasing level, 
	*	and for monophonic VuMeters it simply displays the 'left' value. */
	void setPeak(float left, float right=0.0f);
    
    void setMinDb(float minDb){ minDb_ = fabs(minDb); };
    
	void setPeakMultiChannel(float *numbers, int numChannels);

private:

	void drawMonoMeter(Graphics &g);

	void drawStereoMeter(Graphics &g);;



	Colour colours[numColours];

  
    Type type;

    float left_;
    float right_;
 
    float previousValue;
    
    float minDb_;
    float warnDb_;
    float errDb_;
    
	float multiChannels[max_IO_Channels];
	int numChannels;

};



class WaveformComponent: public Component
{
public:

	enum WaveformType
	{
		Sine = 1,
		Triangle,
		Saw,
		Square,
		Noise,
		Custom,
		numWaveformTypes
	};

	WaveformComponent():
		type(Sine)
	{};

	void mouseDown(const MouseEvent &)
	{
		if (selector != nullptr)
		{
			selector->showPopup();
		}
	}

	void setSelector(ComboBox *b)
	{
		selector = b;
	}

	void paint(Graphics &g);

	void setType(int t)
	{
		type = (WaveformType)t;
		repaint();
	}

private:

	WaveformType type;

	Component::SafePointer<ComboBox> selector;

};

