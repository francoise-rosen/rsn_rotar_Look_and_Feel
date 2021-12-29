/*
  ==============================================================================

    LFOSection.cpp
    Created: 20 Sep 2020 12:27:44pm
    Author:  syfo_dias

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOSection.h"

//==============================================================================
LFOSection::LFOSection()
{
    addAndMakeVisible (&lfoRateSlider);
    
    makeMesh();
    addControls();
    makeControlsVisible();
    
    //lfoLookAndFeel.setToggleButtonTickStyle (WaveshaperLookAndFeel::ToggleButtonTickStyle::Fill);
    setLookAndFeel (&lfoLookAndFeel);
}

LFOSection::~LFOSection()
{
    setLookAndFeel (nullptr);
}

void LFOSection::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::silver);   // clear the background

    g.setColour (juce::Colours::black);
    g.setOpacity(0.05f);
    g.setFont (getHeight() * 0.85f);
    g.drawText ("LFO", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    g.setColour(juce::Colours::orange);
    
    for (auto rect : areas) {
        g.drawRect(rect);
    }
}

void LFOSection::resized()
{
    auto area = getLocalBounds();
    makeMesh();
    // Rate Slider + Label
    
}

void LFOSection::makeMesh()
{
    areas.resize(NumAreas);
    auto area = getLocalBounds();
    areas[Rate] = area.removeFromLeft(section["Rate"] * getWidth());
    areas[On] = area.removeFromLeft(section["On"] * getWidth());
}

void LFOSection::addControls()
{
    controls.clear();
    controls.resize (numTargets);
    for (int i = 0; i < controls.size(); ++i)
    {
//        controls[i].amount->setSliderStyle (juce::Slider::SliderStyle::Rotary);
//        controls[i].toggle = std::make_unique<juce::ToggleButton> ("Send " + juce::String (i));
        controls[i].toggle = std::make_unique<juce::ToggleButton> ();
        controls[i].amount = std::make_unique<juce::Slider> (juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox);
        controls[i].target = std::make_unique<juce::ComboBox> ("Choice " + juce::String (i));
        controls[i].target->addItemList({"iF FReQ", "iF Q", "iF Bst", "oF Freq", "oF Q", "oF Bst", "Satur", "Crossfd", "mx"}, 1);
    }
}

void LFOSection::makeControlsVisible()
{
    for (int i = 0; i < controls.size(); ++i)
    {
        addAndMakeVisible (controls[i].amount.get());
        addAndMakeVisible (controls[i].toggle.get());
        addAndMakeVisible (controls[i].target.get());
        controls[i].target->setColour(juce::ComboBox::backgroundColourId, juce::Colours::darkcyan);
        controls[i].target->setColour(juce::ComboBox::textColourId, juce::Colours::black);
        controls[i].target->setColour(juce::ComboBox::outlineColourId, juce::Colours::black);
        controls[i].amount->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::black);
        controls[i].amount->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
        
    }
}


