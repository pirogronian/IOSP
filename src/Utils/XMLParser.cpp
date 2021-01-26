
#include <cstdio>

#include "XMLParser.h"

using namespace IOSP;

IOSP::XMLParser::~XMLParser()
{
    m_xml->drop();
}

void print(const IOSP::XMLParser::NodeHandler::NodeHandlers_t &hmap)
{
    printf("Child node handler count: %i\n", hmap.size());
    auto it = hmap.getConstIterator();
    while(!it.atEnd())
    {
        printf("Handler for node: \"%ls\"\n", it->getKey().c_str());
        printf("Handler accessible: %i\n", hmap.find(it->getKey()) != nullptr);
        it++;
    }
}

bool IOSP::XMLParser::parse(const NodeHandler *nodeHandler)
{
//     std::puts("Entering new parse loop...");
//     print(nodeHandler->m_nodeHandlers);
    while(m_xml->read())
    {
        switch(m_xml->getNodeType())
        {
            case irr::io::EXN_NONE:
//                 std::puts("None node type? Why?");
                break;
            case irr::io::EXN_UNKNOWN:
//                 std::puts("Unknown node type. Well?");
                break;
            case irr::io::EXN_CDATA:
                if (nodeHandler->m_cdataHandler)  (this->*nodeHandler->m_cdataHandler)(m_xml->getNodeData());
                break;
            case irr::io::EXN_TEXT:
                if (nodeHandler->m_textHandler)  (this->*nodeHandler->m_textHandler)(m_xml->getNodeData());
                break;
            case irr::io::EXN_COMMENT:
                if (nodeHandler->m_commentHandler)  (this->*nodeHandler->m_commentHandler)(m_xml->getNodeData());
                break;
            case irr::io::EXN_ELEMENT:
            {
//                 std::printf("Found node with name: %ls\n", m_xml->getNodeName());
//                 print(nodeHandler->m_nodeHandlers);
                auto *node = nodeHandler->m_nodeHandlers.find(m_xml->getNodeName());
                if (node)
                {
                    auto *childHandler = node->getValue();
                    if (childHandler->m_attrHandler)
                    {
                        int i = m_xml->getAttributeCount() - 1;
//                         std::printf("Attribute count: %i\n", i + 1);
                        while(i >= 0)
                        {
                            Variant v;
                            v.Float = m_xml->getAttributeValueAsFloat(i);
                            v.Int = m_xml->getAttributeValueAsInt(i);
                            v.wChar = m_xml->getAttributeValue(i);
                            (this->*childHandler->m_attrHandler)(m_xml->getAttributeName(i), v);
                            --i;
                        }
                        if (childHandler->m_attrEndHandler) (this->*childHandler->m_attrEndHandler)();
//                         else std::puts("No end attributes handler!");
                    } // else std::puts("No defined child attribute handler!");
                    if (!m_xml->isEmptyElement())
                        parse(childHandler);
                } // else std::printf("No node handler for node <\"%ls\">\n", m_xml->getNodeName());
                break;
            }
            case irr::io::EXN_ELEMENT_END:
//                 std::printf("Found end of the node with name: %ls\n", m_xml->getNodeName());
                return true;
            default:
                std::puts("Unknown node type. Event for Irrlicht!");
                return false;
        }
    }

    return true;
}
