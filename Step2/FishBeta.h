/**
* \file FishBeta.h
*
* \author Michael H. Wright
*
* \brief Class the implements a Beta fish
*/

#pragma once

#include <memory>

#include "Fish.h"


/**
* \brief Implements a Beta fish
*/
class CFishBeta : public CFish
{
public:
	CFishBeta(CAquarium *aquarium);

	/// \brief Default constructor (disabled)
	CFishBeta() = delete;

	/// \brief Copy constructor (disabled)
	CFishBeta(const CFishBeta &) = delete;

	~CFishBeta();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;


private:
};