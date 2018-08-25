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
    beat0 = 0;
    time14 = time24 = time84 = time164 = time324 = 0.0;
    link14 = link24 = link84 = link164 = link44 = 0.0;
    //gui->getToggle("Enable")->setChecked(false);
    link.enableLink();
}

void ofxDarkKnightAbletonLink::update()
{
    if (getModuleEnabled()) {
        if (!link.isLinkEnabled()) {
            link.enableLink();
            beat0 = link.getBeat();
            //link.setBeatForce(0);
        }
        double beat = link.getBeat() - beat0;
        
        double t14 = beat - time14;
        if(t14 >= 1) time14 = beat;
        
        double t24 = beat - time24;
        if(t24 >= 2) time24 = beat;
        
        double t84 = beat - time84;
        if(t84 >= 8) time84 = beat;
        
        double t164 = beat - time164;
        if(t164 >= 16) time164 = beat;
        
        
        link44 = link.getPhase()/link.getQuantum();
        
        link14 = t14 / 1.0;
        link24 = t24 / 2.0;
        //link44 =
        link84 = t84 / 8.0;
        link164 = t164 / 16.0;
    } else {
        time14 = time24 = time84 = time164 = time324 = 0.0;
        link14 = link24 = link84 = link164 = link44 = 0.0;
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
    //ofxDatGuiFolder * linkFolder = gui->addFolder("Ableton link");
    
    gui->addSlider("1/4", 0, 1)->setPrecision(4)->bind(link14);
    gui->addSlider("2/4", 0, 1)->setPrecision(4)->bind(link24);
    gui->addSlider("4/4", 0, 1)->setPrecision(4)->bind(link44);
    gui->addSlider("8/4", 0, 1)->setPrecision(4)->bind(link84);
    gui->addSlider("16/4", 0, 1)->setPrecision(4)->bind(link164);
}

void ofxDarkKnightAbletonLink::unMount()
{
    link.disableLink();
}
