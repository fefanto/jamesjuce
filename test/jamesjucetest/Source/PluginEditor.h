/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class JamesjucetestAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    JamesjucetestAudioProcessorEditor (JamesjucetestAudioProcessor&);
    ~JamesjucetestAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void createUI();
    
    ScopedPointer<jamesjuce::Storyboard> storyboard;
    
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JamesjucetestAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JamesjucetestAudioProcessorEditor)
};
