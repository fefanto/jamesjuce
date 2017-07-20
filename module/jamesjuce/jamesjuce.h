/*
  ==============================================================================


  ==============================================================================
*/

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:               jamesjuce
    vendor:           fefanto
    version:          1.0.0
    name:             jamesjuce
    description:      JUCE utils module for plugin development. 
    website:          https://www.fefanto.com
    dependencies:     juce_core,  juce_audio_basics, juce_audio_processors, juce_gui_basics, juce_graphics

END_JUCE_MODULE_DECLARATION 
*/

#ifndef __JAMESJUCE_H_INCLUDED__
#define __JAMESJUCE_H_INCLUDED__

#if JUCE_LITTLE_ENDIAN && ! defined (__LITTLE_ENDIAN__)
 #define __LITTLE_ENDIAN__
#endif

#if JUCE_MAC
 #define __MACOSX_CORE__
#endif

#if JUCE_MSVC
 #pragma warning (push)
 #pragma warning (disable: 4127 4702 4244 4305 4100 4996 4309)
#endif


/*
 ATTENTION PEOPLE: include here the juce module headers that you need to see the juce objects in this module (this list of headers must be in sync with the dependencies list in the above JUCE_MODULE_DECLARATION
 */
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>

#include <atomic>

#ifdef JUCE_WINDOWS
#define _USE_MATH_DEFINES 
#include <math.h>
#endif

using namespace juce;



namespace jamesjuce
{

#include "utils/PluginParameterUnits.h"
#include "utils/PluginParameterValueLambdas.h"
#include "utils/PluginTempoSync.h"

#include "dsp/utils/PerformanceValue.h"
#include "dsp/utils/LowPassSmoothedValue.h"
#include "dsp/utils/AudioMixer.h"

#include "ui/parametercomponents/AudioProcessorParameterSlider.h"
#include "ui/parametercomponents/AudioProcessorParameterTextButton.h"
#include "ui/parametercomponents/AudioProcessorParameterToggleButton.h"
#include "ui/parametercomponents/AudioProcessorParameterCarouselButton.h"

#include "ui/storyboard/StoryBoardElement.h"
#include "ui/storyboard/SceneController.h"
#include "ui/storyboard/StoryBoard.h"
    
#include "utils/PluginParameterMacros.h"
    
}

#if JUCE_MSVC
 #pragma warning (pop)
#endif

#endif   // __STK_STKHEADER__
