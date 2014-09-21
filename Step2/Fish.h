#pragma once
#include "Item.h"
#include "Aquarium.h"
#include "XmlNode.h"

/** \brief Base class for a fish
* This applies to all of the fish, but not the decor
* items in the aquarium.
*/
class CFish : public CItem
{
public:
	/// \brief Default constructor (disabled)
	CFish() = delete;

	/// \brief Copy constructor (disabled)
	CFish(const CFish &) = delete;

	~CFish();

	void Update(double elapsed);

	std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** \brief The X speed of the fish
	* \returns X axis speed of fish */
	double GetSpeedX() const { return mSpeedX; }

	/** \brief The Y speed of the fish
	* \returns Y axis speed of fish */
	double GetSpeedY() const { return mSpeedY; }

private:
	/// Fish speed in the X direction
	double mSpeedX;

	/// Fish speed in the Y direction
	double mSpeedY;

	/// Width of each fish.
	double mWidth = (mItemImage->GetWidth());

	/// Width of each fish.
	double mHeight = (mItemImage->GetHeight());

	/// Amount of horizontal padding needed between fish and screen edges
	double mHPadding = (mWidth/2 + 50);

	/// Amount of vertical padding needed between fish and screen top/bottom
	double mVPadding = (mHeight / 2 + 50);


protected:
	/** Constructor
	* \param aquarium The aquarium we are in
	* \param filename Filename for the image we use
	*/
	CFish(CAquarium *aquarium, const std::wstring &filename);
};

