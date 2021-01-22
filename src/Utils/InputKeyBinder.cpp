
#include <Utils/VectorHelper.h>
#include "InputKeyBinder.h"

int IOSP::InputKeyBinder::actionKey(int action) const
{
    if (!isIndexValid(m_actionKeys, action))  return 0;
    return m_actionKeys[action];
}

bool IOSP::InputKeyBinder::actionShift(int action) const
{
    if (!isIndexValid(m_actionShift, action))  return false;
    return m_actionShift[action];
}

bool IOSP::InputKeyBinder::actionCtrl(int action) const
{
    if (!isIndexValid(m_actionCtrl, action))  return false;
    return m_actionCtrl[action];
}

int IOSP::InputKeyBinder::boundAction(int key, bool shift, bool ctrl) const
{
    auto itv = m_keyActions.find(key);
    if (itv == m_keyActions.end())  return 0;
    return itv->second.access(shift, ctrl);
}

void IOSP::InputKeyBinder::bind(int action, int key, bool shift, bool ctrl)
{
    IOSP::ensureSize(m_actionKeys, action, 0);
    m_actionKeys.at(action) = key;
    IOSP::ensureSize(m_actionShift, action, false);
    m_actionShift.at(action) = shift;
    IOSP::ensureSize(m_actionCtrl, action, false);
    m_actionCtrl.at(action) = ctrl;
    auto& kv = m_keyActions[key];
    kv.access(shift, ctrl) = action;
}

void IOSP::InputKeyBinder::unbindKey(int key, bool shift, bool ctrl)
{
    auto itv = m_keyActions.find(key);
    if (itv == m_keyActions.end())  return;
    int action = itv->second.access(shift, ctrl);
    itv->second.access(shift, ctrl) = 0;
    if (m_actionKeys.size() > action)
        m_actionKeys.at(action) = 0;
    if (m_actionShift.size() > action)
        m_actionShift.at(action) = 0;
    if (m_actionCtrl.size() > action)
        m_actionCtrl.at(action) = 0;
}

void IOSP::InputKeyBinder::unbindAction(int action)
{
    int key = actionKey(action);
    bool shift = actionShift(action);
    bool ctrl = actionCtrl(action);
    if (isIndexValid(m_actionKeys, action)) m_actionKeys[action] = 0;
    if (isIndexValid(m_actionShift, action)) m_actionShift[action] = false;
    if (isIndexValid(m_actionCtrl, action)) m_actionCtrl[action] = false;
    auto itv = m_keyActions.find(key);
    if (itv == m_keyActions.end())  return;
    itv->second.access(shift, ctrl) = 0;
    if (itv->second.count() == 0)  m_keyActions.erase(itv);
}
