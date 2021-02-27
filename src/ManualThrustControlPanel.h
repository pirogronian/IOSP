
#pragma once

#include <LinearThruster.h>
#include <ControlPanelSceneNode.h>
// #include <Gui.h>

namespace IOSP
{
    class ManualThrustControlPanel : public ControlPanelSceneNode
    {
    protected:
        std::vector<int> m_lths;
        irr::gui::IGUIWindow *m_window{nullptr};
        irr::gui::IGUIListBox *m_ltListbox{nullptr};
    public:
        enum GuiIds
        {
            LinearThrusterListBox
        };
        ManualThrustControlPanel(
            irr::scene::ISceneNode *parent,
            irr::scene::ISceneManager *smgr,
            irr::s32 id = -1,
            const irr::core::vector3df& pos = irr::core::vector3df(0, 0, 0),
            const irr::core::vector3df& rot = irr::core::vector3df(0, 0, 0));
        void render() override {}
        void update() override {}
        void drawUI() override {}
        void scanForLinearThrusters();
    };
}
