
#include <cassert>
#include <cstdio>
#include <Utils/XMLParser.h>
#include <Utils/XMLNodeWriter.h>
#include <Utils/IsAlive.h>
#include "Settings.h"

using namespace IOSP;
using namespace irr;

class SettingsXMLParser : public XMLParser
{
    NodeHandler m_rootHandler, m_fontsHandler, m_fontHandler;
    Settings &m_settings;
    int m_fontCategory{0};
    const wchar_t *m_fontFile{nullptr};
    unsigned int m_fontSize{10};
public:
    void fontAttrEnd()
    {
        core::stringw val(m_fontFile ? m_fontFile : L"");
        if (!val.empty())
        {
            printf(
                "Adding font to config: [%ls (%i)]: { %ls, %i }\n",
                CommonObject::getFontName(m_fontCategory).c_str(), m_fontCategory,
                val.c_str(), m_fontSize);
            m_settings.setFont(val, m_fontSize, m_fontCategory);
        }
        m_fontFile = nullptr;
        m_fontSize = 10;
    }
    void fontAttr(const wchar_t *attr, Variant v)
    {
//         std::printf("Processing attribute: %ls\n", attr);
        if (Settings::FontCategoryAttr == attr)
        {
            m_fontCategory = CommonObject::getFontType(v.wChar);
            return;
        }
        if (Settings::FontFileAttr == attr)
        {
            m_fontFile = v.wChar;
            return;
        }
        if (Settings::FontSizeAttr == attr)
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
        m_rootHandler.m_nodeHandlers.insert(Settings::FontsNodeName, &m_fontsHandler);
        m_fontsHandler.m_nodeHandlers.insert(Settings::FontNodeName, &m_fontHandler);
        m_fontHandler.m_attrHandler = (NodeHandler::AttrHandler_t)&SettingsXMLParser::fontAttr;
        m_fontHandler.m_attrEndHandler = (NodeHandler::AttrEndHandler_t)&SettingsXMLParser::fontAttrEnd;
    }
};

// static void writeFont(const irr::core::stringw&)
// {
// }

const irr::core::stringw IOSP::Settings::FontsNodeName = L"fonts";
const irr::core::stringw IOSP::Settings::FontNodeName = L"font";
const irr::core::stringw IOSP::Settings::FontCategoryAttr = L"category";
const irr::core::stringw IOSP::Settings::FontFileAttr = L"file";
const irr::core::stringw IOSP::Settings::FontSizeAttr = L"size";

void IOSP::Settings::setFont(const irr::core::stringw& file, unsigned int size, int i)
{
    if (!isValidFont(i))  return;
    Settings::Font font(file, size);
    m_fonts.set(i, font);
    setDirty(true);
}

IOSP::Settings::Font IOSP::Settings::getFont(int i) const
{
    auto *node = m_fonts.find(i);
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
        printf("Font: [%ls]: { %ls, %i }\n", getFontName(c).c_str(), f.file.c_str(), f.size);
        it++;
    }
}

bool IOSP::Settings::load(const irr::io::path& arg)
{
    IsAlive loading(m_loading);
    assert(isLoading());
    irr::io::path fpath = arg.empty() ? m_fpath : arg;
    auto *reader = getFileSystem()->createXMLReader(fpath);
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
    auto *writer = getFileSystem()->createXMLWriter(fpath);
    if (!writer)
    {
        std::printf("Unable to save config file: \"%s\"\n", fpath.c_str());
        return false;
    }
    std::printf("Saving to config file: \"%s\"\n", fpath.c_str());
    writer->writeXMLHeader();
    {
        XMLNodeWriter fontsW(writer, FontsNodeName, 0);
//         fontsW.write();
        auto it = m_fonts.getConstIterator();
        while(!it.atEnd())
        {
            XMLNodeWriter fontW(writer, FontNodeName, true);
            Font font = it->getValue();
            std::printf("Saving font: { %ls, %ls, %i }\n", getFontName(it->getKey()).c_str(), font.file.c_str(), font.size);
            fontW.addAttribute(FontCategoryAttr, getFontName(it->getKey()));
            fontW.addAttribute(FontFileAttr, font.file);
            fontW.addAttribute(FontSizeAttr, (int)font.size);
            it++;
        }
    }
    setDirty(false);
    return true;
}
