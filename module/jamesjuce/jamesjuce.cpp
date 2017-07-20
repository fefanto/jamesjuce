/*
  ==============================================================================

  

  ==============================================================================
*/

#if defined (__STK_STKHEADER__) && ! JUCE_AMALGAMATED_INCLUDE
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE cpp file"
#endif

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"

#include "jamesjuce.h"

// stops a warning with clang
#ifdef __clang__
 #pragma clang diagnostic ignored "-Wtautological-compare"
#endif

#if JUCE_MSVC
 #pragma warning (push)
 #pragma warning (disable: 4127 4702 4244 4305 4100 4996 4309)
#endif

namespace jamesjuce
{

    
#include "utils/PluginTempoSync.cpp"

#include "dsp/utils/PerformanceValue.cpp"
#include "dsp/utils/AudioMixer.cpp"

#include "ui/parametercomponents/AudioProcessorParameterSlider.cpp"
#include "ui/parametercomponents/AudioProcessorParameterTextButton.cpp"
#include "ui/parametercomponents/AudioProcessorParameterToggleButton.cpp"
#include "ui/parametercomponents/AudioProcessorParameterCarouselButton.cpp"

    
}

#if JUCE_MSVC
#pragma warning (pop)
 #pragma warning (disable: 4127 4702 4244 4305 4100 4996 4309)
#endif

#ifdef __clang__
 #pragma pop // -Wtautological-compare
#endif
