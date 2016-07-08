#include "Ability.h"




Ability::Ability(uint32_t texture_id, InGameObject & owner, bool targetable)
	: texture_id(texture_id), owner(owner), targetable(targetable)
{
}

Ability::~Ability()
{
}



