/*
  ==============================================================================

    Dist1Component.h
    Created: 3 Mar 2021 10:23:06pm
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
class Dist1Component  : public juce::Component
{
public:
    Dist1Component(TremDistortionAudioProcessor&);
    ~Dist1Component() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CustomLAF customLAF;
    
    juce::Slider gainSlider;
    juce::Slider toneSlider;
    juce::Slider volSlider;
    
    juce::Label sectionHeading;
    juce::Label gainLabel;
    juce::Label toneLabel;
    juce::Label volLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> toneSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volSliderAttachment;
    
    TremDistortionAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Dist1Component)
};
