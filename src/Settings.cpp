
#include <cassert>
#include <cstdio>
#include <Utils/XMLParser.h>
#include <Utils/IsAlive.h>
#include "Settings.h"

using namespace IOSP;
using namespace irr;

class SettingsXMLParser : public XMLParser
{
    NodeHandler m_rootHandler, m_fontsHandler, m_fontHandler;
    Settings &m_settings;
    const wchar_t *m_fontCategory{nullptr}, *m_fontFile{nullptr};
    unsigned int m_fontSize{10};
    const core::stringw m_fontCatAttrName{"category"};
    const core::stringw m_fontFileAttrName{"file"};
    const core::stringw m_fontSizeAttrName{"size"};
public:
    void fontAttrEnd()
    {
        core::stringw key(m_fontCategory);
        core::stringw val(m_fontFile);
        if (key.empty())  key = L"Default";
        if (!val.empty())
        {
            printf("Adding font to config: [%ls]: { %ls, %i }\n", key.c_str(), val.c_str(), m_fontSize);
            m_settings.setFont(key, val, m_fontSize);
        }
//         else std::puts("Value empty!");
        m_fontCategory = nullptr;
        m_fontFile = nullptr;
        m_fontSize = 10;
    }
    void fontAttr(const wchar_t *attr, Variant v)
    {
//         std::printf("Processing attribute: %ls\n", attr);
        if (m_fontCatAttrName == attr)
        {
            m_fontCategory = v.wChar;
            return;
        }
        if (m_fontFileAttrName == attr)
        {
            m_fontFile = v.wChar;
            return;
        }
        if (m_fontSizeAttrName == attr)
        {
            m_fontSize = v.Int;
            return;
        }
//         std::printf("Unknown font attribute: %ls\n", attr);
    }
    SettingsXMLParser(Settings &settings, irr::io::IXMLReader *xml)
        : m_settings{settings},
        XMLParser(xml, &m_rootHandler)
    {
        m_rootHandler.m_nodeHandlers.insert(L"fonts", &m_fontsHandler);
        m_fontsHandler.m_nodeHandlers.insert(L"font", &m_fontHandler);
        m_fontHandler.m_attrHandler = (NodeHandler::AttrHandler_t)&SettingsXMLParser::fontAttr;
        m_fontHandler.m_attrEndHandler = (NodeHandler::AttrEndHandler_t)&SettingsXMLParser::fontAttrEnd;
    }
};

void IOSP::Settings::setFont(const irr::core::stringw& cat, const irr::core::stringw& file, unsigned int size)
{
    Settings::Font font(file, size);
    auto *node = m_fonts.find(cat);
    if (node)  node->setValue(font);
    else m_fonts.insert(cat, font);
    setDirty(true);
}

IOSP::Settings::Font IOSP::Settings::getFont(const irr::core::stringw& arg) const
{
    irr::core::stringw cat = arg;
    if (cat.empty())  cat = L"Default";
    auto *node = m_fonts.find(cat);
    if (!node)  return IOSP::Settings::Font();
    return node->getValue();
}

void IOSP::Settings::printFonts() const
{
    printf("Loaded fonts: %i\n", m_fonts.size());
    auto it = m_fonts.getConstIterator();
    while(!it.atEnd())
    {
        auto f = it->getValue();
        auto c = it->getKey();
        printf("Font: [%ls]: { %ls, %i }\n", c.c_str(), f.file.c_str(), f.size);
        it++;
    }
}

bool IOSP::Settings::load(const irr::io::path& arg)
{
    IsAlive loading(m_loading);
    assert(isLoading());
    irr::io::path fpath = arg.empty() ? m_fpath : arg;
    auto *reader = m_fs->createXMLReader(fpath);
    if (!reader)
    {
        std::printf("Unable to load config file: \"%s\"\n", fpath.c_str());
        return false;
    }
    SettingsXMLParser parser(*this, reader);
    return parser.parse();
}

bool IOSP::Settings::save(const irr::io::path& arg)
{
    if (!isDirty())  return true;
    irr::io::path fpath = arg.empty() ? m_fpath : arg;
    auto *writer = m_fs->createXMLWriter(fpath);
    if (!writer)
    {
        std::printf("Unable to save config file: \"%s\"\n", fpath.c_str());
        return false;
    }
    std::printf("Saving to config file: \"%s\"\n", fpath.c_str());
    writer->writeXMLHeader();
    writer->writeLineBreak();
    writer->writeElement(L"fonts");
    writer->writeLineBreak();
    auto it = m_fonts.getConstIterator();
    while(!it.atEnd())
    {
        Font font = it->getValue();
        irr::core::stringw sizestr(font.size);
        writer->writeElement(L"font", true, L"category", it->getKey().c_str(), L"file", font.file.c_str(), L"size", sizestr.c_str());
        writer->writeLineBreak();
        it++;
    }
    writer->writeClosingTag(L"fonts");
    writer->writeLineBreak();
    irr::core::stringw fontSizeStr();
    setDirty(false);
    return true;
}
