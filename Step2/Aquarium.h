/**
* \file Aquarium.h
*
* \author Michael H. Wright
*
* \brief Class that represents an aquarium.
*/
#pragma once

#include <memory>
#include <vector>

#include "XmlNode.h"

class CItem;

using namespace std;

/**
* \brief Represents an aquarium
*/
class CAquarium
{
public:
	CAquarium();

	virtual ~CAquarium();

	void OnDraw(Gdiplus::Graphics *graphics);

	void Add(std::shared_ptr<CItem> item);

	std::shared_ptr<CItem> HitTest(int x, int y);

	void MoveToFront(std::shared_ptr<CItem> item);

	// True/False statement to activate or disable Trashcan

	void Save(const std::wstring &filename);	bool ActivateTrashcan();

	void Load(const std::wstring &filename);

	void Clear();

	int NumItems();

	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode> &node);
	
	void Update(double elapsed);

	/// \brief Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return mBackground->GetWidth(); }

	/// \brief Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return mBackground->GetHeight(); }

private:
	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image to use

	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Trashcan data member to represent the image
	std::unique_ptr<Gdiplus::Bitmap> mTrashcan;

	/// Switch to check if the Trashcan is appearing or not
	bool mTrashcanActive = false;
};

