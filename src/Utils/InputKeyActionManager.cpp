
#include <Utils/VectorHelper.h>

#include "InputKeyActionManager.h"

using namespace IOSP;

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

void IOSP::InputKeyStateActionManager::OnKeyInput(const irr::SEvent::SKeyInput& ki)
{
    int action = boundAction(ki);
    if (action <= 0)  return;
    if (ki.PressedDown)  setActive(action, true);
    else setActive(action, false);
}
