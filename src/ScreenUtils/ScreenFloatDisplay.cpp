
#include <Utils/FloatFormatString.h>

#include "ScreenFloatDisplay.h"

using namespace irr;
using namespace IOSP;

void IOSP::SimpleFloatDisplay::setFormat(unsigned char total, unsigned char frac, const char *caption)
{
    char ffs[64];
    generateFloatFormatString(ffs, total, frac);
    char vfs[m_maxLen];
    if (caption)
        snprintf(vfs, m_maxLen, "%s: %s", caption, ffs);
    else
        snprintf(vfs, m_maxLen, "%s", ffs);
    m_format = vfs;
    ScreenFormattedText::setFormat(m_format.c_str());
}

void IOSP::SimpleFloat3Display::setFormat(unsigned char total, unsigned char frac, const char *caption)
{
    char ffs[64];
    generateFloatFormatString(ffs, total, frac);
    char vfs[m_maxLen];
    if (caption)
        snprintf(vfs, m_maxLen, "%s: [%s, %s, %s]", caption, ffs, ffs, ffs);
    else
        snprintf(vfs, m_maxLen, "[%s, %s, %s]", ffs, ffs, ffs);
    m_format = vfs;
    ScreenFormattedText::setFormat(m_format.c_str());
}
