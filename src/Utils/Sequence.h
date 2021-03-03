
#pragma once

namespace IOSP
{
    template<typename T, T START = 0>
    class Sequence
    {
    protected:
        T m_value{START};
    public:
        void reset() { m_value = START; }
        T getValue() const { return m_value; }
        T next() { return m_value++; }
        T prev() { return m_value--; }
    };

    typedef Sequence<unsigned int> SimpleSequence;
}
