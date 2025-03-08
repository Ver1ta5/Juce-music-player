

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"


//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                 AudioFormatManager& formatManagerToUse,
                 AudioThumbnailCache& cacheToUse) : player(_player), waveformDisplay(formatManagerToUse,cacheToUse)
{
    //set image for imagebutton
    imgPlayButton.setImages(true, true, true, play, 1.0f, {}, {}, 1.0f, {}, {}, 1.0f, {}, 0);
    imgPauseButton.setImages(true, true, true, pause, 1.0f, {}, {}, 1.0f, {}, {}, 1.0f, {}, 0);
    imgStopButton.setImages(true, true, true, stop, 1.0f, {}, {}, 1.0f, {}, {}, 1.0f, {}, 0);

    //build a rotary slider to increase vol
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
 
    //build a speed slider to increase sample rate
    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    
    //set slider decimal place
    posSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    volSlider.setNumDecimalPlacesToDisplay(2);

    
  
   
    
  //make button,label and slider visible
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(imgPlayButton);
    addAndMakeVisible(imgPauseButton);
    addAndMakeVisible(imgStopButton);
    addAndMakeVisible(SpeedLabel);
    addAndMakeVisible(VolumeLabel);
    addAndMakeVisible(forwardButton);
    
    
 

    //Add text to label
    VolumeLabel.setText("Volume",dontSendNotification);
    SpeedLabel.setText("Speed",dontSendNotification);

  //make button and slider visible  
    
    imgPlayButton.addListener(this);
    imgPauseButton.addListener(this);
    imgStopButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    //set range of slider
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 5.0);
    posSlider.setRange(0.0, 1.0);

    startTimer(200);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    
    //draw background image for deckGUI background
    g.drawImage(backgroundImage, getLocalBounds().toFloat());

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", 10,0,50,20,
                Justification::left, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;

    VolumeLabel.setBounds(getWidth() /2+20, getHeight() / 2 - 30, 50, 20);
    SpeedLabel.setBounds(getWidth() - 85, getHeight() / 2 -30, 50, 20);
  
    volSlider.setBounds(getWidth()/4+50, getHeight() / 2-10, getWidth()/2, rowH*4);
    speedSlider.setBounds(getWidth()-100, getHeight()/2-10, 80, rowH * 4);
    posSlider.setBounds(0,rowH*2, getWidth(), rowH*2);
    waveformDisplay.setBounds(0, 20, getWidth(), rowH * 2);
  
    imgPlayButton.setBounds(0, rowH * 4 - 20, getWidth() / 4, rowH * 2 + 20);
    imgPauseButton.setBounds(0, rowH * 6, getWidth() / 4-25,rowH*2);
    imgStopButton.setBounds(getWidth() /7, rowH * 6, getWidth() / 4, rowH*2-5);

    forwardButton.setBounds((getWidth() / 18)+getWidth()/6, rowH * 4, getWidth() /8+15 , rowH*2);
    
       
    
    

}

void DeckGUI::buttonClicked(Button* button)
{
    //play song
    if (button == &imgPlayButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }

    //pause song
     if (button == &imgPauseButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }

     //reset to start and stop song
     if (button == &imgStopButton) {
         player->setPositionRelative(0);
         player->stop();
     }

    
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        if (slider->getValue()>0) {
            player->setSpeed(slider->getValue());
            
        }
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
        
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
     
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    std::cout << "Timer" << std::endl;
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    
    

   
}

// to load from playlist component
void DeckGUI::loadTrack(URL audioURL) {
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
 }

