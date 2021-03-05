
#pragma once

namespace IOSP
{
    class SimpleState
    {
    protected:
        int m_cnt{0};
    public:
        void modify() { m_cnt++; }
        int getCounter() const { return m_cnt; }
        bool isSync(const SimpleState& other) const { return m_cnt == other.getCounter(); }
        bool trySync(const SimpleState&);
    };
}
