#include "PluginProcessor.h"
#include "PluginEditor.h"

QuasarCompressorAudioProcessorEditor::QuasarCompressorAudioProcessorEditor(QuasarCompressorAudioProcessor& p) : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 300);
}
QuasarCompressorAudioProcessorEditor::~QuasarCompressorAudioProcessorEditor()
{
}
void QuasarCompressorAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}
void QuasarCompressorAudioProcessorEditor::resized()
{
}
