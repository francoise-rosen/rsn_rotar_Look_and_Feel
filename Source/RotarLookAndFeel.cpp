/*
  ==============================================================================

    RotarLookAndFeel.cpp
    Created: 30 Mar 2021 7:49:22pm
    Author:  syfo_dias

  ==============================================================================
*/

#include "RotarLookAndFeel.h"

namespace Rosen
{
    RotarLookAndFeel::RotarLookAndFeel(unsigned char colourStyle)
    :colourStyle {static_cast<ColourStyle>(colourStyle)}
    {
        setColourStyle();
    }
    
    RotarLookAndFeel::~RotarLookAndFeel() {}
    
    void RotarLookAndFeel::setColourStyle() noexcept {
        switch (colourStyle) {
            case Default:
            {
                /* Slider default colours */
                setColour (juce::Slider::backgroundColourId, juce::Colours::darkcyan);
                setColour (juce::Slider::trackColourId, juce::Colours::cyan);
                setColour (juce::Slider::thumbColourId, juce::Colours::darkcyan);
                setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::white);
                setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);
                setColour (juce::Slider::textBoxTextColourId, juce::Colours::silver.withBrightness (0.75f));
                setColour (juce::Slider::textBoxBackgroundColourId, juce::Colours::darkcyan.withBrightness (0.5f));
                setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::red.withBrightness (0.2f));
            
                /* ComboBox and PopupMenu defaults. */
                setColour (juce::ComboBox::backgroundColourId, juce::Colours::black);
                setColour (juce::ComboBox::outlineColourId, juce::Colours::white.withAlpha (0.75f));
                setColour (juce::PopupMenu::backgroundColourId, juce::Colours::black.withAlpha (0.5f));
                
                /* Label. */
                setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);
                setColour (juce::Label::textColourId, juce::Colours::silver.withBrightness (0.5f));
                setColour (juce::Label::outlineColourId, juce::Colours::black.withAlpha(0.2f));
                setColour (juce::Label::backgroundWhenEditingColourId, juce::Colours::blue.withAlpha (0.5f));
                
                /* Button. */
                setColour (juce::TextButton::buttonColourId, juce::Colours::silver.darker());
                setColour (juce::TextButton::buttonOnColourId, juce::Colours::orange);
                setColour (juce::ToggleButton::textColourId, juce::Colours::black);
                setColour (juce::ToggleButton::tickColourId, juce::Colours::orange);
                break;
            }
            case BlackWhite:
            {
                /* Slider default colours */
                setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);
                setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::white);
                setColour (juce::Slider::backgroundColourId, juce::Colours::darkcyan);
                setColour (juce::Slider::trackColourId, juce::Colours::cyan);
                setColour (juce::Slider::thumbColourId, juce::Colours::white);
                break;
            }
            case SilverBlack:
            {
                /* Slider default colours */
                setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colours::silver.brighter());
                setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::silver.brighter());
                setColour (juce::Slider::trackColourId, juce::Colours::silver.darker());
                setColour (juce::Slider::thumbColourId, juce::Colours::silver.brighter());
                
                break;
            }
                
            case Cyan:
            {
                setColour (juce::Slider::backgroundColourId, juce::Colours::blue.withBrightness (0.2f));
                setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::blue.withBrightness (0.2f));
                setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkcyan);
                break;
            }
                
            case Uranus:
            {
                /* add shades */
                setColour (juce::Slider::backgroundColourId, juce::Colours::blue.withBrightness (0.2f));
                setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::blue.withBrightness (0.2f));
                setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkcyan);
                setColour (juce::Slider::thumbColourId, juce::Colours::darkcyan);
                break;
            }
            default:
                return;
                
        }
    }
    
    //================================================================================
    /* Slider  */
    
    /* Slider functions.
        This is a middle rotary slider with outer rim, inner body, outer body, and a thumb.
        This is a plane version, so the inner body is placed right in the centre of the
        outer body.
     */
    void RotarLookAndFeel::drawRotarySlider (juce::Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider)
    {
        //=========================================
        /* TEMP. */
        ColourScheme colourScheme = getMidnightColourScheme();
        g.setColour (colourScheme.getUIColour (ColourScheme::outline));
        //g.setColour (juce::Colours::yellow);
        //=========================================
        auto fill = slider.findColour (juce::Slider::rotarySliderFillColourId);
        auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
        juce::Point<float> centre {x + width * 0.5f, y + height * 0.5f};
        auto area = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (5.0f);
        //=========================================
        /* TEMP. */
        g.drawRect (area);
        //=========================================
        auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
        
        /* Outer body and outline. */
        const float outerRadius = juce::jmin (area.getWidth() * 0.5f, area.getHeight() * 0.5f) * sliderOuterRimScaleFactor;
         //const float outerRadius = juce::jmin (area.getWidth() * 0.5f, area.getHeight() * 0.5f) - 5.0f;
        const float rimWidth {2.0f};
        juce::Point<float> outerRimXY {centre.getX() - outerRadius, centre.getY() - outerRadius};
        
        /* Inner body. */
        const float innerRadius = outerRadius * 0.69f;
        juce::Point<float> innerRimXY {centre.getX() - innerRadius, centre.getY() - innerRadius};
        
        if (outlineVisible)
        {
            /*
               - I want to draw starting and ending at different angles from this in input
               - I want to use outline type that can be set by caller
               - delegate this to other functions, maybe helpers?
             */
            juce::Path outerArc;
            outerArc.addCentredArc (centre.getX(),
                                    centre.getY(),
                                    outerRadius,
                                    outerRadius,
                                    0.0f,
                                    rotaryStartAngle,
                                    rotaryEndAngle,
                                    true);
            g.setColour (outline);
            g.strokePath (outerArc, juce::PathStrokeType (rimWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }
        
        if (isThumbOnTop)
        {
            g.setColour (fill);
            g.fillEllipse (innerRimXY.getX(), innerRimXY.getY(), innerRadius * 2.0f, innerRadius * 2.0f);
            g.setColour (slider.findColour (juce::Slider::thumbColourId));
            drawRotaryThumb (g, centre, outerRadius, angle);
        }
        else
        {
            g.setColour (slider.findColour (juce::Slider::thumbColourId));
            drawRotaryThumb (g, centre, outerRadius, angle);
            g.setColour (fill);
            g.fillEllipse (innerRimXY.getX(), innerRimXY.getY(), innerRadius * 2.0f, innerRadius * 2.0f);
        }
    }
    
    int RotarLookAndFeel::getSliderThumbRadius (juce::Slider& slider)
    {
        return juce::jmin (12, slider.isHorizontal() ? static_cast<int> ((float) slider.getHeight() * 0.75f)
                     : static_cast<int> ((float) slider.getWidth()  * 0.75f));
    }
    
    /* Thumb : Triangle, Arrow, Circle
        ThumbFill : OneColour, Gradient
        Track : OneColour, Gradient
     */
    void RotarLookAndFeel::drawLinearSlider (juce::Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, const juce::Slider::SliderStyle, juce::Slider &)
    {
        // todo
        /* At first only Horizonal and Vertical Linear sliders. */
    }
    
    juce::Label* RotarLookAndFeel::createSliderTextBox (juce::Slider& slider)
    {
        auto* l = juce::LookAndFeel_V2::createSliderTextBox (slider);
        /* For linear slider / bar. */
        //l->setColour (juce::Label::outlineColourId, juce::Colours::red);
        /* The following does not work. */
    //    auto textBoxPos = slider.getTextBoxPosition();
    //    if (textBoxPos == juce::Slider::TextBoxBelow || textBoxPos == juce::Slider::TextBoxAbove)
    //    {
    //        juce::Font font = defaultFont.withHeight (juce::jmin (14.0f, slider.getHeight() * 0.1f));
    //        l->setFont (font);
    //    }
        
        /* User must be able to change these! */
    //    auto colour = l->findColour (juce::Label::backgroundColourId).withMultipliedAlpha (0.1f);
    //    l->setColour (juce::Label::backgroundColourId, slider.findColour (juce::Slider::thumbColourId).withMultipliedAlpha (0.5f));
    //    l->setColour (juce::Label::outlineColourId, slider.findColour (juce::Slider::textBoxOutlineColourId));
        l->setColour (juce::Label::backgroundColourId, slider.findColour (juce::Slider::textBoxBackgroundColourId));
        l->setColour (juce::Label::outlineColourId, slider.findColour (juce::Slider::textBoxOutlineColourId));
        l->setColour (juce::Label::textColourId, slider.findColour (juce::Slider::textBoxTextColourId));
        l->setFont (defaultFont);
        l->setMinimumHorizontalScale (1.0f);
        return l;
    }
    
    // WHAT'S THIS?
    juce::Slider::SliderLayout RotarLookAndFeel::getSliderLayout (juce::Slider& slider)
    {
        // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints
        int minXSpace = 0;
        int minYSpace = 0;
        auto textBoxPos = slider.getTextBoxPosition();
        if (textBoxPos == juce::Slider::TextBoxLeft || textBoxPos == juce::Slider::TextBoxRight)
            minXSpace = 20;
        else
            minYSpace = 15;
        auto localBounds = slider.getLocalBounds();
        auto textBoxWidth  = juce::jmax (0, juce::jmin (slider.getTextBoxWidth(),  localBounds.getWidth() - minXSpace));
        auto textBoxHeight = juce::jmax (0, juce::jmin (slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));
        juce::Slider::SliderLayout layout;
        // 2. set the textBox bounds
        if (textBoxPos != juce::Slider::NoTextBox)
        {
            if (slider.isBar())
            {
                layout.textBoxBounds = localBounds;
            }
            else
            {
                layout.textBoxBounds.setWidth (textBoxWidth);
                layout.textBoxBounds.setHeight (textBoxHeight);
                if (textBoxPos == juce::Slider::TextBoxLeft)           layout.textBoxBounds.setX (0);
                else if (textBoxPos == juce::Slider::TextBoxRight)     layout.textBoxBounds.setX (localBounds.getWidth() - textBoxWidth);
                else /* above or below -> centre horizontally */ layout.textBoxBounds.setX ((localBounds.getWidth() - textBoxWidth) / 2);
                if (textBoxPos == juce::Slider::TextBoxAbove)          layout.textBoxBounds.setY (0);
                else if (textBoxPos == juce::Slider::TextBoxBelow)     layout.textBoxBounds.setY (localBounds.getHeight() - textBoxHeight);
                else /* left or right -> centre vertically */    layout.textBoxBounds.setY ((localBounds.getHeight() - textBoxHeight) / 2);
            }
        }
        // 3. set the slider bounds
        layout.sliderBounds = localBounds;
        if (slider.isBar())
        {
            layout.sliderBounds.reduce (1, 1);   // bar border
        }
        else
        {
            if (textBoxPos == juce::Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft (textBoxWidth);
            else if (textBoxPos == juce::Slider::TextBoxRight) layout.sliderBounds.removeFromRight (textBoxWidth);
            else if (textBoxPos == juce::Slider::TextBoxAbove) layout.sliderBounds.removeFromTop (textBoxHeight);
            else if (textBoxPos == juce::Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom (textBoxHeight);
            const int thumbIndent = getSliderThumbRadius (slider);
            if (slider.isHorizontal())    layout.sliderBounds.reduce (thumbIndent, 0);
            else if (slider.isVertical()) layout.sliderBounds.reduce (0, thumbIndent);
        }
        return layout;
    }
    
    //================================================================================
    /* Button  */
    
    void RotarLookAndFeel::setToggleButtonTickStyle (RotarLookAndFeel::ToggleButtonTickStyle style)
    {
        tickStyle = style;
    }
    
    juce::Font RotarLookAndFeel::getFont() const
    {
        return defaultFont;
    }
    
    juce::Font RotarLookAndFeel::getTextButtonFont (juce::TextButton& tb, int height)
    {
        return defaultFont.withHeight(juce::jmin (16.0f, tb.getHeight() * 0.5f));
    }
    
    // todo
    void RotarLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isButtonHighlighted, bool isButtonDown)
    {
        auto area = button.getLocalBounds().toFloat().reduced (1.0f);
        //auto cornerSize = juce::jmin (6.0f, juce::jmin (area.getWidth(), area.getHeight()) * 0.25f);
        auto baseColour = backgroundColour.withMultipliedSaturation ((button.hasKeyboardFocus (true) ? 1.3f : 0.9f)).withMultipliedAlpha((button.isEnabled()) ? 1.0f : 0.5f);
        if (isButtonDown || isButtonHighlighted)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.05f);
        auto buttonOn = button.findColour (juce::TextButton::buttonOnColourId);
        const float maxRadius = juce::jmin (area.getWidth() * 0.5f, area.getHeight() * 0.5f);
        const float rimWidth { 2.0f };
        //const float shadowWidth { 4.0f };
        const float shadowWidth { juce::jmin (maxRadius * 0.25f, 4.0f) };
        if (buttonShape == ButtonShape::Circle)
        {
            const float rimRadius = maxRadius - rimWidth;
            const float shadowRadius = maxRadius - shadowWidth;
            juce::Point<float> rimXY {area.getCentreX() - maxRadius, area.getCentreY() - maxRadius};
            if (isButtonDown)
            {
                g.setColour (buttonOn);
                g.fillEllipse(rimXY.getX(), rimXY.getY(), maxRadius * 2.0f, maxRadius * 2.0f);
                g.setColour (juce::Colours::black.withMultipliedAlpha (0.5f));
                g.drawEllipse (rimXY.getX() + shadowWidth , rimXY.getY() + shadowWidth, shadowRadius * 2.0f, shadowRadius * 2.0f, shadowWidth);
            }
            else
            {
                g.setColour (baseColour);
                g.fillEllipse(rimXY.getX(), rimXY.getY(), maxRadius * 2.0f, maxRadius * 2.0f);
            }
            g.setColour (juce::Colours::black);
            g.drawEllipse (rimXY.getX() + rimWidth, rimXY.getY() + rimWidth , rimRadius * 2.0f, rimRadius * 2.0f, rimWidth);
        }
        else if (buttonShape == ButtonShape::Rect)
        {
            
        }
        
        else if (buttonShape == ButtonShape::RoundedRect)
        {
            
        }
        
        else if (buttonShape == ButtonShape::Custom)
        {
            /* rounded triangle with direction. */
            /* button to fit the shape of the environment. */
        }
    }
    
    // TODO!
    void RotarLookAndFeel::drawToggleButton (juce::Graphics& g, juce::ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
    {
        auto fontSize = juce::jmin (15.0f, (float) button.getHeight() * 0.75f);
        auto tickWidth = fontSize * 1.1f;
        
        /* the button style must use buttonShape.
            So I need to change drawTickBox function to be able to draw different shapes.
         */
        if (tickStyle == ToggleButtonTickStyle::Tick){
            drawTickBox (g, button, 4.0f, ((float) button.getHeight() - tickWidth) * 0.5f,
                         tickWidth, tickWidth,
                         button.getToggleState(),
                         button.isEnabled(),
                         shouldDrawButtonAsHighlighted,
                         shouldDrawButtonAsDown);
        }
        else if (tickStyle == ToggleButtonTickStyle::Cross)
        {
            //drawCrossBox
        }
        
        else if (tickStyle == ToggleButtonTickStyle::Fill)
        {
            // this is like the TextButton
        
        }
        
        g.setColour (button.findColour (juce::ToggleButton::textColourId));
        g.setFont (fontSize);
        
        if (! button.isEnabled())
            g.setOpacity (0.5f);
        
        g.drawFittedText (button.getButtonText(),
                          button.getLocalBounds().withTrimmedLeft (juce::roundToInt (tickWidth) + 10)
                          .withTrimmedRight (2),
                          juce::Justification::centredLeft, 10);
    }
    
    //================================================================================
    /* Label */
    
   juce::Font RotarLookAndFeel::getLabelFont (juce::Label& l)
    {
        return l.getFont();
    }
    
    juce::BorderSize<int> RotarLookAndFeel::getLabelBorderSize(juce::Label& l)
    {
        return l.getBorderSize();
    }

    void RotarLookAndFeel::drawLabel (juce::Graphics& g, juce::Label& label)
    {
        // fill the area
        g.fillAll (label.findColour (juce::Label::backgroundColourId));

        // set the text properties
        if (! label.isBeingEdited())
        {
            auto alpha = (label.isEnabled()) ? 1.0f: 0.2f;
            const juce::Font font {getLabelFont (label)};
            g.setColour (label.findColour (juce::Label::textColourId).withMultipliedAlpha (alpha));
            g.setFont (font);
            /** Draw the text. */
            auto textArea = getLabelBorderSize (label).subtractedFrom     (label.getLocalBounds());
            g.drawFittedText (label.getText(), textArea, label.getJustificationType(), juce::jmax (1, static_cast<int> (static_cast<float>(textArea.getHeight()) / font.getHeight())), label.getMinimumHorizontalScale() );
            g.setColour (label.findColour (juce::Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        else if (label.isEnabled())
        {
            g.setColour (label.findColour (juce::Label::outlineColourId));
        }

        // draw a rounded rectangle
        //g.setColour (label.findColour (juce::Label::outlineColourId));
        g.drawRect (label.getLocalBounds());
    }
    
    //================================================================================
    /* ComboBox, PopupMenu, Font etc. */
    
    void RotarLookAndFeel::drawComboBox (juce::Graphics& g, int width, int height, bool down, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box)
    {
        /* box properties */
        auto cornerSize = box.findParentComponentOfClass<juce::ChoicePropertyComponent>() != nullptr ? 0.0f : juce::jmax (height * 0.1f, 3.0f);
        juce::Rectangle<int> area (0, 0, width, height);
        g.setColour (box.findColour (juce::ComboBox::backgroundColourId));
        g.fillRoundedRectangle (area.toFloat(), cornerSize);
        g.setColour (box.findColour (juce::ComboBox::outlineColourId));
        g.drawRoundedRectangle (area.toFloat(), cornerSize, 1.0f);
        //g.drawRect (area);
        
        /* an arrow */
    //    float side = juce::jmin (area.getWidth() * 0.25f, area.getHeight() * 0.6f);
    //    juce::Point<float> arrowCentre ;
        float side = juce::jmin (area.getWidth() * 0.1f, area.getHeight() * 0.2f);
        juce::Rectangle<float> arrowBox {(juce::Rectangle<float>{side, side}).withCentre ({width - edge - side * 0.5f, (float)area.getCentreY()})};
        juce::Path p;
        p.startNewSubPath (arrowBox.getX(), arrowBox.getY());
        p.lineTo (arrowBox.getCentreX(), arrowBox.getBottom());
        p.lineTo (arrowBox.getRight(), arrowBox.getY());
        p.closeSubPath();
        g.strokePath (p, juce::PathStrokeType {2.0f});
        //g.drawRect((juce::Rectangle<float>{side, side}).withCentre (arrowCentre));
        
    }
    
    void RotarLookAndFeel::drawPopupMenuBackground (juce::Graphics& g, int width, int height)
    {
        g.fillAll (findColour (juce::PopupMenu::backgroundColourId));
        
    #if ! JUCE_MAC
        g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
        g.drawRect (0, 0, width, height);
    #endif
    }
    
    void RotarLookAndFeel::positionComboBoxText (juce::ComboBox& box, juce::Label& label)
    {
        label.setColour (juce::Label::outlineColourId, box.findColour (juce::ComboBox::backgroundColourId).withMultipliedAlpha(0.0f));
        label.setBounds (1, 1,
                         box.getWidth() - 10,
                         box.getHeight() - 2);
        label.setFont (getComboBoxFont (box));
    }
    
    juce::Font RotarLookAndFeel::getComboBoxFont (juce::ComboBox& box)
    {
        return defaultFont.withHeight (juce::jmin (fontHeight, box.getHeight() * 0.72f));
    }
    
    void RotarLookAndFeel::setFontHeight (const float& newHeight)
    {
        /* we don't need any micro fonts. */
        if (newHeight < 8.0f)
            fontHeight = 8.0f;
        fontHeight = newHeight;
    }
    
    /* Miscellaneous */
    
    /* Special colour functions. */
    //================================================================================
    void RotarLookAndFeel::setThumbGradientTargetColour (const juce::Colour& colour)
    { //todo
        
    }
    void RotarLookAndFeel::setTrackGradientTargetColour (const juce::Colour& colour)
    { //todo
        
    }
    void RotarLookAndFeel::setThumbShadowColour (const juce::Colour& colour)
    { //todo
        
    }
    
    /* Setters */
    //================================================================================
    
    /* Test this (unit test).
        The drawing may overcomplicate the drawRotary method.
        Delegate drowing the arc to other methods?
     */
    void RotarLookAndFeel::setOutlineType (OutlineType outlineType)
    {
        localOutlineType = outlineType;
    }
    
    void RotarLookAndFeel::setThumbPosition (bool isOnTop)
    {
        isThumbOnTop = isOnTop;
    }
    
    /* If outline is not visible, only sliderFill and sliderThumb
     are visible, but outer body (outline is still drown, it's just transparent.
     */
    
    bool RotarLookAndFeel::isOutlineVisible() const
    {
        return outlineVisible;
    }
    
    void RotarLookAndFeel::setOutlineVisibility (bool isVisible)
    {
        outlineVisible = isVisible;
    }
    
    void RotarLookAndFeel::setTrackVisibility (bool isVisible)
    {
        isTrackVisible = isVisible;
    }
    
    void RotarLookAndFeel::setComponentAreaOutlinerVisibility(bool isVisible) {
        isComponentAreaOutlinerVisible = isVisible;
    }
    
    /* Protected */
    //================================================================================
    
    void RotarLookAndFeel::drawRotaryThumb (juce::Graphics& g, const juce::Point<float> centre, const float& radius, const float& angle) noexcept
    {
        /* Thumb dimentions (rectangle). */
        const float thumbWidth = radius * 0.27f;
        const float thumbHeight = radius * 0.33f;
        
        juce::Path p;
        p.addRectangle (-thumbWidth * 0.5, -radius * 0.87f, thumbWidth, thumbHeight);
        p.applyTransform (juce::AffineTransform::rotation (angle).translated (centre));
        g.fillPath (p);
    }
    
    void RotarLookAndFeel::drawComponentArea(juce::Graphics& g, const juce::Rectangle<float>& area, juce::Component* component) noexcept
    {
        g.setColour (juce::Colours::orange);
        g.drawRect (area);
//        g.setColour (slider.findColour (juce::Slider::backgroundColourId));
//        g.drawRect (slider.getLocalBounds());
    }
    
    //================================================================================
    /* Rotary Big Slider */
    //================================================================================
    
    //================================================================================
    /* Constructors */
    
    RotarBigRotaryLookAndFeel::RotarBigRotaryLookAndFeel(unsigned char colourStyle)
    :RotarLookAndFeel(colourStyle) {}
    RotarBigRotaryLookAndFeel::~RotarBigRotaryLookAndFeel() {}
    
    void RotarBigRotaryLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                                      float sliderPosProportional, float rotaryStartAngle,
                                                      float rotaryEndAngle, juce::Slider& slider)
    {
        
        auto background = slider.findColour (juce::Slider::backgroundColourId);
        auto fill = slider.findColour (juce::Slider::rotarySliderFillColourId);
        auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
        auto thumb = slider.findColour (juce::Slider::thumbColourId);
        juce::Point<float> centre {x + width * 0.5f, y + height * 0.5f};
        auto area = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (edge);
        auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
        
        if (isComponentAreaOutlinerVisible)
            drawComponentArea(g, area, &slider);
        
        /* Outer body. */
        float outerRimArcWidth {3.0f};
        float outerRimRadius {juce::jmin (area.getWidth() * 0.5f, area.getHeight() * 0.5f) - ((outerRimArcWidth > edge - 1.0f) ? outerRimArcWidth - edge - 1.0f : 0.0f)};
        juce::Point<float> outerRimXY {centre.getX() - outerRimRadius, centre.getY() - outerRimRadius};
        
        g.setColour (background);
        g.drawRect (juce::Rectangle<int> (x, y, width, height));
        if (backgroundFill == RotaryBackgroundFillShape::Circular)
        {
            g.fillEllipse (outerRimXY.getX(), outerRimXY.getY(), outerRimRadius * 2.0f, outerRimRadius * 2.0f);
        }
        else if (backgroundFill == RotaryBackgroundFillShape::Rectangular)
        {
            g.fillRect (area);
        }
        
        /* Arc section. */
//        float arcRadius = outerRimRadius - ( (edge > outerRimArcWidth) ? edge : outerRimArcWidth + edge);
        float arcRadius = outerRimRadius * 0.92f;
        juce::Point<float> arcXY { centre.getX() - arcRadius, centre.getY() - arcRadius };
        juce::Path arc;
        arc.addCentredArc (centre.getX(),
                           centre.getY(),
                           arcRadius,
                           arcRadius,
                           0.0f,
                           rotaryStartAngle,
                           rotaryEndAngle,
                           true);
        g.setColour (outline);
        g.strokePath (arc, { outerRimArcWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded });
        /* The thumb. */
        g.setColour (thumb);
        drawRotaryThumb(g, centre, arcRadius, angle);
        
        /* The knob. */
        const float knobRadius = arcRadius * knobToArcScaleFactor;
        juce::Point<float> knobXY { centre.getX() - knobRadius, centre.getY() - knobRadius };
        juce::ColourGradient gradient {
            fill,
            centre,
            thumb,
            centre.withX (centre.getX() - knobRadius),
            true
        };
        g.setGradientFill (gradient);
        g.fillEllipse (knobXY.getX(), knobXY.getY(), knobRadius * 2.0f, knobRadius * 2.0f);
    }
    
    void RotarBigRotaryLookAndFeel::setRotaryBackgroundFeelShape (const RotaryBackgroundFillShape shape)
    {
        backgroundFill = shape;
    }
    
    //================================================================================
    /* Rotary sliders with symmetrical view */
    //================================================================================
    RotarSymmetricalRotaryLookAndFeel::RotarSymmetricalRotaryLookAndFeel(unsigned char colourStyle) : RotarLookAndFeel(colourStyle) {
        
    }
    RotarSymmetricalRotaryLookAndFeel::~RotarSymmetricalRotaryLookAndFeel() {
        setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colours::white);
    }
    
    void RotarSymmetricalRotaryLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider& slider)
    {
        
        auto fill = slider.findColour (juce::Slider::rotarySliderFillColourId);
        auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
        juce::Point<float> centre {x + width * 0.5f, y + height * 0.5f};
        auto area = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (edge);
        auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
        
        /* Outer body. */
        const float outerRadius = juce::jmin (area.getWidth() * 0.5f, area.getHeight() * 0.5f) * sliderOuterRimScaleFactor;
        const float rimWidth = 2.0f;
        juce::Point<float> outerRimXY {centre.getX() - outerRadius, centre.getY() - outerRadius};
        
        /* Inner body. */
        const float innerRadius = outerRadius * knobToArcScaleFactor;
        juce::Point<float> innerRimXY {centre.getX() - innerRadius, centre.getY() - innerRadius};
        
        juce::Path outerArc;
        outerArc.addCentredArc (centre.getX(),
                                centre.getY(),
                                outerRadius,
                                outerRadius,
                                0.0f,
                                rotaryStartAngle,
                                rotaryEndAngle,
                                true);
        g.setColour (outline);
        g.strokePath (outerArc, juce::PathStrokeType (rimWidth, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        juce::Path middleLine;
        middleLine.startNewSubPath (centre.getX(), centre.getY() - outerRadius);
        middleLine.lineTo (centre.getX(), y);
        g.setColour (outline);
        g.strokePath (middleLine, juce::PathStrokeType (rimWidth));
        
        g.setColour (fill);
        g.fillEllipse (innerRimXY.getX(), innerRimXY.getY(), innerRadius * 2.0f, innerRadius * 2.0f);
        
        g.setColour (slider.findColour (juce::Slider::thumbColourId));
        drawRotaryThumb (g, centre, outerRadius, angle);

    }
    
    //================================================================================
    /* Linear sliders with symmetrical view */
    //================================================================================

    RotarSymmetricalLinearLookAndFeel::RotarSymmetricalLinearLookAndFeel() {}
    RotarSymmetricalLinearLookAndFeel::~RotarSymmetricalLinearLookAndFeel() {}
        
}
