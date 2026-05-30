#include "AudioUtils.h"

#include <algorithm>

int ClampVolume(int volume)
{
	return std::max(0, std::min(volume, 128));
}