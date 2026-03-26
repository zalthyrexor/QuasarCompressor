#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class QuasarCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    QuasarCompressorAudioProcessorEditor (QuasarCompressorAudioProcessor&);
    ~QuasarCompressorAudioProcessorEditor() override;
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    QuasarCompressorAudioProcessor& audioProcessor;
};
