
#include "IrrlichtObject.h"

using namespace IOSP;
using namespace irr;

irr::IrrlichtDevice *IOSP::IrrlichtObject::s_dev{nullptr};

const gui::IGUIFont * IOSP::IrrlichtObject::getFont() const
{
    auto *g = getGui();
    if (!g)  return nullptr;
    return g->getSkin()->getFont();
}

gui::IGUIFont * IOSP::IrrlichtObject::getFont()
{
    auto *g = getGui();
    if (!g)  return nullptr;
    return g->getSkin()->getFont();
}
