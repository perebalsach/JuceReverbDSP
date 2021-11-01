/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessor::ReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ReverbAudioProcessor::~ReverbAudioProcessor()
{
}

//==============================================================================
const juce::String ReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1;

    leftReverb.prepare(spec);
    rightReverb.prepare(spec);

    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void ReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

   
    params.roomSize     = *apvts.getRawParameterValue("size");
    params.damping      = *apvts.getRawParameterValue("damp");
    params.width        = *apvts.getRawParameterValue("width");
    params.wetLevel     = *apvts.getRawParameterValue("dw");
    params.dryLevel     = 1.0f - *apvts.getRawParameterValue("dw");
    params.freezeMode   = *apvts.getRawParameterValue("freeze");

    leftReverb.setParameters(params);
    rightReverb.setParameters(params);

    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    leftReverb.process(leftContext);
    rightReverb.process(rightContext);

    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    auto* channelData = buffer.getWritePointer (channel);

    //    // ..do something to the data...
    //}
}

//==============================================================================
bool ReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ReverbAudioProcessor::createEditor()
{
    return new ReverbAudioProcessorEditor (*this);
}

//==============================================================================
void ReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout ReverbAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat> ("size",
                                                            "size",
                                                            juce::NormalisableRange<float>(.0f, 1.f, 0.001f, 1.f),
                                                            .5f,
                                                            juce::String(),
                                                            juce::AudioProcessorParameter::genericParameter,
                                                            [](float value, int) {
                                                                if (value * 100 < 10.f)
                                                                    return juce::String(value * 100, 2);
                                                                else if (value * 100 < 100.f)
                                                                    return juce::String(value * 100, 1);
                                                                else
                                                                    return juce::String(value * 100, 0); },
                                                            nullptr));

    layout.add(std::make_unique<juce::AudioParameterFloat> ("damp",
                                                            "damp",
                                                            juce::NormalisableRange<float>(.0f, 1.f, 0.001f, 1.f),
                                                            .5f,
                                                            juce::String(),
                                                            juce::AudioProcessorParameter::genericParameter,
                                                            [](float value, int) {
                                                                if (value * 100 < 10.f)
                                                                    return juce::String(value * 100, 2);
                                                                else if (value * 100 < 100.f)
                                                                    return juce::String(value * 100, 1);
                                                                else
                                                                    return juce::String(value * 100, 0); },
                                                            nullptr));

    layout.add(std::make_unique<juce::AudioParameterFloat> ("width",
                                                            "width",
                                                            juce::NormalisableRange<float>(.0f, 1.f, 0.001f, 1.f),
                                                            .5f,
                                                            juce::String(),
                                                            juce::AudioProcessorParameter::genericParameter,
                                                            [](float value, int) {
                                                                if (value * 100 < 10.f)
                                                                    return juce::String(value * 100, 2);
                                                                else if (value * 100 < 100.f)
                                                                    return juce::String(value * 100, 1);
                                                                else
                                                                    return juce::String(value * 100, 0); },
                                                            nullptr));

    layout.add(std::make_unique<juce::AudioParameterFloat> ("dw",
                                                            "dw",
                                                            juce::NormalisableRange<float>(.0f, 1.f, 0.001f, 1.f),
                                                            .5f,
                                                            juce::String(),
                                                            juce::AudioProcessorParameter::genericParameter,
                                                            [](float value, int) {
                                                                if (value * 100 < 10.f)
                                                                    return juce::String(value * 100, 2);
                                                                else if (value * 100 < 100.f)
                                                                    return juce::String(value * 100, 1);
                                                                else
                                                                    return juce::String(value * 100, 0); },
                                                            nullptr));

    layout.add(std::make_unique<juce::AudioParameterBool>("freeze", "freeze", false));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverbAudioProcessor();
}
