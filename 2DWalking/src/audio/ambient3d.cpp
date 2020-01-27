#include "ambient3d.h"


Ambient3d::Ambient3d() : Sound3d()
{
	alSourcei(id, AL_LOOPING, AL_TRUE);
}

Ambient3d::~Ambient3d()
{

}
