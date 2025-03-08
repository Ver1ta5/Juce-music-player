/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 9 Feb 2023 4:48:29am
    Author:  Y

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse)
    : audioThumb(1000, formatManagerToUse, cacheToUse),
    fileLoaded(false), position(0)

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{

}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(Colours::cadetblue);
    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1); // draw an outline around the component
    g.setColour(Colours::palegoldenrod);

    if (fileLoaded)
    {
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(),0, 1.0f);
        g.setColour(Colours::violet);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight(), 1);
      
    }
    else
    {
        g.setFont(20.0f);
        g.drawText("File not loaded...", getLocalBounds(),
            Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
void WaveformDisplay::loadURL(URL audioURL)
{
    
    audioThumb.clear();
    fileLoaded=audioThumb.setSource(new URLInputSource(audioURL));
    if (fileLoaded)
    {
        std::cout << "loaded" << std::endl;
    }
    else
    {
        std::cout << "not loaded" << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* Source)
{
    std::cout << "updated" << std::endl;
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position && pos>0)
    {
        position = pos;
        repaint();
    }
}


