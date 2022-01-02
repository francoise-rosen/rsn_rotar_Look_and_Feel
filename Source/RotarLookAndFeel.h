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
    //================================================================================
    // RotarLookAndFeel - base for the Rotar Look and Feel style
    //================================================================================
    class RotarLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        
        //================================================================================
        /* Public Types */
        
        enum class OutlineType { Ellipse, ArcNormal, ArcWithArrows, ArcWithCornersOut,
            ArcWithCornersIn, ArcThreePointerEmpty, ArcThreePointerFilled, NoOutline };
        enum class ButtonShape { RoundedRect, Rect, Circle, Custom };
        enum class ToggleButtonTickStyle { Fill, Tick, Cross };
        enum ColourStyle {DefaultBuild, DefaultRelease, BlackWhite, SilverBlack, Cyan, Uranus};
        
        //================================================================================
        /* Constructors */
        
        RotarLookAndFeel (unsigned char colourStyle = 0x0);
        
        virtual ~RotarLookAndFeel() override;
        
        /* Managed objects */
        
        //================================================================================
        /* Slider */
        
        void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
        
        int getSliderThumbRadius (juce::Slider& slider) override;
        
        void drawLinearSlider (juce::Graphics &, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider &) override;
        
        juce::Label* createSliderTextBox (juce::Slider& slider) override;
        
        juce::Slider::SliderLayout getSliderLayout (juce::Slider& slider) override;
        
        //================================================================================
        /* Toggle Button and Text Button */
        
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
                
        //================================================================================
        /* Special colour functions. */
        
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
        
        void setComponentAreaOutlinerVisibility(bool isVisible);
        
        /* Getters */
        //================================================================================
        
        juce::Font getFont() const;
        
    protected:
        /* Draw Rotary Slider thumb.
         Make it protected? a virtual? or make it helper, unless I want to use
         different thumbs in derived looks
         */
        virtual void drawRotaryThumb (juce::Graphics& g, const juce::Point<float> centre, const float& radius, const float& angle) noexcept;
        
        bool isComponentAreaOutlinerVisible {true};
        virtual void drawComponentArea(juce::Graphics& g, const juce::Rectangle<float>& area, juce::Component* component) noexcept;
        
        /* Draw Linear Slider thumb. */
        // todo!
        
        /* default font properties */
        float fontHeight {14.0f};
        const float edge {5.0f};
        juce::Font defaultFont  {"Monaco", "Plain", fontHeight};
      
    private:
        
        /* variables */
        ColourStyle colourStyle;
        const float sliderOuterRimScaleFactor {0.92f};
        bool outlineVisible {true};
        bool isThumbOnTop {true};
        bool isTrackVisible {false};
        OutlineType localOutlineType {OutlineType::ArcNormal};
        ButtonShape buttonShape { ButtonShape::Circle };
        ToggleButtonTickStyle tickStyle { ToggleButtonTickStyle::Tick };
        
        /* Private methods */
        void setColourStyle() noexcept;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotarLookAndFeel)
    };
    
    //================================================================================
    /* Rotary Big slider */
    //================================================================================
    class RotarBigRotaryLookAndFeel : public RotarLookAndFeel {
    public:
        
        //================================================================================
        /* Public Types */
        
        enum class RotaryBackgroundFillShape { Circular, Rectangular, Ellipse };
        
        //================================================================================
        /* Constructors */
        
        RotarBigRotaryLookAndFeel(unsigned char colourStyle = 0x3);
        virtual ~RotarBigRotaryLookAndFeel();
        
        //================================================================================
        /* Big Rotary Slider public methods */
        
        virtual void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional,                             float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
        
        void setRotaryBackgroundFeelShape (const RotaryBackgroundFillShape shape);
        
    private:
        const float knobToArcScaleFactor {0.72f};
        RotaryBackgroundFillShape backgroundFill {RotaryBackgroundFillShape::Circular}; /**< background fill shape flag*/
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotarBigRotaryLookAndFeel)
    };
    
    //================================================================================
    /* Rotary Small slider */
    //================================================================================
    
    class RotarSmallRotaryLookAndFeel : public RotarLookAndFeel
    {
    public:
        RotarSmallRotaryLookAndFeel(const bool& b = false);
        virtual ~RotarSmallRotaryLookAndFeel();
        
        void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
        
        bool isSymmetrical() const;
        void setSymmetry (bool b);
    private:
        bool symmetry;
        void drawThumbShadow (juce::Graphics& g, const juce::Point<float>& centre, const float& trackRadius, const float& radius, const float& angle);
        
        void drawSliderThumb (juce::Graphics& g, juce::Point<float>& centre, const float& radius, const float& angle);
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotarSmallRotaryLookAndFeel)
    };
    
    //================================================================================
    /* Rotary sliders with symmetrical view */
    //================================================================================
    class RotarSymmetricalRotaryLookAndFeel : public RotarLookAndFeel {
    public:
        RotarSymmetricalRotaryLookAndFeel(unsigned char colourStyle = 0x0);
        virtual ~RotarSymmetricalRotaryLookAndFeel() override;
        virtual void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
        
    private:
        OutlineType localOutlineType {OutlineType::ArcNormal};
        float sliderOuterRimScaleFactor {0.92f};
        float knobToArcScaleFactor {0.69f};

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotarSymmetricalRotaryLookAndFeel)
    };
    
    //================================================================================
    /* Linear sliders with symmetrical view */
    //================================================================================
    class RotarSymmetricalLinearLookAndFeel : public RotarLookAndFeel {
    public:
        //================================================================================
        /* Public Types */
        
        enum class PointerFill { NoFill, Fill, FillGradient };
        enum class TriangleFillType { OneColour, Triangles, Pencil, Gradient };
        enum class PointerType { Triangle, Circle, Rectangle, Arrow };
        
        //================================================================================
        /* Constructors */
        RotarSymmetricalLinearLookAndFeel();
        virtual ~RotarSymmetricalLinearLookAndFeel() override;
        
    };
    
    //================================================================================
    /* Rotary and Linear Sliders with symmetrical view */
    //================================================================================
    class RotarSymmetricalSliderLookAndFeel : public RotarSymmetricalRotaryLookAndFeel,
                                         public RotarSymmetricalLinearLookAndFeel
    {
    public:
        RotarSymmetricalSliderLookAndFeel();
        virtual ~RotarSymmetricalSliderLookAndFeel() override;
        
    };
}
