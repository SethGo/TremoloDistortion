/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>
#define PI 3.141592653

//==============================================================================
TremDistortionAudioProcessor::TremDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParameters())
#endif
{
    apvts.addParameterListener ("GAIN1", this);
    apvts.addParameterListener ("TONE1", this);
    apvts.addParameterListener ("VOL1", this);
    
    apvts.addParameterListener ("GAIN2", this);
    apvts.addParameterListener ("TONE2", this);
    apvts.addParameterListener ("VOL2", this);
    
    apvts.addParameterListener ("MIX", this);
    
    apvts.addParameterListener ("RATE", this);
    apvts.addParameterListener ("DEPTH", this);
}

TremDistortionAudioProcessor::~TremDistortionAudioProcessor()
{
    apvts.removeParameterListener ("GAIN1", this);
    apvts.removeParameterListener ("TONE1", this);
    apvts.removeParameterListener ("VOL1", this);
    
    apvts.removeParameterListener ("GAIN2", this);
    apvts.removeParameterListener ("TONE2", this);
    apvts.removeParameterListener ("VOL2", this);
    
    apvts.removeParameterListener ("MIX", this);
    
    apvts.removeParameterListener ("RATE", this);
    apvts.removeParameterListener ("DEPTH", this);
}

//==============================================================================
const juce::String TremDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TremDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TremDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TremDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TremDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TremDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TremDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TremDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TremDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void TremDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TremDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TremDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TremDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void TremDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    int numSamples = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, numSamples);
    
    if (paramsNeedUpdating)
    {
        updateParams();
    }
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < numSamples; sample++)
        {
            float signalSplit1 = channelData[sample];
            float signalSplit2 = channelData[sample];
            
            // Ditortion 1, Bounded Sine foldover waveshaper
            signalSplit1 = std::tanh ((signalSplit1 + ((distData[0] * 10.00f) * (std::sin (signalSplit1 * (distData[1] * 300.0f)))))) * distData[2];

            // Distortion 2, Tanh waveshaper with LPF pre-filter
            // (add LPF filter before tanh)
            signalSplit2 = std::tanh (signalSplit2 * (distData[3] * 250.00f)) * distData[5];
            
            // Combine each distorted signal
            channelData[sample] = (signalSplit1 * (1 - mix)) + (signalSplit2 * mix);
        }
    }
}

//==============================================================================
bool TremDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TremDistortionAudioProcessor::createEditor()
{
    return new TremDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void TremDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TremDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TremDistortionAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout TremDistortionAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("GAIN1", "Gain1", juce::NormalisableRange<float> (0.01f, 1.0f), 0.2f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("TONE1", "Tone1", juce::NormalisableRange<float> (0.01f, 1.0f), 0.50f)); 
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("VOL1", "Vol1", juce::NormalisableRange<float> (0.0f, 1.0f), 0.50f));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("GAIN2", "Gain2", juce::NormalisableRange<float> (0.01f, 1.0f), 0.6f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("TONE2", "Tone2", juce::NormalisableRange<float> (0.01f, 1.0f), 0.50f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("VOL2", "Vol2", juce::NormalisableRange<float> (0.00f, 1.0f), 0.50f));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("MIX", "Mix", 0.00f, 1.00f, 0.50f));
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("RATE", "Rate", 0.00f, 1.00f, 0.50f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("DEPTH", "Depth", 0.00f, 1.00f, 0.50f));
    
    return { params.begin(), params.end() };
}

void TremDistortionAudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    paramsNeedUpdating = true;
}

void TremDistortionAudioProcessor::updateParams()
{
    setDistData();
    setMix();
    setLfoData();
    paramsNeedUpdating = false;
}

void TremDistortionAudioProcessor::setDistData()
{
    float gain1 = apvts.getRawParameterValue ("GAIN1")->load();
    float tone1 = apvts.getRawParameterValue ("TONE1")->load();
    float vol1 = apvts.getRawParameterValue ("VOL1")->load();
    
    float gain2 = apvts.getRawParameterValue ("GAIN2")->load();
    float tone2 = apvts.getRawParameterValue ("TONE2")->load();
    float vol2 = apvts.getRawParameterValue ("VOL2")->load();
    
    distData[0] = gain1;
    distData[1] = tone1;
    distData[2] = vol1;
    distData[3] = gain2;
    distData[4] = tone2;
    distData[5] = vol2;
}

void TremDistortionAudioProcessor::setLfoData()
{
    float rate = apvts.getRawParameterValue ("RATE")->load();
    float depth = apvts.getRawParameterValue ("DEPTH")->load();
    
    lfoData[0] = rate;
    lfoData[1] = depth;
}

void TremDistortionAudioProcessor::setMix()
{
    mix = apvts.getRawParameterValue ("MIX")->load();
}
