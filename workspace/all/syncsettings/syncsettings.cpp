#include <cstdio>
#include <unistd.h>

// libmsettings' public header is C (no extern "C" guard); include as extern "C".
extern "C" {
#include "msettings.h"
}

int main (int argc, char *argv[]) {
	InitSettings();
	
	sleep(1);
	SetVolume(GetVolume());
	SetBrightness(GetBrightness());
	return 0;
}
