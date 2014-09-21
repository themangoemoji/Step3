/**
* \file FishDory.cpp
*
* \author Michael H. Wright
*/

#include "stdafx.h"
#include <string>
#include "FishDory.h"

using namespace std;
using namespace Gdiplus;

/// Fish filename 
const wstring FishDoryImageName(L"images/dory.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CFishDory::CFishDory(CAquarium *aquarium) : CFish(aquarium, FishDoryImageName)
{
}

/**
* \brief Destructor
*/
CFishDory::~CFishDory()
{
}

/** \brief Save this fish to an XML node
* \param node The node we are going to be a child of
*/
std::shared_ptr<xmlnode::CXmlNode> CFishDory::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto fishNode = CFish::XmlSave(node);
	fishNode->SetAttribute(L"type", L"dory");
	return fishNode;
}