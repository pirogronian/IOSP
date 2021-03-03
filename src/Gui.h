
#pragma once

#include <Utils/Sequence.h>

namespace IOSP
{
    enum GuiElements
    {
        OpenTTFButton = 1,
        OpenTTFFileDialog,
        SettingsDialog,
        GlobalGuiMaxId
    };

    extern SimpleSequence ImGuiIDs;
}
