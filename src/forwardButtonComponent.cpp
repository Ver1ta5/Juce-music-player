

#include <JuceHeader.h>
#include "forwardButtonComponent.h"

//==============================================================================
forwardButtonComponent::forwardButtonComponent(DJAudioPlayer* _djAudioPlayer):djAudioPlayer(_djAudioPlayer)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    //create an imageless button and make it visible and have listener 
    forwardButton.setImages(true, true, true, {}, 1.0f, {}, {}, 1.0f, {}, {}, 1.0f, {}, 0);
    addAndMakeVisible(forwardButton);
    forwardButton.addListener(this);
}

forwardButtonComponent::~forwardButtonComponent()
{
}

void forwardButtonComponent::paint (juce::Graphics& g)
{
  

   //draw the button image to cover the entire component 
    g.drawImage(buttonImage, getLocalBounds().toFloat());



  
}

void forwardButtonComponent::resized()
{
    
    //set the entire size of the component as a button
    forwardButton.setBounds(0, 0, getWidth(), getHeight());

}

void forwardButtonComponent::buttonClicked(Button* button) {
    if (button == &forwardButton)
    {
        djAudioPlayer->setPositionRelative(djAudioPlayer->getPositionRelative() + 0.1);
    }
}
