/*
  ==============================================================================

    LFOSection.h
    Created: 20 Sep 2020 12:27:44pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "WaveshaperLookAndFeel.h"
#include "RotarLookAndFeel.h"

//==============================================================================
/*
*/
class LFOSection  : public juce::Component
{
public:
    LFOSection();
    virtual ~LFOSection() override;
    
    struct SendControl
    {
        //SendControl (const SendControl&);
        
        std::unique_ptr<juce::ToggleButton> toggle;
        std::unique_ptr<juce::Slider> amount;
        std::unique_ptr<juce::ComboBox> target;
        // reserved area for the object contained in SendControl object
        std::unique_ptr<juce::Rectangle<int>> area_a;
    };
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    /* Control names - each of these must have a lable (or lable for the group) and a listener*/
    enum LFOControl {Rate, PhaseAlpha, PhaseBeta, PhaseGamma, AmountAlpha, AmountBeta, AmountGamma, OnAlpha, OnBeta, OnGamma, NumControls};
    juce::Slider lfoRateSlider { juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow };
    juce::Label labelLFO;
    
    /* This is how many targets the LFO has .*/
    const int numTargets { 3 };
    std::vector<SendControl> controls;
    Rosen::RotarLookAndFeel lfoLookAndFeel;
    
    /* areas. */
    std::unique_ptr<juce::Rectangle<int>> rateArea;
    std::unique_ptr<juce::Rectangle<int>> phaseArea;
    std::unique_ptr<juce::Rectangle<int>> targetArea;
    
    void addControls();
    void makeControlsVisible();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOSection)
};
