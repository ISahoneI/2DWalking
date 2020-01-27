#pragma once

#include "sound.h"

class Ambient : public Sound {
	private:
		
		
	public:
		Ambient();
		~Ambient();

		void play(ALuint buffer, float volume, float pitch);
};
