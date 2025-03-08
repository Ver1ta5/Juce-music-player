
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include <vector>
#include <string>
#include "forwardButtonComponent.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget,
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    void timerCallback() override;
    
    void loadTrack(URL(audioURL));
    

private:
    Image play = ImageFileFormat::loadFrom(BinaryData::_555_png, BinaryData::_555_pngSize);
    Image pause = ImageFileFormat::loadFrom(BinaryData::_556_png, BinaryData::_556_pngSize);
    Image stop = ImageFileFormat::loadFrom(BinaryData::_557_png, BinaryData::_557_pngSize);
    ImageButton imgPlayButton;
    ImageButton imgPauseButton;
    ImageButton imgStopButton;
    Image backgroundImage = ImageFileFormat::loadFrom(BinaryData::vecteezy_circletechnologybackgroundfuturisticconceptwithcircuit_6430152_jpg, BinaryData::vecteezy_circletechnologybackgroundfuturisticconceptwithcircuit_6430152_jpgSize);

    //to label the sliders
    Label VolumeLabel;
    Label SpeedLabel;
   
    DJAudioPlayer* player;
    forwardButtonComponent forwardButton{player};
  
    Slider volSlider; 
    Slider speedSlider;
    Slider posSlider;

    FileChooser fChooser{"Select a file..."};

    
   
    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
