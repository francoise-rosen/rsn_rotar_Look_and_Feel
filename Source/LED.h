/*
  ==============================================================================

    LED.h
    Created: 1 May 2022 3:42:18pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace Rosen::Interface {
    class LED : public juce::LookAndFeel_V4
    {
    public:
        LED()
        {}
        
        LED (juce::Colour componentBackground)
        :fillColour {componentBackground.withAlpha(0.0f)}, gradientOuterColour {componentBackground}
        {}
        
        virtual ~LED() override
        {}
        
        enum class LEDShape { Ellipse, Circle, RoundedRectangle, Rectangle, Triangle };
        void setGradientOuterColour (juce::Colour colour)
        {
            gradientOuterColour = colour;
        }
        void setGradientOn (bool isOn)
        {
            isGradientOn = isOn;
        }
        void setFillColour (juce::Colour componentBackground)
        {
            fillColour = componentBackground;
        }
        void drawLabel (juce::Graphics& g, juce::Label& label) override
        {
            auto innerColour = label.findColour (juce::Label::backgroundColourId);
            outlineColour = label.findColour (juce::Label::outlineColourId);
            auto labelArea = label.getLocalBounds();
            juce::Point<float> pivot { labelArea.getWidth() * 0.5f, labelArea.getHeight() * 0.5f };
            
            g.fillAll (fillColour);
            
            std::unique_ptr<juce::ColourGradient> gradient;
            if (isGradientOn)
            {
                juce::Point<float> outerPoint;
                if ( (shape == LEDShape::Ellipse) ||
                     (shape == LEDShape::RoundedRectangle) ||
                     (shape == LEDShape::Rectangle ) )
                {
                    outerPoint = juce::Point<float> {
                        (labelArea.getWidth() > labelArea.getHeight()) ? 0.0f : labelArea.getWidth() * 0.5f, (labelArea.getWidth() > labelArea.getHeight()) ? labelArea.getHeight() * 0.5f : 0.0f
                    };
                }
                else if (shape == LEDShape::Circle)
                {
                    auto diameter = juce::jmin (labelArea.getWidth(), labelArea.getHeight());
                    outerPoint = juce::Point<float> {
                        pivot.getX() - diameter * 0.5f, pivot.getY() - diameter * 0.5f
                    };
                }
                gradient = std::make_unique<juce::ColourGradient>
                        (innerColour,
                         pivot,
                         gradientOuterColour,
                         outerPoint,
                         (shape == LEDShape::Ellipse) ? true : false
                         );
            }
            
            g.setColour (innerColour);
            if (shape == LEDShape::RoundedRectangle)
            {
                g.fillRoundedRectangle (labelArea.toFloat(), 5.0f);
            }
            else if (shape == LEDShape::Rectangle)
            {
                g.fillRect (labelArea);
            }
            else if (shape == LEDShape::Ellipse)
            {
                if (isGradientOn)
                {
                    g.setGradientFill (*gradient);
                }
                g.fillEllipse (labelArea.toFloat());
                auto margin = juce::jmin (2.0f, juce::jmin (labelArea.getWidth(), labelArea.getHeight()) * 0.1f);
                g.setColour (outlineColour);
                g.drawEllipse (labelArea.reduced (margin).toFloat(), margin);
            }
            else if (shape == LEDShape::Triangle)
            {
                /** I need to know the direction and the pivot point.
                 I need to know how to fit it in label bounds when rotated. */
                
            }
        
            g.setColour (textColour);
            auto textArea = getLabelBorderSize (label).subtractedFrom (labelArea);
            g.drawFittedText (label.getText(), textArea, label.getJustificationType(), 1, label.getMinimumHorizontalScale());
        }
        
    private:
        LEDShape shape { LEDShape::Ellipse };
        bool isGradientOn { false };
        
        /** How do I set these? */
        juce::Colour fillColour { juce::Colours::orange.withAlpha(0.25f) };
        juce::Colour outlineColour { juce::Colours::black.withAlpha (0.0f) };
        juce::Colour gradientOuterColour { juce::Colours::black };
        juce::Colour textColour { juce::Colours::white };
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LED);
    };
}

