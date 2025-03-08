/*
  ==============================================================================

    PlayListComponent.cpp
    Created: 10 Feb 2023 2:44:02am
    Author:  Y

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayListComponent.h"

//==============================================================================
PlayListComponent::PlayListComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2):deckGUI1(_deckGUI1), deckGUI2(_deckGUI2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
   

    //load track
   
    File file = File::getCurrentWorkingDirectory().getChildFile("MusicLibrary.txt");
    saveData = file.getFullPathName();

    FileInputStream input(file);
    
        if (!input.openedOk())
        {
            DBG("error in input");
        }
        else {
            String tempString = input.readString();
            if (!tempString.isEmpty()) {
                 
                toTrackList = tempString;
            }
        }
        
        StringArray tokens;
        tokens.addLines(toTrackList);
        
         tokens.removeEmptyStrings();
         
            
       
         DBG("tokenSize" << tokens.size());
    if (tokens.size() > 2) {
        for (int i = 0; i < (tokens.size()/3); i++) {
            
            
            if (i == 0) {
              
                trackTitle.push_back(tokens[i].toStdString());
                trackLength.push_back(tokens[i + 1].toStdString());
                saveURL.push_back(tokens[i + 2].toStdString());
            }
            else {
                trackTitle.push_back(tokens[i * 3].toStdString());
                trackLength.push_back(tokens[(i * 3) + 1].toStdString());
                saveURL.push_back(tokens[(i * 3) + 2].toStdString());
                /*DBG("saveURL:" << tokens[(i * 3) + 2]);*/
            }
            
        }


   
    }

    for (int j = 0; j < saveURL.size(); j++) {
        File saveFile = File(saveURL[j]);
        trackFile.push_back(saveFile);
        if (trackFile[j].exists()) {
            trackPaths.push_back(URL(trackFile[j]));
        }
        else
        {
            trackFile[j].deleteFile();
        }

        /*  DBG("trackAbsoluteFile:" <<saveURL[j]);*/


    }

   
   

    /////
    PlaylistFormatManager.registerBasicFormats();
   
    
    tableComponent.getHeader().addColumn("Track Title", 1, 400);
    tableComponent.getHeader().addColumn("Duration", 2, 200);
    tableComponent.getHeader().addColumn("player 1", 3, 100);
    tableComponent.getHeader().addColumn("player 2", 4, 100);
    
    
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
    startTimer(200);
      
}

PlayListComponent::~PlayListComponent()
{
    //store all the song in the current music library when the program is terminated
    File file = File::getCurrentWorkingDirectory().getChildFile("MusicLibrary.txt");
    saveData = file.getFullPathName();

    File MusicLibrary = saveData;

    TemporaryFile tempFile(MusicLibrary);
    {
        FileOutputStream fileOutputStream(tempFile.getFile());
        
            if (fileOutputStream.openedOk() == false) {
                DBG("file error");
            }
            else {
               
                    for (int i = 0; i < trackTitle.size(); i++) {
                        fileOutputStream.writeText(trackTitle[i] + "\n", false, false, nullptr);
                        fileOutputStream.writeText(trackLength[i] + "\n", false, false, nullptr);
                        fileOutputStream.writeText(saveURL[i] + "\n", false, false, nullptr);
                        fileOutputStream.flush();
                    }
                
               
            }
            


    }

    bool transfer = tempFile.overwriteTargetFileWithTemporary();
     
    tempFile.deleteTemporaryFile();
    if (!transfer) {
        DBG("error in transfer");
    }
    

    tableComponent.setModel(nullptr);
    
}

void PlayListComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
   


    
    tableComponent.setColour(TableListBox::backgroundColourId,Colours::steelblue);
    

    g.setColour (juce::Colours::aliceblue);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlayListComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlayListComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight()-50);
    loadButton.setBounds(0, getHeight()-50, getWidth(), 50);
    

}

int PlayListComponent::getNumRows()
{
    
    return trackTitle.size();
}

void PlayListComponent::paintRowBackground(Graphics & g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::aliceblue);
    }
    else
    {
        g.fillAll(Colours::antiquewhite);
    }
}



void PlayListComponent::paintCell(Graphics& g, int rowNumber, int columnID, int width, int height, bool rowIsSelected)
{

    //draw the tracktitle in column 1

    if (columnID == 1 && rowNumber<trackTitle.size()) {
        g.drawText(trackTitle[rowNumber], // the important bit
            trackTitle.size(), 2,
            400, height,
            Justification::centredLeft,
            true);
   }

    //draw the trackLength in column 2
    if (columnID == 2 ) {
        g.drawText(trackLength[rowNumber], // the important bit
            trackLength.size(), 2,
            400, height,
            Justification::centredLeft,
            true);
    }

    

    

    
}

Component* PlayListComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    //create load button at column so that you can load track when pressing it later and store the button id
    
        if (columnId == 3)
        {
            if (existingComponentToUpdate == nullptr)
            {
                TextButton* btn = new TextButton{ "load" };
                String id{ std::to_string(rowNumber) };
                btn->setComponentID(id);
                btn->addListener(this);
                existingComponentToUpdate = btn;
            }
        }
        if (columnId == 4)
        {
            if (existingComponentToUpdate == nullptr)
            {
                TextButton* btn2 = new TextButton{ "load" };
                String id2{ std::to_string(rowNumber+1000) };
                btn2->setComponentID(id2);
                btn2->addListener(this);
                existingComponentToUpdate = btn2;
            }
        }

    

   
    return existingComponentToUpdate;
}




void PlayListComponent::buttonClicked(Button* button)
{
    //to create playlist
    if (button == &loadButton)
    {
        DBG("create list button press");
        auto fileChooserFlags =
            FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
            {

                DBG("File selected");
        auto chosenFile = chooser.getResult();

        //for loop for checking for duplicate file
        if (trackFile.size() > 0) {
            for (int a = 0; a < trackFile.size(); a++)
            {
                if (chosenFile.getFileName() == trackFile[a].getFileName()) {
                    duplicateFile = true;
                    AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Duplicate File", "File already in playlist", "Ok", nullptr);
                }
                else {
                    duplicateFile = false;
                }
            }
        }
        else {
            duplicateFile = false;
        }


        //if statement so that if a file is not selected it will not create a blank row
        if (chosenFile.existsAsFile() == true && duplicateFile == false)
        {
            DBG("duplicate File: false ,chosenfile: exisit");
            trackFile.push_back(chosenFile);
            trackPaths.push_back(URL(trackFile[trackFile.size() - 1]));
            trackTitle.push_back(trackFile[trackFile.size() - 1].getFileNameWithoutExtension().toStdString());
            saveURL.push_back((trackFile[trackFile.size() - 1].getFullPathName().toStdString()));



            if (auto FileData = PlaylistFormatManager.createReaderFor((trackFile[trackFile.size() - 1]))) {


                auto reader = PlaylistFormatManager.createReaderFor(trackPaths[trackPaths.size() - 1].createInputStream(false));
                trackLength.push_back(std::to_string(reader->lengthInSamples / (reader->sampleRate) / 60));
            }





        }

            });




    }
    else {

        //if button id is less than 1000  it will load to deckGui 1
        int id = std::stoi(button->getComponentID().toStdString());
        if (id < 1000) {
            for (int i = 0; i < trackPaths.size(); i++) {
                if (id == i) {
                    //loadFile
                    deckGUI1->loadTrack(trackPaths[i]);
                   
                }
            }
        }
        else {
            //if button id is more than 1000  will load to deckGui 2
            for (int j = 1000; j < 1000 + trackPaths.size(); j++) {
                if (id == j) {
                    //loadFile
                    deckGUI2->loadTrack(trackPaths[j - 1000]);
                    
                }
            }
        }

    }

    }


    void PlayListComponent::timerCallback()
    {
        //timer to constatly refresh the playlist to check for new tracks
      
        tableComponent.setModel(this);
        tableComponent.updateContent();
        repaint();
    }



    
        
    

    

    
    
   
    






