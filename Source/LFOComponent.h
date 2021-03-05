/*
  ==============================================================================

    LFOComponent.h
    Created: 3 Mar 2021 8:54:26pm
    Author:  Seth Gory

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLAF.h"

//==============================================================================
/*
*/
class LFOComponent  : public juce::Component
{
public:
    LFOComponent();
    ~LFOComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CustomLAF customLAF;
    
    juce::Slider lfoRateSlider;
    juce::Slider lfoDepthSlider;
    
    juce::Label sectionHeading;
    juce::Label rateLabel;
    juce::Label depthLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};
