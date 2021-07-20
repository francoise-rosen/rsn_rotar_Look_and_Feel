/*
  ==============================================================================

    RotarLookAndFeel.cpp
    Created: 30 Mar 2021 7:49:22pm
    Author:  syfo_dias

  ==============================================================================
*/

#include "RotarLookAndFeel.h"

namespace rosen
{
    RotarLookAndFeel::RotarLookAndFeel(int colourStyle)
    :colourStyle {static_cast<ColourStyle>(colourStyle)}
    {
        setColourStyle();
    }
    
    RotarLookAndFeel::~RotarLookAndFeel() {}
    
    void RotarLookAndFeel::setColourStyle() {
        switch (colourStyle) {
            case Default:
            {
                /** Slider default colours */
                setColour (juce::Slider::backgroundColourId, juce::Colours::darkcyan);
                setColour (juce::Slider::trackColourId, juce::Colours::cyan);
                setColour (juce::Slider::thumbColourId, juce::Colours::darkcyan);
                setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::white);
                setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);
                setColour (juce::Slider::textBoxTextColourId, juce::Colours::silver.withBrightness (0.75f));
                setColour (juce::Slider::textBoxBackgroundColourId, juce::Colours::darkcyan.withBrightness (0.5f));
                setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::red.withBrightness (0.2f));
            
                /** ComboBox and PopupMenu defaults. */
                setColour (juce::ComboBox::backgroundColourId, juce::Colours::black);
                setColour (juce::ComboBox::outlineColourId, juce::Colours::white.withAlpha (0.75f));
                setColour (juce::PopupMenu::backgroundColourId, juce::Colours::black.withAlpha (0.5f));
                
                /** Label. */
                setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);
                setColour (juce::Label::textColourId, juce::Colours::silver.withBrightness (0.5f));
                setColour (juce::Label::outlineColourId, juce::Colours::black.withAlpha(0.2f));
                setColour (juce::Label::backgroundWhenEditingColourId, juce::Colours::blue.withAlpha (0.5f));
                
                /** Button. */
                setColour (juce::TextButton::buttonColourId, juce::Colours::silver.darker());
                setColour (juce::TextButton::buttonOnColourId, juce::Colours::orange);
                setColour (juce::ToggleButton::textColourId, juce::Colours::black);
                setColour (juce::ToggleButton::tickColourId, juce::Colours::orange);
            }
        }
    }
}
