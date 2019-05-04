/*
 Copyright (C) 2018 Luis Fernando García [http://luiscript.com]
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "ofxDarkKnightAbletonLink.hpp"


ofxDarkKnightAbletonLink::ofxDarkKnightAbletonLink()
{
    link.disableLink();
}

void ofxDarkKnightAbletonLink::setup()
{
    link14 = link24 = link84 = link164 = link44 = link324 =0.0;
    oldBpm = bpm = 120;
    link.enableLink();
    
}

void ofxDarkKnightAbletonLink::update()
{
    if (getModuleEnabled()) {
        
        if (!link.isLinkEnabled()) {
            link.enableLink();
        }
        
        link14 = fmod(link.getBeat(), 1) / 1;
        link24 = fmod(link.getBeat(), 2) / 2;
        link44 = link.getPhase()/link.getQuantum();
        link84 = fmod(link.getBeat(), 8) / 8;
        link164 = fmod(link.getBeat(), 16) / 16;
        link324 = fmod(link.getBeat(), 32) / 32;
        
        numPeersLabel->setLabel(ofToString(link.getNumPeers())  + " LINK  ");
        
        if(oldBpm != bpm)
        {
            link.setBPM(bpm);
            oldBpm = bpm;
        }
        
        bpm = link.getBPM();
    } else {
        if (link.isLinkEnabled()) {
            link.disableLink();
        }
    }
}

void ofxDarkKnightAbletonLink::draw()
{

}

void ofxDarkKnightAbletonLink::addModuleParameters()
{
    numPeersLabel = gui->addLabel("");
    numPeersLabel->setLabelAlignment(ofxDatGuiAlignment::RIGHT);
    gui->addSlider("BPM", 30, 300, 120)->bind(bpm);
    gui->addSlider("1 Beat", 0, 1)->setPrecision(4)->bind(link14);
    gui->addSlider("2 Beats", 0, 1)->setPrecision(4)->bind(link24);
    gui->addSlider("1 Bar", 0, 1)->setPrecision(4)->bind(link44);
    gui->addSlider("2 Bars", 0, 1)->setPrecision(4)->bind(link84);
    gui->addSlider("4 Bars", 0, 1)->setPrecision(4)->bind(link164);
    gui->addSlider("8 Bars", 0, 1)->setPrecision(4)->bind(link324);
    
}

void ofxDarkKnightAbletonLink::unMount()
{
    link.disableLink();
}
