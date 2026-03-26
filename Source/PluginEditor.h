#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class QuasarCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    QuasarCompressorAudioProcessorEditor (QuasarCompressorAudioProcessor&);
    ~QuasarCompressorAudioProcessorEditor() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override { repaint(); }
private:
    QuasarCompressorAudioProcessor& audioProcessor;

    juce::Slider thresholdSlider, ratioSlider, pSlider, iSlider, dSlider;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> threshAttach, ratioAttach, pAttach, iAttach, dAttach;
    void setupSlider(juce::Slider& slider, juce::String name);
};
