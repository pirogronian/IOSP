
#pragma once

#include <irrlicht.h>

namespace IOSP
{
    class XMLNodeWriter
    {
    protected:
        irr::io::IXMLWriter *m_xml{nullptr};
        const irr::core::stringw m_nodeName;
        bool m_empty{false}, m_written{false};
        irr::core::array<irr::core::stringw> m_attrNames;
        irr::core::array<irr::core::stringw> m_attrVals;
    public:
        XMLNodeWriter(irr::io::IXMLWriter *xml, const irr::core::stringw& name, bool empty = false)
        : m_xml{xml}, m_nodeName{name}, m_empty(empty) {}
        ~XMLNodeWriter();
        void write();
        void addAttribute(const irr::core::stringw&, const irr::core::stringw&);
        void addAttribute(const irr::core::stringw& name, int val)
        {
            addAttribute(name, irr::core::stringw(val));
        }
        void addAttribute(const irr::core::stringw& name, float val)
        {
            addAttribute(name, irr::core::stringw(val));
        }
    };
}
