#pragma once
#include "DrawableObject.h"

class ObjectFactory
{
public:
	virtual DrawableObject* CreateObject() = 0;
};