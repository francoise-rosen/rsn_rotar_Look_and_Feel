/*
  ==============================================================================

    RotarLookAndFeel.h
    Created: 30 Mar 2021 7:49:22pm
    Author:  syfo_dias

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace Rosen
{
    class RotarLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        /* Public Types */
        //================================================================================
        enum class OutlineType { Ellipse, ArcNormal, ArcWithArrows, ArcWithCornersOut,
            ArcWithCornersIn, ArcThreePointerEmpty, ArcThreePointerFilled, NoOutline };
        enum class ButtonShape { RoundedRect, Rect, Circle, Custom };
        enum class ToggleButtonTickStyle { Fill, Tick, Cross };
        enum ColourStyle {Default};
        
        /* Constructors */
        //================================================================================
        
        RotarLookAndFeel (int colourStyle = 0);
        virtual ~RotarLookAndFeel() override;
        
        /* Managed objects */
        
        /* Slider */
        //================================================================================
        
        void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
        
        int getSliderThumbRadius (juce::Slider& slider) override;
        void drawLinearSlider (juce::Graphics &, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider &) override;
        juce::Label* createSliderTextBox (juce::Slider& slider) override;
        juce::Slider::SliderLayout getSliderLayout (juce::Slider& slider) override;
        
        /* Button  */
        //================================================================================
        
        void setToggleButtonTickStyle (RotarLookAndFeel::ToggleButtonTickStyle style);
        juce::Font getTextButtonFont (juce::TextButton& t, int buttonHeight) override;
        void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isButtonHighlighted, bool isButtonDown) override;
        void drawToggleButton (juce::Graphics& g, juce::ToggleButton& tb, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
        
        //================================================================================
        /* ComboBox, PopupMenu, Font etc. */
        
        void drawComboBox (juce::Graphics& g, int width, int height, bool down, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) override;
        void drawPopupMenuBackground (juce::Graphics& g, int width, int height) override;
        void positionComboBoxText (juce::ComboBox& box, juce::Label& label) override;
        juce::Font getComboBoxFont (juce::ComboBox& box) override;
        void setFontHeight (const float& newHeight);
        
        //================================================================================
        /* Label */
        
        juce::Font getLabelFont (juce::Label& l) override;
        juce::BorderSize<int> getLabelBorderSize (juce::Label& l) override;
        void drawLabel (juce::Graphics& g, juce::Label& j) override;
        
        /* Miscellaneous */
        
        /* Special colour functions. */
        //================================================================================
        
        void setThumbGradientTargetColour (const juce::Colour& colour);
        void setTrackGradientTargetColour (const juce::Colour& colour);
        void setThumbShadowColour (const juce::Colour& colour);
        
        /* Setters */
        //================================================================================
        
        /* Test this (unit test).
            The drawing may overcomplicate the drawRotary method.
            Delegate drowing the arc to other methods?
         */
        void setOutlineType (OutlineType outlineType);
        void setThumbPosition (bool isOnTop);
        
        /* If outline is not visible, only sliderFill and sliderThumb
         are visible, but outer body (outline is still drown, it's just transparent.
         */
        
        bool isOutlineVisible() const;
        void setOutlineVisibility (bool isVisible);
        void setTrackVisibility (bool isVisible);
        
        /* Getters */
        //================================================================================
        
        juce::Font getFont() const;
        
    protected:
        /* Draw Rotary Slider thumb.
         Make it protected? a virtual? or make it helper, unless I want to use
         different thumbs in derived looks
         */
        virtual void drawRotaryThumb (juce::Graphics& g, const juce::Point<float> centre, const float& radius, const float& angle) noexcept;
        
        /* Draw Linear Slider thumb. */
        // todo!
        
        /* default font properties */
        float fontHeight {14.0f};
        juce::Font defaultFont  {"Monaco", "Plain", fontHeight};
      
    private:
        
        /* variables */
        ColourStyle colourStyle;
        const float edge {5.0f};
        const float sliderOuterRimScaleFactor {0.92f};
        bool outlineVisible {true};
        bool isThumbOnTop {true};
        bool isTrackVisible {false};
        OutlineType localOutlineType {OutlineType::ArcNormal};
        ButtonShape buttonShape { ButtonShape::Circle };
        ToggleButtonTickStyle tickStyle { ToggleButtonTickStyle::Tick };
        
        /* Private methods */
        void setColourStyle();
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotarLookAndFeel)
    };
}
