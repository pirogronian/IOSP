
#pragma once

#include <irrlicht.h>
#include <Utils/Variant.h>

namespace IOSP
{
    class XMLParser
    {
    public:
        struct NodeHandler
        {
            typedef void (XMLParser::*CommonHandler_t)(const wchar_t *);
            typedef void (XMLParser::*AttrHandler_t)(const wchar_t *, Variant);
            typedef void (XMLParser::*AttrEndHandler_t)();
            typedef irr::core::map<irr::core::stringw, NodeHandler*> NodeHandlers_t;
            CommonHandler_t m_textHandler {nullptr};
            CommonHandler_t m_cdataHandler {nullptr};
            CommonHandler_t m_commentHandler {nullptr};
            AttrHandler_t m_attrHandler {nullptr};
            AttrEndHandler_t m_attrEndHandler {nullptr};
            NodeHandlers_t m_nodeHandlers;
        };
    protected:
        irr::io::IXMLReader *m_xml{nullptr};
        NodeHandler *m_rootNodeHandler{nullptr};
        bool parse(const NodeHandler *);
    public:
        XMLParser(irr::io::IXMLReader *xml, NodeHandler *rootHandler) : 
            m_xml(xml), m_rootNodeHandler(rootHandler) {}
        ~XMLParser();
        bool parse()
        {
            return parse(m_rootNodeHandler);
        }
    };
}
