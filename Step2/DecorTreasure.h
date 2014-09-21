/**
* \file FishSparty.h
*
* \author Michael H. Wright
*
* \brief Class the implements a Tresure Decoration Item
*/

#pragma once

#include <memory>

#include "Item.h"


/**
* \brief Implements a Treasure Chest Decor Item
*/
class CDecorTreasure : public CItem
{
public:
	CDecorTreasure(CAquarium *aquarium);

	/// \brief Default constructor (disabled)
	CDecorTreasure() = delete;

	/// \brief Copy constructor (disabled)
	CDecorTreasure(const CDecorTreasure &) = delete;

	~CDecorTreasure();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

private:
};
