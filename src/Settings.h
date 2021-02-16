
#pragma once

#include <irrlicht.h>
#include <Utils/IrrCommonObject.h>
#include <Utils/Variant.h>

namespace IOSP
{
    class Settings : public IrrCommonObject
    {
    public:
        struct Font
        {
            irr::core::stringw file;
            unsigned int size{0};
            Font() = default;
            Font(const irr::core::stringw& f, unsigned int s) : file(f), size(s) {}
        };
        static const irr::core::stringw FontsNodeName;
        static const irr::core::stringw FontNodeName;
        static const irr::core::stringw FontCategoryAttr;
        static const irr::core::stringw FontFileAttr;
        static const irr::core::stringw FontSizeAttr;
    protected:
        bool m_dirty{false};
        bool m_loading{false};
        irr::io::path m_fpath;
        irr::core::map<irr::core::stringw, Font> m_fonts;
    public:
        Settings(const irr::io::path& fpath = "") : m_fpath(fpath) {}
        bool isLoading() const { return m_loading; }
        void setLoading(bool t) { m_loading = t; }
        bool isDirty() const { return m_dirty; }
        void setDirty(bool t, bool f = false)
        {
            if (!isLoading() || f)
                m_dirty = t;
        }
        bool load(const irr::io::path& fpath = "");
        bool save(const irr::io::path& fpath = "");
        irr::io::path& path() { return m_fpath; }
        const irr::io::path& path() const { return m_fpath; }
        void setFont(const irr::core::stringw&, const irr::core::stringw&, unsigned int);
        Font getFont(const irr::core::stringw& = irr::core::stringw()) const;
        void printFonts() const;
    };
}
