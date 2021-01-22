
#pragma once

#include <Utils/InputKeyBinder.h>

namespace IOSP
{
    class AbstractInputKeyActionManager : public InputKeyBinder
    {
    public:
        virtual bool OnKeyInput(const irr::SEvent::SKeyInput&) = 0;
    };

    class AbstractInputKeyTriggeredActionManager : public AbstractInputKeyActionManager
    {
    public:
        virtual void triggered(int) = 0;
        bool OnKeyInput(const irr::SEvent::SKeyInput& ki) override
        {
            if (!ki.PressedDown)  return false;
            int action = boundAction(ki);
            if (action > 0)  triggered(action);
            return true;
        }
    };

    class InputKeyStateActionManager : public AbstractInputKeyActionManager
    {
    protected:
        std::vector<bool> m_actionStates{0, false};
    public:
        bool isActive(int) const;
        void setActive(int, bool);
        bool OnKeyInput(const irr::SEvent::SKeyInput&) override;
    };
}
