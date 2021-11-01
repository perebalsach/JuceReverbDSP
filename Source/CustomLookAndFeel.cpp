/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 29 Oct 2021 9:57:56am
    Author:  Pere.Balsach

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    knobImage = juce::ImageFileFormat::loadFrom(BinaryData::knob_png, BinaryData::knob_pngSize);
    juce::ImageCache::addImageToCache(knobImage, 0);
}

juce::Slider::SliderLayout CustomLookAndFeel::getSliderLayout(juce::Slider& slider)
{
    auto localBounds = slider.getLocalBounds();
    juce::Slider::SliderLayout layout;

    // layout.textBoxBounds    = localBounds;
    layout.sliderBounds     = localBounds;

    return layout;
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotatoryStartAngle, float rotatoryEndAngle, juce::Slider& slider)
{
    /*auto fill = slider.findColour(juce::Slider::rotarySliderFillColourId);

    auto bounds = juce::Rectangle<float>(x, y, width, height).reduced(2.f);
    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.f;
    auto toAngle = rotatoryStartAngle + sliderPos * (rotatoryEndAngle - rotatoryStartAngle);
    auto lineW = radius * .085f;
    auto arcRadius = radius - lineW * 1.5f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                .0f,
                                rotatoryStartAngle,
                                rotatoryEndAngle,
                                true);

    g.setColour(blackGrey);
    g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    juce::Path valueArc;
    valueArc.addCentredArc (bounds.getCentreX(),
                            bounds.getCentreY(),
                            arcRadius,
                            arcRadius,
                            .0f,
                            rotatoryStartAngle,
                            toAngle,
                            true);

    auto alpha = .1f + (float)slider.getValue() * .9f;
    auto brightness = .4f + (float)slider.getValue() * .6f;

    g.setColour(fill.withAlpha(alpha).brighter(brightness));
    g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    auto thumbWidth = lineW * 2.f;

    juce::Path thumb;
    thumb.addRectangle(-thumbWidth / 2, -thumbWidth / 2, thumbWidth, radius + lineW);

    g.setColour(offWhite);
    g.fillPath(thumb, juce::AffineTransform::rotation(toAngle + 3.12f).translated(bounds.getCentre()));

    g.fillEllipse(bounds.reduced(8.f));*/
 
    // Drawing the know image and rotation
    const float angle = rotatoryStartAngle + sliderPos * (rotatoryEndAngle - rotatoryStartAngle);
    const float pivotX = juce::ImageCache::getFromHashCode(0).getWidth() / 2;
    const float pivotY = juce::ImageCache::getFromHashCode(0).getHeight() / 2;
    
    g.drawImageTransformed(juce::ImageCache::getFromHashCode(0), juce::AffineTransform::rotation(angle, pivotX, pivotY));
}

//juce::Label* CustomLookAndFeel::createSliderTextBox(juce::Slider& slider)
//{
//    auto* l = new juce::Label();
//    l->setJustificationType(juce::Justification::centred);
//    l->setColour(juce::Label::textColourId, slider.findColour(juce::Slider::textBoxTextColourId));
//    l->setColour(juce::Label::textWhenEditingColourId, slider.findColour(juce::Slider::textBoxTextColourId));
//    l->setColour(juce::Label::outlineWhenEditingColourId, slider.findColour(juce::Slider::textBoxOutlineColourId));
//    l->setInterceptsMouseClicks(false, false);
//    l->setFont(15);
//
//    return l;
//}
//
//juce::Font CustomLookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight)
//{
//    return juce::Font();
//}

void CustomLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
}
