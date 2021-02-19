
#include "CommonObject.h"

using namespace irr;
using namespace IOSP;

const std::array<irr::core::stringw, CommonObject::TotalFontCount + 1> IOSP::CommonObject::s_fnames
{
    L"Default",
    L"Button",
    L"Window",
    L"Menu",
    L"Tooltip",
    L"Caption",
    L"Number",
    L"Invalid"
};

std::array<irr::gui::IGUIFont*, CommonObject::ExtraFontCount> IOSP::CommonObject::s_extrafonts{nullptr};

irr::u8 IOSP::CommonObject::getFontType(const wchar_t *s)
{
    for(std::size_t i = 0; i < s_fnames.size(); i++)
        if (s_fnames[i] == s)  return i;
    return InvalidFont;
}
