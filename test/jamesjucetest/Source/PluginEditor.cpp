/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "ParameterConstants.h"

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JamesjucetestAudioProcessorEditor::JamesjucetestAudioProcessorEditor (JamesjucetestAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    createUI();
    
    
    double ratio = 4.0/3.0; // landscape
    setSize(800.0,800.0/ratio);
    

}

JamesjucetestAudioProcessorEditor::~JamesjucetestAudioProcessorEditor()
{
}

//==============================================================================
void JamesjucetestAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void JamesjucetestAudioProcessorEditor::resized()
{
    Rectangle<int> uiBounds = getLocalBounds();//.reduced(0, 20);
    storyboard->setBounds(uiBounds);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}



void JamesjucetestAudioProcessorEditor::createUI()
{
    storyboard = new jamesjuce::Storyboard(processor.getValueTreeState());
    
    float clipperRowY = 0.12f;
    
    storyboard->addElement(new jamesjuce::StoryboardElement(jamesjuce::widgetType::wtBarSlider,
                                                            0.30f,clipperRowY,0.15f,7.0f,
                                                            STORYBOARD_ADD_PARAMS(InLevel),
                                                            false,true,1,false,
                                                            nullptr,nullptr
                                                            )
                           );
    
    
    
    
    storyboard->init();
    
    //    storyboard->setBackground(Drawable::createFromImageData(BinaryData::BackgroundLandscape_svg, BinaryData::BackgroundLandscape_svgSize));
    //
    
    addAndMakeVisible(storyboard);
    
    
}


