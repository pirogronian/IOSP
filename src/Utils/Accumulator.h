
#pragma once

namespace MOSP
{
    namespace Utils
    {
        template <typename T>
        class Accumulator
        {
        protected:
            T m_accumulatedDelta{0};
            T m_referenceDelta{0};
        public:
            Accumulator(T rd = 0) { m_referenceDelta = rd; }
            T accumulatedDelta() const { return m_accumulatedDelta; }
            T referenceDelta() const { return m_referenceDelta; }
            T& referenceDelta() { return m_referenceDelta; }
            T left() const { return m_referenceDelta - m_accumulatedDelta; }
            T appendDelta(T d) {
                m_accumulatedDelta += d;
                return left();
            }
            void reset() { m_accumulatedDelta = 0; }
        };

        typedef Accumulator<double> StandardAccumulator;
//         typedef TriggeringAccumulator<double> StandardTriggeringAccumulator;
    }
}
