/**
* \file FishSparty.cpp
*
* \author Michael H. Wright
*/

#include "stdafx.h"
#include <string>
#include "FishSparty.h"

using namespace std;
using namespace Gdiplus;

/// Fish filename 
const wstring FishSpartyImageName(L"images/sparty-fish.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishSparty::CFishSparty(CAquarium *aquarium) : CFish(aquarium, FishSpartyImageName)
{
}


/**
* \brief Destructor
*/
CFishSparty::~CFishSparty()
{
}

/** \brief Save this fish to an XML node
* \param node The node we are going to be a child of
*/
std::shared_ptr<xmlnode::CXmlNode> CFishSparty::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto fishNode = CFish::XmlSave(node);
	fishNode->SetAttribute(L"type", L"sparty");
	return fishNode;
}
