/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TremDistortionAudioProcessorEditor::TremDistortionAudioProcessorEditor (TremDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), dist1Component (p), dist2Component (p), mixComponent (p), lfoComponent (p), audioProcessor (p)
{
    addAndMakeVisible (dist1Component);
    addAndMakeVisible (dist2Component);
    addAndMakeVisible (mixComponent);
    addAndMakeVisible (lfoComponent);

    setSize (500, 350);
}

TremDistortionAudioProcessorEditor::~TremDistortionAudioProcessorEditor()
{
}

//==============================================================================
void TremDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (juce::Colour (33, 16, 64));
}

void TremDistortionAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    auto distRow = area.removeFromTop (getHeight() * 0.45);
    dist1Component.setBounds (distRow.removeFromLeft (getWidth() / 2));
    dist2Component.setBounds (distRow);
    
    mixComponent.setBounds (area.removeFromTop (getHeight() * 0.2));
    
    lfoComponent.setBounds (area);
}
