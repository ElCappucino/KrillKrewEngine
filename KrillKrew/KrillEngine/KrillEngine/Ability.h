#pragma once

class Ability {
	void* abilityFunc;
	std::string name;
public:
	void* getAbility();
	void setAbility(void* ability);
};
