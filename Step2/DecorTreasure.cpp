/**
* \file FishBeta.cpp
*
* \author Michael H. Wright
*/

#include "stdafx.h"
#include "DecorTreasure.h"
#include <string>

using namespace std;
using namespace Gdiplus;

/// Fish filename 
const wstring DecorTreasureImageName(L"images/treasure-chest.png");

/** Constructor
* \param aquarium The aquarium this is a member of
*/
CDecorTreasure::CDecorTreasure(CAquarium *aquarium) : CItem(aquarium, DecorTreasureImageName)
{
}

/**
* \brief Destructor
*/
CDecorTreasure::~CDecorTreasure()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
*/
std::shared_ptr<xmlnode::CXmlNode> CDecorTreasure::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CItem::XmlSave(node);
	itemNode->SetAttribute(L"type", L"treasure-chest");
	return itemNode;
}