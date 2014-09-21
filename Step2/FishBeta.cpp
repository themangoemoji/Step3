/**
* \file FishBeta.cpp
*
* \author Michael H. Wright
*/

#include "stdafx.h"
#include <string>
#include "FishBeta.h"

using namespace std;
using namespace Gdiplus;

/// Fish filename 
const wstring FishBetaImageName(L"images/beta.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishBeta::CFishBeta(CAquarium *aquarium) : CFish(aquarium, FishBetaImageName)
{
}

/**
* \brief Destructor
*/
CFishBeta::~CFishBeta()
{
}

/** \brief Save this fish to an XML node
* \param node The node we are going to be a child of
*/
std::shared_ptr<xmlnode::CXmlNode> CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto fishNode = CFish::XmlSave(node);
	fishNode->SetAttribute(L"type", L"beta");
	fishNode->SetAttribute(L"SpeedX", GetSpeedX());
	fishNode->SetAttribute(L"SpeedY", GetSpeedY());
	return fishNode;
}

