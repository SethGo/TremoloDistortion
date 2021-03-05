/*
  ==============================================================================

    MixComponent.h
    Created: 3 Mar 2021 8:52:21pm
    Author:  Seth Gory

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLAF.h"

//==============================================================================
/*
*/
class MixComponent  : public juce::Component
{
public:
    MixComponent(TremDistortionAudioProcessor&);
    ~MixComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CustomLAF customLAF;
    
    juce::Slider mixSlider;
    juce::Label mixLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;
    
    TremDistortionAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixComponent)
};
