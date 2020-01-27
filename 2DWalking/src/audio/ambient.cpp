#include "ambient.h"


Ambient::Ambient() : Sound()
{
	alSourcei(id, AL_LOOPING, AL_TRUE);
}

Ambient::~Ambient()
{

}
