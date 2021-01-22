
#pragma once

#include <vector>
#include <unordered_map>
#include <irrlicht.h>

namespace IOSP
{
    class InputKeyBinder
    {
    public:
        struct KeyActionVariant
        {
            int m_basic{0};
            int m_shift{0};
            int m_ctrl{0};
            int m_shift_ctrl{0};
            int& access(bool shift = false, bool ctrl = false)
            {
                if (!shift && !ctrl)  return m_basic;
                if (shift && !ctrl)  return m_shift;
                if (!shift && ctrl)  return m_ctrl;
                return m_shift_ctrl;
            }
            const int& access(bool shift = false, bool ctrl = false) const
            {
                if (!shift && !ctrl)  return m_basic;
                if (shift && !ctrl)  return m_shift;
                if (!shift && ctrl)  return m_ctrl;
                return m_shift_ctrl;
            }
            std::size_t count() const
            {
                std::size_t c = 0;
                if (m_basic > 0) ++c;
                if (m_shift > 0) ++c;
                if (m_ctrl > 0) ++c;
                if (m_shift_ctrl > 0) ++c;
                return c;
            }
        };
    protected:
        std::vector<int> m_actionKeys{0, 0};
        std::vector<bool> m_actionShift{0, false};
        std::vector<bool> m_actionCtrl{0, false};
        std::unordered_map<int, KeyActionVariant> m_keyActions;
    public:
        int actionKey(int) const;
        bool actionShift(int) const;
        bool actionCtrl(int) const;
        int boundAction(int key, bool shift = false, bool ctrl = false) const;
        int boundAction(const irr::SEvent::SKeyInput& ke) const
        {
            return boundAction(ke.Key, ke.Shift, ke.Control);
        }
        void bind(int action, int key, bool shift = false, bool ctrl = false);
        void unbindKey(int key, bool shift = false, bool ctrl = false);
        void unbindAction(int action);
    };
}
