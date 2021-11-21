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
        std::unique_ptr<juce::Rectangle<int>> objectArea;
    };
    void paint (juce::Graphics&) override;
    void resized() override;
    void addLabels() noexcept;

private:
    /* Control names - each of these must have a lable (or lable for the group) and a listener*/
    //enum LFOControl {Rate, PhaseAlpha, PhaseBeta, PhaseGamma, AmountAlpha, AmountBeta, AmountGamma, OnAlpha, OnBeta, OnGamma, NumControls};
    juce::Slider lfoRateSlider { juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow };
    std::array<std::string, 4> labels {"Rate", "Amount", "Target", "ø"};
    std::vector<std::unique_ptr<juce::Label>> controlLabel;
    
    /* This is how many targets the LFO has .*/
    const int numTargets { 3 };
    std::vector<SendControl> controls;
    Rosen::RotarLookAndFeel lfoLookAndFeel;
    
    /* areas. */
    std::unique_ptr<juce::Rectangle<int>> labelArea; // 4 objects
    std::unique_ptr<juce::Rectangle<int>> rateArea; // 1 object
    std::unique_ptr<juce::Rectangle<int>> phaseArea; // 3 objects
    std::unique_ptr<juce::Rectangle<int>> targetArea; // 3 objects
    // button area?
    
    void addControls();
    void makeControlsVisible();
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOSection)
};
