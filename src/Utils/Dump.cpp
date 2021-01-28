
#include <cstdio>

#include "Dump.h"

void IOSP::dump(const irr::SEvent::SKeyInput& ki)
{
    printf("SKeyInput\n{\n   Char: %lc\n   Key: %i\n   Pressed: %i\n   Control: %i\n   Shift: %i\n}\n",
        ki.Char, ki.Key, ki.PressedDown, ki.Control, ki.Shift
    );
}
