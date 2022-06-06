/*
  ==============================================================================

    LFOSection.cpp
    Created: 20 Sep 2020 12:27:44pm
    Author:  syfo_dias

  ==============================================================================
*/

#include <JuceHeader.h>
#include "../Source/LFOSection.h"

//==============================================================================
LFOSection::LFOSection()
{
    setLookAndFeel (&lfoLookAndFeel);
    addAndMakeVisible (&lfoRateSlider);
    
    addControls();
    makeControlsVisible();
    makeMesh();
    
    //lfoLookAndFeel.setToggleButtonTickStyle (WaveshaperLookAndFeel::ToggleButtonTickStyle::Fill);
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
    
    g.setColour(juce::Colours::darkcyan);
    
    g.setOpacity(1.0f);
    g.setFont(14.0f);
    for (auto i = 0; i < NumAreas; ++i) {
        g.drawRect(areas[i]);
        g.drawText(section[i].first, areas[i].withTop(juce::jmin(15.0f, getHeight() * 0.1f)), juce::Justification::centredTop, true);
    }
}

void LFOSection::resized()
{
    makeMesh();
    // Rate Slider + Label
    lfoRateSlider.setBounds(areas[Rate].removeFromBottom(getHeight() - 30));
    
    auto phaseArea = areas[Phase].withTop(labelHight);
    auto amountArea = areas[Amount].withTop(labelHight);
    auto targetArea = areas[Target].withTop(labelHight);

    for (auto j = 0; j < controls.size(); ++j) {
        controls[j].phase->setBounds(phaseArea.removeFromTop(phaseArea.getHeight() / (controls.size() - j)).reduced(2, 7));
        controls[j].amount->setBounds(amountArea.removeFromTop(amountArea.getHeight() / (controls.size() - j)));
        controls[j].target->setBounds(targetArea.removeFromTop(targetArea.getHeight() / (controls.size() - j)).reduced(2, juce::jmax(7, static_cast<int>(getHeight() * 0.07f))));
    }
    
}

void LFOSection::makeMesh()
{
    areas.resize(section.size());
    auto area = getLocalBounds();
    for (auto i = 0; i < areas.size(); ++i) {
        areas[i] = area.removeFromLeft(section[i].second * getWidth());
    }

}

void LFOSection::addControls()
{
    controls.clear();
    controls.resize (numTargets);
    for (int i = 0; i < controls.size(); ++i)
    {
        controls[i].toggle = std::make_unique<juce::ToggleButton> ();
        controls[i].amount = std::make_unique<juce::Slider> (juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox);
        controls[i].target = std::make_unique<juce::ComboBox> ("Choice " + juce::String (i));
        controls[i].target->addItemList({"iF FReQ", "iF Q", "iF Bst", "oF Freq", "oF Q", "oF Bst", "Satur", "Crossfd", "mx"}, 1);
        
        // phase
        controls[i].phase = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox);
        std::cout << "section" << i << "added\n";
    }
}

void LFOSection::makeControlsVisible()
{
    for (int i = 0; i < controls.size(); ++i)
    {
        addAndMakeVisible (controls[i].amount.get());
        addAndMakeVisible (controls[i].toggle.get());
        addAndMakeVisible (controls[i].target.get());
        addAndMakeVisible (controls[i].phase.get());
        controls[i].target->setColour(juce::ComboBox::backgroundColourId, juce::Colours::darkcyan);
        controls[i].target->setColour(juce::ComboBox::textColourId, juce::Colours::black);
        controls[i].target->setColour(juce::ComboBox::outlineColourId, juce::Colours::black);
        controls[i].amount->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::black);
        controls[i].amount->setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
        
    }
}


