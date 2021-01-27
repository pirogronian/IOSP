
#pragma once

namespace IOSP
{
    class IsAlive
    {
        bool & m_extChecker;
    public:
        IsAlive(bool &checker) : m_extChecker{checker} { m_extChecker = true; }
        ~IsAlive() { m_extChecker = false; }
    };
}
