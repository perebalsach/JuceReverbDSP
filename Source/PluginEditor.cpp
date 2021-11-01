/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessorEditor::ReverbAudioProcessorEditor (ReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    sizeSliderAttatchment(audioProcessor.apvts, "size", sizeSlider),
    dampSliderAttatchment(audioProcessor.apvts, "damp", dampSlider),
    widthSliderAttatchment(audioProcessor.apvts, "width", widthSlider),
    dwSliderAttatchment(audioProcessor.apvts, "dw", dwSlider),
    freezeAttatchment (audioProcessor.apvts, "freeze", freezeButton)
{
    
    
    setSize (500, 250);
    setWantsKeyboardFocus(true);

    /*sizeLabel.setText("size", juce::NotificationType::dontSendNotification);
    sizeLabel.attachToComponent(&sizeSlider, false);

    dampLabel.setText("damp", juce::NotificationType::dontSendNotification);
    dampLabel.attachToComponent(&dampSlider, false);

    widthLabel.setText("width", juce::NotificationType::dontSendNotification);
    widthLabel.attachToComponent(&widthSlider, false);

    dwLabel.setText("dw", juce::NotificationType::dontSendNotification);
    dwLabel.attachToComponent(&dwSlider, false);*/

    // freezeButton.setButtonText(juce::String(juce::CharPointer_UTF8("-")));
    /*freezeButton.setClickingTogglesState(true);
    freezeButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    freezeButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentWhite);
    freezeButton.setColour(juce::TextButton::textColourOnId, juce::Colours::blue);
    freezeButton.setColour(juce::TextButton::textColourOffId, juce::Colours::grey);*/

    addAndMakeVisible(sizeSlider);
    addAndMakeVisible(dampSlider);
    addAndMakeVisible(widthSlider);
    addAndMakeVisible(dwSlider);
    addAndMakeVisible(freezeButton);

}

ReverbAudioProcessorEditor::~ReverbAudioProcessorEditor()
{
    freezeButton.setLookAndFeel(nullptr);
}

//==============================================================================
void ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (black);

    g.setFont (30.0f);
    g.setColour(offWhite);
    g.drawText("King Reverb", 150, 0, 200, 75, juce::Justification::centred);

    juce::Image backgroundImage = juce::ImageCache::getFromMemory(BinaryData::dspBackground_png, BinaryData::dspBackground_pngSize);
    g.drawImageAt(backgroundImage, 0, 0);
}

void ReverbAudioProcessorEditor::resized()
{
    sizeSlider.setBounds(55, 123, 80, 80);
    dampSlider.setBounds(162, 123, 80, 80);
    widthSlider.setBounds(267, 123, 80, 80);
    dwSlider.setBounds(374, 123, 80, 80);
    // freezeButton.setBounds(210, 120, 80, 40);
}
