
#include "SimpleState.h"

using namespace IOSP;

bool SimpleState::trySync(const SimpleState& other)
{
    if (isSync(other))  return false;
    m_cnt = other.getCounter();
    return true;
}
