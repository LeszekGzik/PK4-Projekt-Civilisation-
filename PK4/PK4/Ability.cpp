#include "Ability.h"




Ability::Ability(uint32_t texture_id, InGameObject & owner)
	: texture_id(texture_id), owner(owner)
{
}

Ability::~Ability()
{
}



