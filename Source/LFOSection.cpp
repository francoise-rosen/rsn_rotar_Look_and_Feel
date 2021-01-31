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
    addAndMakeVisible (&label_A);
    label_A.setText ("LFO", juce::NotificationType::dontSendNotification);
    label_A.setJustificationType (juce::Justification::centred);
    label_A.setColour (juce::Label::outlineColourId, juce::Colours::darkblue);
    label_A.setColour (juce::Label::backgroundColourId, juce::Colours::darkcyan.darker());
    
    addControls();
    makeControlsVisible();
    
    setLookAndFeel (&waveshaperLookAndFeel);
}

LFOSection::~LFOSection()
{
    setLookAndFeel (nullptr);
}

void LFOSection::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::silver);   // clear the background

    g.setColour (juce::Colours::black);
    g.setFont (14.0f);
    g.drawText ("LFOSection", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    
    g.setColour(juce::Colours::orange);
    for (int i = 0; i < controls.size(); ++i)
    {
        if (controls[i].area_a != nullptr)
        {
            g.drawRect(*(controls[i].area_a));
        }
    }
}

void LFOSection::resized()
{
    auto box = getLocalBounds();
    rateArea = std::make_unique<juce::Rectangle<int>> (box.removeFromLeft (getWidth() * 0.3f));
    phaseArea = std::make_unique<juce::Rectangle<int>> (box.removeFromLeft (getWidth() * 0.3f));
    targetArea = std::make_unique<juce::Rectangle<int>> (box);
    lfoRateSlider.setBounds (rateArea->reduced (5.0f));
    
    for (int j = 0; j < controls.size(); ++j)
    {
//        controls[j].area_a = std::make_unique<juce::Rectangle<int>> (targetArea->withBottom (targetArea->getY() + targetArea->getHeight() / (numTargets - j)));
        controls[j].area_a = std::make_unique<juce::Rectangle<int>> (targetArea->removeFromTop (getHeight() / numTargets));
        controls[j].amount->setBounds (controls[j].area_a->removeFromRight (targetArea->getWidth() * 0.25f));
        controls[j].toggle->setBounds (controls[j].area_a->removeFromLeft (getHeight() / numTargets));
        controls[j].target->setBounds (controls[j].area_a->withSizeKeepingCentre(controls[j].area_a->getWidth(), juce::jmin (27.0f, controls[j].area_a->getHeight() * 0.5f)));
    }
    
}

/** Copy constructor. */
//LFOSection::SendControl::SendControl (const SendControl& send)
//{
//    /** does make unique deletes the object currently managed by unique_ptr? */
//    toggle = std::make_unique<juce::ToggleButton> ();
//    toggle = std::make_unique<juce::ToggleButton> (*(send.toggle));
//    /** do I need to dereference? */
//    amount = std::make_unique<juce::Slider> (send.amount);
//    destination = std::make_unique<juce::ComboBox> (send.destination);
//    area_a = std::make_unique<juce::Rectangle<int>> (send.area_a);
//}

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

