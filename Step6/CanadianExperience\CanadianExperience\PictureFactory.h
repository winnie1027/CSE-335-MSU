/**
 * \file PictureFactory.h
 *
 * \author Winnie Yang
 *
 * A factory class that builds our picture.
 * 
 */



#pragma once

#include <memory>
#include "Picture.h"

using namespace std;


/**
 * A factory class that builds our picture.
 */
class CPictureFactory
{
public:
	std::shared_ptr<CPicture> Create();
};

