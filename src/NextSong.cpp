/*
  ==============================================================================

    NextSong.cpp
    Created: 13 Mar 2023 5:40:30am
    Author:  Y

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NextSong.h"

//==============================================================================
NextSong::NextSong(DJAudioPlayer* _djAudioPlayer) :djAudioPlayer(_djAudioPlayer)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(forwardButton);
    forwardButton.addListener(this);
}

NextSong::~NextSong()
{
}

void NextSong::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (juce::Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("NextSong", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text
}

void NextSong::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    forwardButton.setBounds(0, 0, 30, 30);
}

void NextSong::buttonClicked(Button* button) {
    if (button == &forwardButton) 
    {
        djAudioPlayer->setPositionRelative(djAudioPlayer->getPositionRelative() + 0.1);
    }
}