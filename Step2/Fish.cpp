/**
 * \file Fish.cpp
 *
 * \author Michael H. Wright
 */

#include "stdafx.h"
#include "Fish.h"
#include "ChildView.h"
#include "Aquarium.h"
#include "XmlNode.h"

using namespace std;

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 400;

/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 200;

/**
 * \brief Constructor
 * \param aquarium the Aquarium object that is being referenced
 * \param filename the filename passed to CItem
 */
CFish::CFish(CAquarium *aquarium, const std::wstring &filename) : CItem(aquarium, filename)
{
	mSpeedX = ((double)rand() / RAND_MAX) * MaxSpeedX;
	mSpeedY = ((double)rand() / RAND_MAX) * MaxSpeedY;
}


/**
* \brief Destructor
*/
CFish::~CFish()
{
}


/** \brief Handle updates in time of our fish
*
* This is called before we draw and allows us to
* move our fish. We add our speed times the amount
* of time that has elapsed.
* \param elapsed Time elapsed since the class call
*/
void CFish::Update(double elapsed)
{

	SetLocation(GetX() + mSpeedX * elapsed,
		GetY() + mSpeedY * elapsed);

	// If fish hits right wall, reverse speed and mirror. 
	// Also allow for padding between screen and image.
	if (mSpeedX > 0 && GetX() >= GetAquarium()->GetWidth() - mHPadding)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}

	// If it hits the left wall, reverse speed and mirror
	if (mSpeedX < 0 && GetX() <= 0 + mHPadding)
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}

	// Top edge, same as about but with respect to Y axis
	if (mSpeedY > 0 && GetY() >= GetAquarium()->GetHeight() - mVPadding)
	{
		mSpeedY = -mSpeedY;
		//SetMirror(mSpeedY < 0);
	}

	// Bottom edge case.
	if (mSpeedY < 0 && GetY() <= 0 + mVPadding)
	{
		mSpeedY = -mSpeedY;
		//SetMirror(mSpeedY < 0);
	}
}


/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* \param node The Xml node we are loading the item from
*/
void CFish::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	mSpeedX = node->GetAttributeDoubleValue(L"SpeedX", 0);
	mSpeedY = node->GetAttributeDoubleValue(L"SpeedY", 0);
}


/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
*/
std::shared_ptr<xmlnode::CXmlNode> CFish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = node->AddChild(L"item");

	itemNode->SetAttribute(L"SeedX", mSpeedX);
	itemNode->SetAttribute(L"SpeedY", mSpeedY);

	return itemNode;
}
