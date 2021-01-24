
#include <Utils/VectorHelper.h>

#include "InputKeyActionManager.h"

using namespace IOSP;

void IOSP::SimpleInputKeyTriggeredActionManager::triggered(int action)
{
    ensureSize(m_triggered, action);
    m_triggered[action] = true;
}

bool IOSP::SimpleInputKeyTriggeredActionManager::isTriggered(int action) const
{
    if (!isIndexValid(m_triggered, action))  return false;
    return m_triggered[action];
}

void IOSP::SimpleInputKeyTriggeredActionManager::reset(int action)
{
    if (action > 0)
    {
        if (!isIndexValid(m_triggered, action))  return;
        m_triggered[action] = false;
        return;
    }
    for (auto it = m_triggered.begin(); it != m_triggered.end(); it++)
        *it = false;
}

bool IOSP::InputKeyStateActionManager::isActive(int action) const
{
    if (!isIndexValid(m_actionStates, action))  return false;
    return m_actionStates[action];
}

void IOSP::InputKeyStateActionManager::setActive(int action, bool active)
{
    ensureSize(m_actionStates, action);
    m_actionStates[action] = active;
}

bool IOSP::InputKeyStateActionManager::OnKeyInput(const irr::SEvent::SKeyInput& ki)
{
    int action = boundAction(ki);
    if (action <= 0)  return false;
    if (ki.PressedDown)  setActive(action, true);
    else setActive(action, false);
    return true;
}
