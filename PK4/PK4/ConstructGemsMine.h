#pragma once
#include "Ability.h"

class Hills;
class GemsDeposit;
class GemsMine;

class ConstructGemsMine :
	public Ability
{
public:
	ConstructGemsMine(InGameObject & owner);
	~ConstructGemsMine();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);

private:
	int production = 1;
};

#include "Hills.h"
#include "GemsDeposit.h"
#include "GemsMine.h"