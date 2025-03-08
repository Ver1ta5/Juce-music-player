/*
  ==============================================================================

    NextSong.h
    Created: 13 Mar 2023 5:40:30am
    Author:  Y

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"


//==============================================================================
/*
*/
class NextSong  : public juce::Component,public Button::Listener
{
public:
    NextSong(DJAudioPlayer* _djAudioPlayer);
    ~NextSong() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button*button) override;
   
    

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NextSong)
        DJAudioPlayer* djAudioPlayer;
    
    TextButton forwardButton{ "forward" };
};
