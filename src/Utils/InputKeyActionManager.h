
#pragma once

#include <irrlicht.h>
#include <Utils/InputKeyBinder.h>

namespace IOSP
{
    class AbstractInputKeyActionManager : public InputKeyBinder, public irr::IEventReceiver
    {
    public:
        virtual bool OnKeyInput(const irr::SEvent::SKeyInput&) = 0;
        bool OnEvent(const irr::SEvent& event) override
        {
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                return OnKeyInput(event.KeyInput);
            return false;
        }
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

    class SimpleInputKeyTriggeredActionManager : public AbstractInputKeyTriggeredActionManager
    {
        std::vector<bool> m_triggered{0, false};
    public:
        void triggered(int) override;
        bool isTriggered(int) const;
        void reset(int = -1);
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
