#include "emu.Settings.h"
/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "emu.log.h"
#include "emu.Settings.h"

#include "tinyxml2.h"

//#include <map>

using namespace tinyxml2;

emu::Settings * settings = 0;

emu::Settings::Settings()
{
    //Save("pspe4all.xml");
    //Load("pspe4all.xml");
    XMLDocument xmlDoc;
    XMLError    eResult = xmlDoc.LoadFile("pspe4all.xml");
    if (eResult != XML_SUCCESS)
    {
        //we haven't found a xml file create a new one with default settings
        debugf(emu, "Cannot find pspe4all.xml. Creating default one");
        CreateDefaultXml("pspe4all.xml");
    }
    Load("pspe4all.xml");
}


emu::Settings::~Settings()
{
}

void emu::Settings::Save(char const * filename)
{
    XMLDocument xmlDoc;

    XMLNode * pRoot = xmlDoc.NewElement("pspe4all");
    xmlDoc.InsertFirstChild(pRoot);
    XMLElement * pElement = xmlDoc.NewElement("GeneralSettings");

    XMLElement * pListElement = xmlDoc.NewElement("CpuMode");
    pListElement->SetText(cpumode.c_str());

    pElement->InsertEndChild(pListElement);

    XMLElement * pListElement2 = xmlDoc.NewElement("GeRenderer");
    pListElement2->SetText(gerenderer.c_str());

    pElement->InsertEndChild(pListElement2);

    pRoot->InsertEndChild(pElement);

    xmlDoc.SaveFile(filename);
}

void emu::Settings::Load(char const * filename)
{
    XMLDocument xmlDoc;
    XMLError eResult = xmlDoc.LoadFile(filename);
    if (eResult != XML_SUCCESS)
    {
        //something went wrong with loading create a default one
        debugf(emu, "Can't load pspe4all.xml .Creating adefault one");
        CreateDefaultXml(filename);
        return;
    }
    XMLNode * pRoot = xmlDoc.FirstChild();
    XMLElement * pElement = pRoot->FirstChildElement("GeneralSettings");
    XMLElement * pListElement = pElement->FirstChildElement("CpuMode");
    cpumode = pListElement->GetText();
    pListElement = pListElement->NextSiblingElement("GeRenderer");
    gerenderer = pListElement->GetText();

    debugf(emu, "Loaded %s from pspe4all.xml", cpumode.c_str());
    debugf(emu, "Loaded %s from pspe4all.xml", gerenderer.c_str());
}

void emu::Settings::CreateDefaultXml(char const * filename)
{
    cpumode = "interpeter-slow";
    gerenderer = "pspe4all-hal.video.OGL4";

    XMLDocument xmlDoc;

    XMLNode * pRoot = xmlDoc.NewElement("pspe4all");
    xmlDoc.InsertFirstChild(pRoot);
    XMLElement * pElement = xmlDoc.NewElement("GeneralSettings");

    XMLElement * pListElement = xmlDoc.NewElement("CpuMode");
    pListElement->SetText(cpumode.c_str());

    pElement->InsertEndChild(pListElement);

    XMLElement * pListElement2 = xmlDoc.NewElement("GeRenderer");
    pListElement2->SetText(gerenderer.c_str());

    pElement->InsertEndChild(pListElement2);

    pRoot->InsertEndChild(pElement);

    xmlDoc.SaveFile(filename);
}