/*
  ==============================================================================

    FilterSection.cpp
    Created: 20 Sep 2020 12:27:10pm
    Author:  syfo_dias

  ==============================================================================
*/

#include <JuceHeader.h>
#include "../Source/FilterSection.h"

//==============================================================================
FilterSection::FilterSection(juce::Colour parentBackground)
{
    localBackground = parentBackground;
    setLookAndFeel (&rotarMainLookAndFeel);
    intialiseFilterControls (alphaFilter);
    intialiseFilterControls (betaFilter);
    alphaFilter.algorithm.addItemList({"LPF", "HPF", "BPF"}, 100);
    alphaFilter.algorithm.setSelectedItemIndex(0);
    betaFilter.algorithm.addItemList({"LPF", "HPF", "BPF"}, 100);

}

FilterSection::~FilterSection()
{
    setLookAndFeel (nullptr);
    //inputFilter.boost.setLookAndFeel (nullptr);
    betaFilter.boost.setLookAndFeel (nullptr);
}

void FilterSection::paint (juce::Graphics& g)
{

    g.fillAll (localBackground);
    
    auto area = getLocalBounds().reduced (edge);
    g.setColour (juce::Colours::red);
    g.drawRect(area);
    juce::Path diagonal;
    diagonal.startNewSubPath(area.getX(), area.getY());
    diagonal.lineTo(area.getX() + area.getWidth(), area.getY() + area.getHeight());
    g.strokePath(diagonal, juce::PathStrokeType {1.0f});
    
    
    g.setColour(juce::Colours::black);
    
    /** Output filter - left bottom secion triangle. */
    juce::Path leftTri;
    leftTri.startNewSubPath (area.getX(), area.getY() + edge);
    leftTri.lineTo (area.getX(), area.getBottom());
    leftTri.lineTo (area.getRight() - edge, area.getBottom());
    leftTri.closeSubPath();
    leftTri = leftTri.createPathWithRoundedCorners (edge * 2.0f);
    g.fillPath(leftTri);
    
    /** Input filter - right upper secion triangle. */
    juce::Path rightTri;
    rightTri.startNewSubPath (area.getRight(), area.getY() + edge);
    rightTri.lineTo (area.getRight(), area.getBottom());
    rightTri.lineTo (area.getX() + edge, area.getY() + edge);
    rightTri.closeSubPath();
    rightTri = rightTri.createPathWithRoundedCorners (edge * 3.0f);
    g.strokePath(rightTri, juce::PathStrokeType (2.0f));
    
    g.setColour (juce::Colours::orange);
    for (auto& area : objectAreas) {
        if (area) {
            g.drawRect(*area);
        }
    }
}
/* Work on proper geometry (angles, edges and stuff.
 This concepts has some vague calculatons and rounding errors!.
 */
void FilterSection::resized()
{
    auto area = getLocalBounds().reduced (edge) ;
    
    //=====================================================================
    /* Alpha filter. */
    auto freqSliderSide = juce::jmin (getHeight() * 0.4f, getWidth() * 0.5f);
    auto midSliderSide = freqSliderSide * 0.67f;
    auto smallSliderSide = midSliderSide * 0.67f;
    auto buttonSide = smallSliderSide * 0.5f;
    
    objectAreas[AlphaFreqRotary] = std::make_unique<juce::Rectangle<int>> (area.withTop(getHeight() - freqSliderSide).withRight (freqSliderSide).reduced (edge));
    objectAreas[AlphaQRotary] = std::make_unique<juce::Rectangle<int>> (area.withBottom (getHeight() - freqSliderSide).withTop (getHeight() - freqSliderSide - midSliderSide).withRight(area.getX() + midSliderSide).reduced (edge));
    objectAreas[AlphaBoostRotary] = std::make_unique<juce::Rectangle<int>> (area.withBottom (objectAreas[AlphaQRotary]->getY()).withTop (objectAreas[AlphaQRotary]->getY() - smallSliderSide).withRight (smallSliderSide).reduced (edge));
    objectAreas[AlphaButton] = std::make_unique<juce::Rectangle<int>>(area.withBottom (objectAreas[AlphaBoostRotary]->getY()).withRight (area.getX() + buttonSide).withTop (objectAreas[AlphaBoostRotary]->getY() - buttonSide).reduced (edge));
    
    alphaFilter.frequency.setBounds (area.withTop(getHeight() - freqSliderSide).withRight (freqSliderSide).reduced (edge));
    alphaFilter.algorithm.setBounds (area.withLeft (freqSliderSide).withTop (getHeight() * 0.9f).withRight (getWidth() * 0.9f).reduced (edge));
    alphaFilter.q.setBounds (*objectAreas[AlphaQRotary]);
    alphaFilter.boost.setBounds (*objectAreas[AlphaBoostRotary]);
    alphaFilter.toggleButton.setBounds (*objectAreas[AlphaButton]);
    
    //=====================================================================
    /* Output filter. */
    objectAreas[BetaQRotary] = std::make_unique<juce::Rectangle<int>> ((*objectAreas[AlphaQRotary]).withCentre({area.getCentreX(), static_cast<int>(area.getY() + edge + edge + objectAreas[AlphaQRotary]->getHeight() * 0.5f)}));
    objectAreas[BetaFreqRotary] = std::make_unique<juce::Rectangle<int>> ((*objectAreas[AlphaFreqRotary]).withCentre({area.getRight() - (int)(freqSliderSide * 0.5f - edge * 0.5f), (int)(area.getY() + midSliderSide * 0.75f + freqSliderSide * 0.5f)}));
    objectAreas[BetaBoostRotary] = std::make_unique<juce::Rectangle<int>> ((*objectAreas[AlphaBoostRotary]).withCentre ({area.getRight() - (int)(smallSliderSide * 0.5f - edge * 0.5f), (int)(area.getY() + midSliderSide * 0.75f + freqSliderSide + smallSliderSide * 0.5f) }));
    objectAreas[BetaButton] = std::make_unique<juce::Rectangle<int>>((*objectAreas[AlphaButton]).withCentre({static_cast<int>(area.getRight() - (int)(buttonSide * 0.5f)), (int)(objectAreas[BetaBoostRotary]->getBottom() + buttonSide * 0.5f) }));
    
    betaFilter.frequency.setBounds (*objectAreas[BetaQRotary]);
    betaFilter.q.setBounds (*objectAreas[BetaFreqRotary]);
    betaFilter.boost.setBounds (*objectAreas[BetaBoostRotary]);
    betaFilter.toggleButton.setBounds (*objectAreas[BetaButton]);

}

void FilterSection::intialiseFilterControls (FilterControls &filterControls)
{
    addAndMakeVisible (& (filterControls.frequency) );
    addAndMakeVisible (& (filterControls.q) );
    addAndMakeVisible (& (filterControls.boost) );
    addAndMakeVisible (& (filterControls.algorithm) );
    addAndMakeVisible (& (filterControls.amount));
    addAndMakeVisible (& (filterControls.toggleButton));
    
    filterControls.frequency.setRange (20.0, 20000.0);
    filterControls.frequency.setSkewFactorFromMidPoint (1000.0);
    filterControls.frequency.setValue (1000.0);
    filterControls.frequency.setNumDecimalPlacesToDisplay (1);
    if (&filterControls == &alphaFilter)
    {
        filterControls.frequency.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::silver.brighter());
        filterControls.frequency.setColour(juce::Slider::thumbColourId, juce::Colours::silver.brighter());
        filterControls.frequency.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::silver.brighter());
        filterControls.q.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::silver.brighter());
        filterControls.q.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::silver.brighter());
        filterControls.q.setColour(juce::Slider::thumbColourId, juce::Colours::silver.brighter());
    }
    
    else if (&filterControls == &betaFilter)
    {
        filterControls.frequency.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::blue.withBrightness(0.2f));
        filterControls.frequency.setColour(juce::Slider::thumbColourId, juce::Colours::blue.withBrightness(0.2f));
        filterControls.frequency.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::blue.withBrightness(0.2f));
        filterControls.q.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::blue.withBrightness(0.2f));
        filterControls.q.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::blue.withBrightness(0.2f));
        filterControls.q.setColour(juce::Slider::thumbColourId, juce::Colours::blue.withBrightness(0.2f));
    }
    
    filterControls.boost.setLookAndFeel (&smallSliderLookAndFeel);
//    filterControls.boost.setColour(juce::Slider::backgroundColourId, juce::Colours::silver);
}

