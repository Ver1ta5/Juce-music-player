

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class forwardButtonComponent  : public juce::Component, public Button::Listener
{
public:
    forwardButtonComponent(DJAudioPlayer* _djAudioPlayer);
    ~forwardButtonComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (forwardButtonComponent)
        DJAudioPlayer* djAudioPlayer;
    Image buttonImage = ImageFileFormat::loadFrom(BinaryData::_558_png, BinaryData::_558_pngSize);
    ImageButton forwardButton;
};
