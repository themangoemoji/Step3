/**
* \file Aquarium.cpp
*
* \author Michael H. Wright
*/


#include "stdafx.h"
#include "Aquarium.h"
#include "resource.h"
#include "FishBeta.h"
#include "FishSparty.h"
#include "FishDory.h"
#include "DecorTreasure.h"
#include "XmlNode.h"
#include "Fish.h"
#include "Item.h"


using namespace xmlnode;
using namespace std;
using namespace Gdiplus;


/**
* \brief Constructor
*/
CAquarium::CAquarium()
{
	mBackground = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/background1.png"));
	if (mBackground->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/background1.png");
	}

	mTrashcan = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/trashcan.png"));
}

/**
* \brief Destructor
*/
CAquarium::~CAquarium()
{
}

/** \brief Draw the aquarium
* \param graphics The GDI+ graphics context to draw on
*/
void CAquarium::OnDraw(Gdiplus::Graphics *graphics)
{
	graphics->DrawImage(mBackground.get(), 0, 0,
		mBackground->GetWidth(), mBackground->GetHeight());

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);

	SolidBrush green(Color(0, 64, 0));
	graphics->DrawString(L"Under the Sea!", -1, &font, PointF(2, 2), &green);

	if (mTrashcanActive)
	{
		graphics->DrawImage(mTrashcan.get(), 0, 0,
			mTrashcan->GetWidth(), mTrashcan->GetHeight());
	}

	for (auto item : mItems)
	{
		item->Draw(graphics);
	}
}

/** \brief Add an item to the aquarium
* \param item New item to add
*/
void CAquarium::Add(std::shared_ptr<CItem> item)
{
	mItems.push_back(item);
}

/** \brief Test an x,y click location to see if it clicked
* on some item in the aquarium.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CItem> CAquarium::HitTest(int x, int y)
{
	for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
	{
		if ((*i)->HitTest(x, y))
		{
			return *i;
		}
	}

	return  nullptr;
}

/**
 * \brief Moves Item to front upon mouse click
 */
void CAquarium::MoveToFront(std::shared_ptr<CItem> item)
{
	auto loc = find(begin(mItems), end(mItems), item);
		if (loc != end(mItems))
		{
		mItems.erase(loc);
		}
}

/**
 * \brief Makes trashcan appear or dissapear.
 * \returns bool for trashcan presence.
 */
bool CAquarium::ActivateTrashcan()
{
	if (!mTrashcanActive)
	{
		mTrashcanActive = true;
	}
	else if (mTrashcanActive)
	{
		mTrashcanActive = false;
	}
	return mTrashcanActive;
}

/** \brief Save the aquarium as a .aqua XML file.
*
* Open an XML file and stream the aquarium data to it.
*
* \param filename The filename of the file to save the aquarium to
*/
void CAquarium::Save(const std::wstring &filename)
{
	//
	// Create an XML document
	//
	auto root = CXmlNode::CreateDocument(L"aqua");

	// Iterate over all items and save them
	for (auto item : mItems)
	{
		item->XmlSave(root);
	}

	try
	{
		root->Save(filename);
	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}

/** \brief Load the aquarium from a .aqua XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* \param filename The filename of the file to load the aquarium from.
*/
void CAquarium::Load(const std::wstring &filename)
{
	// We surround with a try/catch to handle errors
	try
	{
		// Open the document to read
		shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

		// Once we know it is open, clear the existing data
		Clear();

		//
		// Traverse the children of the root
		// node of the XML document in memory!!!!
		//
		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"item")
			{
				XmlItem(node);
			}

		}


	}
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}

}

/**
* \brief Clear the aquarium data.
*
* Deletes all known items in the aquarium.
*/
void CAquarium::Clear()
{
	mItems.erase(mItems.begin(), mItems.end());
}

/**
* \brief Count items present in aquarium
*
* Counts all known items in the Aquarium.
*/
int CAquarium::NumItems()
{
	int count = 0;
	count = mItems.size();
	return count;
}


/**
* \brief Handle an item node.
* \param node Pointer to XML node we are handling
*/
void CAquarium::XmlItem(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	// A pointer for the item we are loading
	shared_ptr<CItem> item;

	// We have an item. What type?
	wstring type = node->GetAttributeValue(L"type", L"");
	if (type == L"beta")
	{
		item = make_shared<CFishBeta>(this);
	}
	else if (type == L"treasure-chest")
	{
		item = make_shared<CDecorTreasure>(this);
	}
	else if (type == L"dory")
	{
		item = make_shared<CFishDory>(this);
	}
	else if (type == L"sparty")
	{
		item = make_shared<CFishSparty>(this);
	}

	if (item != nullptr)
	{
		item->XmlLoad(node);
		Add(item);
	}
}

/** \brief Handle updates for animation
* \param elapsed The time since the last update
*/
void CAquarium::Update(double elapsed)
{
	for (auto item : mItems)
	{
		item->Update(elapsed);
	}
}
