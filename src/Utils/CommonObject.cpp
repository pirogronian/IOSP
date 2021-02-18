
#include "CommonObject.h"

using namespace irr;
using namespace IOSP;

const std::array<irr::core::stringw, CommonObject::TotalFontCount> IOSP::CommonObject::s_fnames
{
    L"Default",
    L"Button",
    L"Window",
    L"Menu",
    L"Tooltip",
    L"Caption",
    L"Number"
};

std::array<irr::gui::IGUIFont*, CommonObject::ExtraFontCount> IOSP::CommonObject::s_extrafonts{nullptr};

irr::u8 IOSP::CommonObject::getFontType(const wchar_t *s)
{
    for(std::size_t i = 0; i < s_fnames.size(); i++)
        if (s_fnames[i] == s)  return i;
    return 255;
}
