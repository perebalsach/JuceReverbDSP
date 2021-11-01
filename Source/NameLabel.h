/*
  ==============================================================================

    NameLabel.h
    Created: 29 Oct 2021 9:57:15am
    Author:  Pere.Balsach

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NameLabel : public juce::Label
{
public:
    NameLabel()
    {
        setFont(20.f);
        setColour(juce::Label::textColourId, grey);
        setJustificationType(juce::Justification::centred);
    }

    ~NameLabel(){}

private:
    juce::Colour grey = juce::Colour::fromFloatRGBA(.42f, .42f, .42f, 1.f);
};