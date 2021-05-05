/**
 * \file Cow.h
 *
 * \author Winnie Yang
 *
 * Class that describes a cow.
 * 
 * This class holds a collection of cows that make
 * up the cow inventory of the farm.
 */


#pragma once
#include <string>
#include "Animal.h"

/**
 * Class that describes a cow.\
 * 
 * Holds a collection of cows that make up the cow inventory.
 */
class CCow : public CAnimal
{
public:
	/// The types of cow we can have on our farm
	enum class Type { Bull, BeefCow, MilkCow };

    void ObtainCowInformation();
    void DisplayAnimal();

private:
    /// The cow's name
    std::string mName;

    /// The type of cow: Bull, BeefCow, or MilkCow
    Type mType = Type::MilkCow;

    /// The milk production for a cow in gallons per day
    double mMilkProduction = 0;
};

