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
    struct SendControl
    {
        std::unique_ptr<juce::ToggleButton> toggle;
        std::unique_ptr<juce::Slider> amount;
        std::unique_ptr<juce::Slider> phase;
        std::unique_ptr<juce::ComboBox> target;
        std::unique_ptr<juce::ComboBox> waveform;
        // reserved area for the object contained in SendControl object
//        std::unique_ptr<juce::Rectangle<int>> objectArea; // including labels
    };
    
    LFOSection();
    virtual ~LFOSection() override;
    
    
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    /* Control names - each of these must have a lable (or lable for the group) and a listener*/
    juce::Slider lfoRateSlider { juce::Slider::SliderStyle::Rotary, juce::Slider::TextEntryBoxPosition::TextBoxBelow };
    
    /* This is how many targets the LFO has .*/
    const int numTargets { 3 };
    int labelHight {30};
    // horizonal sections
    std::vector<std::pair<std::string, float>> section {{"Rate", 0.2f}, {"On", 0.1f}, {"Targ", 0.2}, {"Amo", 0.2f}, {"ø", 0.3f}};
 
    std::vector<SendControl> controls;
    Rosen::RotarLookAndFeel lfoLookAndFeel;
  
    /* areas. */
    enum AreaRectangle {Rate, On, Target, Amount, Phase, NumAreas};
    std::vector<juce::Rectangle<int>> areas;
  
    void makeMesh();
    void addControls();
    void makeControlsVisible();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOSection)
};
