
#include <cstdio>

#include "XMLNodeWriter.h"

using namespace IOSP;
using namespace irr;

IOSP::XMLNodeWriter::~XMLNodeWriter()
{
    if (!m_written)
        write();
    if (!m_empty)
    {
        m_xml->writeClosingTag(m_nodeName.c_str());
        m_xml->writeLineBreak();
    }
}

void IOSP::XMLNodeWriter::write()
{
    if (m_written)
    {
        std::printf("Node <%ls> already written!\n", m_nodeName.c_str());
        return;
    }
    m_xml->writeElement(m_nodeName.c_str(), m_empty, m_attrNames, m_attrVals);
    m_xml->writeLineBreak();
    m_written = true;
}

void IOSP::XMLNodeWriter::addAttribute(const irr::core::stringw& name, const irr::core::stringw& val)
{
    if (m_written)
    {
        std::printf("Cannot add attribute: node <%ls> already written!\n", m_nodeName.c_str());
        return;
    }
    m_attrNames.push_back(name);
    m_attrVals.push_back(val);
    m_attrNum++;
    if (m_attrNum > 0 && m_attrNum == m_attrNames.size())  write();
}
