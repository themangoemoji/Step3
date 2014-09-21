/**
* \file Item.h
*
* \author Michael H. Wright
*
* \brief Base class for any item in our aquarium.
*/

#pragma once

#include <string>
#include <memory>
#include "XmlNode.h"

class CAquarium;


/**
* \brief Base class for any item in our aquarium.
*/
class CItem
{
public:
	/// \brief Default constructor (disabled)
	CItem() = delete;

	/// \brief Copy constructor (disabled)
	CItem(const CItem &) = delete;

	virtual ~CItem();

	/** \brief The X location of the item
	* \returns X location in pixels */
	double GetX() const { return mX; }

	/** \brief The Y location of the item
	* \returns Y location in pixels */
	double GetY() const { return mY; }

	/** \brief Set the item location
	* \param x X location
	* \param y Y location */
	void SetLocation(double x, double y) { mX = x; mY = y; }

	/** \brief Draw this item
	* \param graphics The graphics context to draw on */
	virtual void Draw(Gdiplus::Graphics *graphics);

	/** \brief Test this item to see if it has been clicked on
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on */
	virtual bool HitTest(int x, int y);

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);


	/// \brief Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed){}

	/// \brief Get the aquarium this item is in
	/// \returns Aquarium pointer
	CAquarium *GetAquarium() { return mAquarium; }

	/// \brief Set the mirror status
	/// \param m New mirror flag
	void SetMirror(bool m) { mMirror = m; }


protected:
	CItem(CAquarium *aquarium, const std::wstring &filename);

	/// The image of this fish
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;


private:
	/// The aquarium this item is contained in
	CAquarium   *mAquarium;

	// Item location in the aquarium
	double   mX = 0;     ///< X location for the center of the item
	double   mY = 0;     ///< Y location for the center of the item

	bool mMirror = false;   ///< True mirrors the fish image

};