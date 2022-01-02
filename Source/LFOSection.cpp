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
    addControls();
    makeControlsVisible();
    makeMesh();
    
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
    auto area = getLocalBounds();
    makeMesh();
    // Rate Slider + Label
    lfoRateSlider.setBounds(areas[Rate].removeFromBottom(getHeight() - 30));
    
    auto phaseArea = areas[Phase];
    for (auto j = 0; j < controls.size(); ++j) {
        controls[j].phase->setBounds(phaseArea.removeFromLeft(phaseArea.getWidth() / (controls.size() - j)));
    }
    
}

void LFOSection::makeMesh()
{
    areas.resize(section.size());
    auto area = getLocalBounds();
    // enum AreaRectangle {Rate, On, Wave, Amount, Target, Phase, NumAreas};
//    areas[Rate] = area.removeFromLeft(section[Rate].second * getWidth());
//    areas[On] = area.removeFromLeft(section[On].second * getWidth());
//    areas[Wave] = area.removeFromLeft(section[Wave].second * getWidth());
//    areas[Amount] = area.removeFromLeft(section[Amount].second * getWidth());
//    areas[Target] = area.removeFromLeft(section[Target].second * getWidth());
//    areas[Phase] = area.removeFromLeft(section[Phase].second * getWidth());
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
//        controls[i].amount->setSliderStyle (juce::Slider::SliderStyle::Rotary);
//        controls[i].toggle = std::make_unique<juce::ToggleButton> ("Send " + juce::String (i));
        controls[i].toggle = std::make_unique<juce::ToggleButton> ();
        controls[i].amount = std::make_unique<juce::Slider> (juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::NoTextBox);
        controls[i].target = std::make_unique<juce::ComboBox> ("Choice " + juce::String (i));
        controls[i].target->addItemList({"iF FReQ", "iF Q", "iF Bst", "oF Freq", "oF Q", "oF Bst", "Satur", "Crossfd", "mx"}, 1);
        
        // phase
        controls[i].phase = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextEntryBoxPosition::NoTextBox);
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


