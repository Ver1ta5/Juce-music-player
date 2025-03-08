/*
  ==============================================================================

    PlayListComponent.h
    Created: 10 Feb 2023 2:44:02am
    Author:  Y

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DeckGUI.h"


//==============================================================================
/*
*/
class PlayListComponent  : public juce::Component,
                           public TableListBoxModel,
                           public Button::Listener,
                           public Timer
                           
                           
{
public:
    PlayListComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2);
    ~PlayListComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;
    void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics&, int rowNumber, int columnID, int width, int height, bool rowIsSelected) override;

    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;

    void buttonClicked(Button* button)override;

    void timerCallback() override;

    std::vector<File> trackFile;
    std::vector<URL> trackPaths;
    std::vector<std::string> trackLength;
    bool duplicateFile;


   




    //to get song length
    AudioFormatManager  PlaylistFormatManager;
    
  
    
     

   //Used for saving tracklist,tracklength and absolute path for the song file
    String saveData;
    TemporaryFile tempFile;
    String toTrackList;
    bool tempFileDeleted;
    std::vector<std::string> saveURL;
    std::vector<String> linkURL;
    

  
   
    

private:
    TableListBox tableComponent;
    
    std::vector<std::string>trackTitle;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    std::vector<std::string>trackTitleCopy;

    TextButton loadButton{"Add to Playlist"};
    FileChooser fChooser{ "Select a file..." };
   
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayListComponent)
};
