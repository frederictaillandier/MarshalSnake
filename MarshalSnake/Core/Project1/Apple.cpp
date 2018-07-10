#include "Apple.h"



Apple::Apple()
{
}


Apple::~Apple()
{
}

std::string const Apple::GetType() const
{
	return (std::string("Apple"));
}

void Apple::Respawn()
{
	SetPosition(MarshalAPI::Vector3(rand() % 20 - 10, 0, rand() % 20 - 10));
}
