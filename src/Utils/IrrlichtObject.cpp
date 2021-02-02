
#include "IrrlichtObject.h"

using namespace IOSP;
using namespace irr;

irr::IrrlichtDevice *IOSP::IrrlichtObject::s_dev{nullptr};

const gui::IGUIFont * IOSP::IrrlichtObject::getFont(irr::gui::EGUI_DEFAULT_FONT f) const
{
    auto *g = getGui();
    if (!g)  return nullptr;
    return g->getSkin()->getFont(f);
}

gui::IGUIFont * IOSP::IrrlichtObject::getFont(irr::gui::EGUI_DEFAULT_FONT f)
{
    auto *g = getGui();
    if (!g)  return nullptr;
    return g->getSkin()->getFont(f);
}
