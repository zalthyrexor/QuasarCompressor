#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

namespace zlth::dsp::compressor
{
    class Compressor
    {
    public:
        Compressor() = default;
        ~Compressor() = default;
        void prepare(double sampleRate)
        {
        }
        void setParameters(float thresholdDb, float ratio, float attackMs, float releaseMs)
        {
        }
        float processSample(float input)
        {
            return input;
        }
        float getGainReduction() const { return 1; }
    private:
    };
}
