
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
        int m_attrNum{-1};
        irr::core::array<irr::core::stringw> m_attrNames;
        irr::core::array<irr::core::stringw> m_attrVals;
    public:
        XMLNodeWriter(irr::io::IXMLWriter *xml, const irr::core::stringw& name, bool empty = false, int attrNum = -1)
        : m_xml{xml}, m_nodeName{name}, m_empty(empty), m_attrNum{attrNum}
        {
            if (m_attrNum == 0) write();
        }
        XMLNodeWriter(irr::io::IXMLWriter *xml, const irr::core::stringw& name, int attrNum, bool empty = false)
        : m_xml{xml}, m_nodeName{name}, m_attrNum{attrNum}, m_empty{empty}
        {
            if (m_attrNum == 0) write();
        }
        ~XMLNodeWriter();
        bool isWritten() const { return m_written; }
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
