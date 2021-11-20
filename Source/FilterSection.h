/*
  ==============================================================================

    FilterSection.h
    Created: 20 Sep 2020 12:27:10pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveshaperLookAndFeel.h"
#include "RotarLookAndFeel.h"

//==============================================================================
/*
*/
struct FilterControls
{
    juce::Slider frequency {juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow};
    juce::Slider q {juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow};
    juce::Slider boost {juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow};
    juce::Slider amount {juce::Slider::SliderStyle::LinearHorizontal, juce::Slider::TextEntryBoxPosition::TextBoxBelow};
    juce::TextButton toggleButton;
    juce::ComboBox algorithm;
    // overload does not work, maybe better to wrap components in unique_ptr ?
//    bool operator==(FilterControls& a)
//    {
//        return ( (&frequency == &(a.frequency)) && (q == a.q) && (boost == a.boost) && (amount == a.amount) && (algorithm == a.algorithm));
//    }
//    bool operator!=(FilterControls& a)
//    {
//        return !(*this == a);
//    }
};

class FilterSection  : public juce::Component
{
public:
    FilterSection(juce::Colour parentBackground);
    virtual ~FilterSection() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void intialiseFilterControls (FilterControls& filterControls);

private:
    const float edge {4.0f};
    juce::Colour localBackground;
    Rosen::RotarLookAndFeel rotarMainLookAndFeel;
    Rosen::RotarSmallRotaryLookAndFeel smallSliderLookAndFeel {true};
    FilterControls alphaFilter;
    FilterControls betaFilter;
    
    enum ObjectArea {AlphaFreqRotary, AlphaQRotary, AlphaFilterMixRotary, AlphaBoostRotary, AlphaButton, BetaFreqRotary, BetaQRotary, BetaFilterMixRotary, BetaBoostRotary, BetaButton, NumObjects};
    
    std::unique_ptr<juce::Rectangle<int>> objectAreas[NumObjects];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterSection)
};
