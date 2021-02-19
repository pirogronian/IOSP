
#pragma once

#include <array>
#include <irrlicht.h>
#include <CGUITTFont.h>
#include <Utils/IrrCommonObject.h>

namespace IOSP
{
    class CommonObject : public IrrCommonObject
    {
    public:
        enum ExtraFontType
        {
            ExtraCaptionFont = 0,
            ExtraNumberFont = 1
        };
        enum FontType
        {
            CaptionFont = irr::gui::EGDF_COUNT + ExtraCaptionFont,
            NumberFont = irr::gui::EGDF_COUNT + ExtraNumberFont
        };
        static constexpr irr::u8 ExtraFontCount = 2;
        static constexpr irr::u8 TotalFontCount = irr::gui::EGDF_COUNT + ExtraFontCount;
    protected:
        static const std::array<irr::core::stringw, TotalFontCount> s_fnames;
        static std::array<irr::gui::IGUIFont*, ExtraFontCount> s_extrafonts;
    public:
        static const irr::core::stringw& getFontName(irr::u8 i) { return s_fnames[i]; }
        static irr::u8 getFontType(const wchar_t*);
        static irr::u8 getFontType(const irr::core::stringw& s) { return getFontType(s.c_str()); }
        static irr::gui::IGUIFont *getExtraFont(ExtraFontType i) { return s_extrafonts[i]; }
        static void setExtraFont(irr::u8 i, irr::gui::IGUIFont *f) { s_extrafonts[i] = f; }
        static bool isExtraFont(irr::u8 i) { return i >= irr::gui::EGDF_COUNT; }
        static bool isValidFont(irr::u8 i) { return i <  TotalFontCount; }
        static bool isFontExtraAndValid(irr::u8 i) { return isExtraFont(i) && isValidFont(i); }
        static bool isIrrlichtFont(irr::u8 i) { return i < irr::gui::EGDF_COUNT; }
        static irr::u8 toExtraFont(irr::u8 i) { return i - irr::gui::EGDF_COUNT; }
        static irr::gui::IGUIFont *getFont(irr::u8 i = irr::gui::EGDF_DEFAULT) {
            if (isIrrlichtFont(i))  return IrrCommonObject::getFont(static_cast<irr::gui::EGUI_DEFAULT_FONT>(i));
            if (isValidFont(i)) return getExtraFont(static_cast<ExtraFontType>(toExtraFont(i)));
            return nullptr;
        }
        static irr::gui::IGUIFont *getFontDefault(irr::u8 i)
        {
            auto ret = getFont(i);
            if (!ret)  return getFont();
        }
        static void setFont(irr::gui::IGUIFont *f, irr::u8 i = irr::gui::EGDF_DEFAULT) {
            if (isIrrlichtFont(i)) IrrCommonObject::setFont(f, static_cast<irr::gui::EGUI_DEFAULT_FONT>(i));
            if (isValidFont(i))  setExtraFont(static_cast<ExtraFontType>(toExtraFont(i)), f);
        }
        static bool setTTF(const irr::io::path& fname, const irr::u32 size, irr::u8 i = irr::gui::EGDF_DEFAULT)
        {
            auto font = irr::gui::CGUITTFont::createTTFont(getDevice(), fname, size);
            if (font)
            {
                setFont(font, i);
                return true;
            } else return false;
        }
    };
}
