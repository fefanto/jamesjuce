/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "ParameterConstants.h"


#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JamesjucetestAudioProcessor::JamesjucetestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    initValueTreeState();
    

}

JamesjucetestAudioProcessor::~JamesjucetestAudioProcessor()
{
}

//==============================================================================
const String JamesjucetestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JamesjucetestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JamesjucetestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double JamesjucetestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JamesjucetestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JamesjucetestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JamesjucetestAudioProcessor::setCurrentProgram (int index)
{
}

const String JamesjucetestAudioProcessor::getProgramName (int index)
{
    return {};
}

void JamesjucetestAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JamesjucetestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JamesjucetestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JamesjucetestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JamesjucetestAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool JamesjucetestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JamesjucetestAudioProcessor::createEditor()
{
    return new JamesjucetestAudioProcessorEditor (*this);
}

//==============================================================================
void JamesjucetestAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JamesjucetestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void JamesjucetestAudioProcessor::parameterChanged	(	const String & 	parameterID, float 	newValue){
    
    DBG("Parameter Changed : ID = " << parameterID << " - newValue = " << newValue);
    if(parameterID==PARAMETER_ID_STRING(InLevel)){
        DBG("IN LEVEL!!!!!");
    }
    
}


void JamesjucetestAudioProcessor::initValueTreeState(){
    
    parameters = new AudioProcessorValueTreeState(*this,nullptr); // TBD sub with plugin core
    
    parameters->createAndAddParameter(VTS_ADD_PARAMS(InLevel,jamesjuce::ParameterLambdas::dbValueToTextFunction,jamesjuce::ParameterLambdas::numericTextToValueFunction));

    parameters->state = ValueTree (Identifier (JucePlugin_Name));
    parameters->state.setProperty("version", JucePlugin_VersionString, nullptr);
    
    parameters->addParameterListener(PARAMETER_ID_VARIABLE(InLevel), this);
    
    
}




    //==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JamesjucetestAudioProcessor();
}
