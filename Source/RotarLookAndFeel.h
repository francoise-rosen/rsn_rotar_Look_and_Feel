/*
  ==============================================================================

    RotarLookAndFeel.h
    Created: 30 Mar 2021 7:49:22pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace rosen
{
    class RotarLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        enum ColourStyle {Default};
        RotarLookAndFeel (int colourStyle = 0);
        virtual ~RotarLookAndFeel() override;
      
    private:
        ColourStyle colourStyle;
        
        /* Colours */
        void setColourStyle();
    };
}
