/*
  ==============================================================================

    LFOComponent.h
    Created: 3 Mar 2021 8:54:26pm
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
class LFOComponent  : public juce::Component
{
public:
    LFOComponent(TremDistortionAudioProcessor&);
    ~LFOComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TremDistortionAudioProcessor& audioProcessor;
    CustomLAF customLAF;
    
    juce::Slider lfoRateSlider;
    juce::Slider lfoDepthSlider;
    
    juce::Label sectionHeading;
    juce::Label rateLabel;
    juce::Label depthLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoRateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoDepthSliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};
