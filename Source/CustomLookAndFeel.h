/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 29 Oct 2021 9:57:56am
    Author:  Pere.Balsach

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() {};

    juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                            float sliderPos, float rotatoryStartAngle,
                            float rotatoryEndAngle, juce::Slider& slider) override;

    // juce::Label* createSliderTextBox(juce::Slider& slider) override;

    // juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override;

    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
        const juce::Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override;

private:
    juce::Colour blue       = juce::Colour::fromFloatRGBA(.43f, .83f, 1.f, 1.f);
    juce::Colour offWhite   = juce::Colour::fromFloatRGBA(.83f, .84f, .9f, 1.f);
    juce::Colour grey       = juce::Colour::fromFloatRGBA(.42f, .42f, .42f, 1.f);
    juce::Colour blackGrey  = juce::Colour::fromFloatRGBA(.2f, .2f, .2f, 1.f);
    juce::Image knobImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel);
};