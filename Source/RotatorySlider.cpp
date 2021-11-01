/*
  ==============================================================================

    RotatorySlider.cpp
    Created: 29 Oct 2021 9:57:44am
    Author:  Pere.Balsach

  ==============================================================================
*/

#include "RotatorySlider.h"

RotatorySlider::RotatorySlider()
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    // setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0, 0);
    setLookAndFeel(&customLookAndFeel);
    setColour(juce::Slider::rotarySliderFillColourId, blue);
    setColour(juce::Slider::textBoxTextColourId, blackGrey);
    setColour(juce::Slider::textBoxOutlineColourId, grey);
    setVelocityBasedMode(true);
    setVelocityModeParameters(.5f, 1, .09f, false);
    setRotaryParameters(juce::MathConstants<float>::pi * 1.25f,
                        juce::MathConstants<float>::pi * 2.75f,
                        true);
    setWantsKeyboardFocus(true);
    setTextValueSuffix(" %");
}

RotatorySlider::~RotatorySlider()
{
    setLookAndFeel(nullptr);
}

void RotatorySlider::paint(juce::Graphics& g)
{
    juce::Slider::paint(g);

    if (hasKeyboardFocus(false))
    {
        auto length = getHeight() > 15 ? 5.f : 4.f;
        auto thick  = getHeight() > 15 ? 3.f : 2.5f;

        g.setColour(findColour(juce::Slider::textBoxOutlineColourId));

        g.drawLine(0, 0, 0, length, thick);
        g.drawLine(0, 0, length, 0, thick);
        g.drawLine(0, getHeight(), 0, getHeight() - length, thick);
        g.drawLine(0, getHeight(), length, getHeight(), thick);
        g.drawLine(getWidth(), getHeight(), getWidth() - length, getHeight(), thick);
        g.drawLine(getWidth(), getHeight(), getWidth(), getHeight() - length, thick);
        g.drawLine(getWidth(), 0, getWidth() - length, 0, thick);
        g.drawLine(getWidth(), 0, getWidth(), length, thick);
    }
}

void RotatorySlider::mouseDown(const juce::MouseEvent& event)
{
    juce::Slider::mouseDown(event);
    setMouseCursor(juce::MouseCursor::NoCursor);
}

void RotatorySlider::mouseUp(const juce::MouseEvent& event)
{
    juce::Slider::mouseUp(event);

    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(event.source.getLastMouseDownPosition());
    setMouseCursor(juce::MouseCursor::NormalCursor);
}
