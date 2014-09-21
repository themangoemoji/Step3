/**
* \file FishSparty.h
*
* \author Michael H. Wright
*
* \brief Class the implements a Spartan fish
*/

#pragma once

#include <memory>

#include "Fish.h"


/**
* \brief Implements a Sparty fish
*/
class CFishSparty : public CFish
{
public:
	CFishSparty(CAquarium *aquarium);

	/// \brief Default constructor (disabled)
	CFishSparty() = delete;

	/// \brief Copy constructor (disabled)
	CFishSparty(const CFishSparty &) = delete;

	~CFishSparty();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

private:
	
};