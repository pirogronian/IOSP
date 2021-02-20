
#pragma once

#include <irrlicht.h>
#include <Utils/CommonObject.h>
#include <Utils/Variant.h>

namespace IOSP
{
    class Settings : public CommonObject
    {
    public:
        static const irr::core::stringw FontsNodeName;
        static const irr::core::stringw FontNodeName;
        static const irr::core::stringw FontCategoryAttr;
        static const irr::core::stringw FontFileAttr;
        static const irr::core::stringw FontSizeAttr;
    protected:
        bool m_dirty{false};
        bool m_loading{false};
        irr::io::path m_fpath;
        irr::core::map<int, TTF> m_fonts;
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
        void setTTF(const irr::core::stringw&, unsigned int, int = 0);
        TTF getTTF(int i = 0) const;
        void printFonts() const;
    };
}
