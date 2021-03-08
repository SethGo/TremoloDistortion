/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Dist1Component.h"
#include "Dist2Component.h"
#include "MixComponent.h"
#include "LFOComponent.h"

//==============================================================================
/**
*/
class TremDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TremDistortionAudioProcessorEditor (TremDistortionAudioProcessor&);
    ~TremDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Distortions
    Dist1Component dist1Component;
    Dist2Component dist2Component;

    // LFO, Mix
    MixComponent mixComponent;
    LFOComponent lfoComponent;
    
    TremDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TremDistortionAudioProcessorEditor)
};
