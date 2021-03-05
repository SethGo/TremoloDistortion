/*
  ==============================================================================

    CustomLAF.h
    Created: 5 Mar 2021 1:30:32am
    Author:  Seth Gory

  ==============================================================================
*/

#pragma once

class CustomLAF : public juce::LookAndFeel_V4
{
public:
    CustomLAF()
    {
        auto green = juce::Colour (158, 255, 65);
        auto darkGreen = juce::Colour (74, 153, 0);
        auto pink = juce::Colour (255, 210, 210);
        auto lightPurple = juce::Colour (94, 46, 184);
        
        // Rotary slider settings
        setColour (juce::Slider::thumbColourId, green);
        setColour (juce::Slider::rotarySliderOutlineColourId, lightPurple);
        setColour (juce::Slider::rotarySliderFillColourId, darkGreen);
        
        // Slider settings
        setColour (juce::Slider::thumbColourId, green);
        setColour (juce::Slider::backgroundColourId, lightPurple);
        setColour (juce::Slider::trackColourId, lightPurple);
        
        // Label settings
        setColour (juce::Label::ColourIds::textColourId, pink);
    }
};
