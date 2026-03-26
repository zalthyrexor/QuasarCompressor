#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <numbers>

QuasarCompressorAudioProcessorEditor::QuasarCompressorAudioProcessorEditor(QuasarCompressorAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setupSlider(thresholdSlider, "Thresh");
    setupSlider(ratioSlider, "Ratio");
    setupSlider(pSlider, "P");
    setupSlider(iSlider, "I");
    setupSlider(dSlider, "D");
    threshAttach = std::make_unique<Attachment>(audioProcessor.apvts, "threshold", thresholdSlider);
    ratioAttach = std::make_unique<Attachment>(audioProcessor.apvts, "ratio", ratioSlider);
    pAttach = std::make_unique<Attachment>(audioProcessor.apvts, "pGain", pSlider);
    iAttach = std::make_unique<Attachment>(audioProcessor.apvts, "iGain", iSlider);
    dAttach = std::make_unique<Attachment>(audioProcessor.apvts, "dGain", dSlider);

    setSize(500, 400);
    startTimerHz(60);
}
QuasarCompressorAudioProcessorEditor::~QuasarCompressorAudioProcessorEditor()
{
}
void QuasarCompressorAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    float gr = audioProcessor.getLatestGR();
    auto area = getLocalBounds().reduced(50);
    auto center = area.getCentre().toFloat();
    float radius = area.getWidth() * 0.3f;
    float angle = juce::jmap(gr, 0.0f, 1.0f, 45.0f * std::numbers::pi_v < float > / 180.0f, 135.0f * std::numbers::pi_v < float > / 180.0f);
    g.setColour(juce::Colours::white);
    auto needleEnd = center.getPointOnCircumference(radius, angle - juce::MathConstants<float>::halfPi);
    g.drawLine(center.x, center.y, needleEnd.getX(), needleEnd.getY(), 2.0f);
    g.drawText("Gain Reduction", area.withY(area.getBottom() - 20).withHeight(20), juce::Justification::centred);
}
void QuasarCompressorAudioProcessorEditor::setupSlider(juce::Slider& slider, juce::String name)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(slider);
}
void QuasarCompressorAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto sliderZone = area.removeFromBottom(100);
    int width = sliderZone.getWidth() / 5;

    thresholdSlider.setBounds(sliderZone.removeFromLeft(width));
    ratioSlider.setBounds(sliderZone.removeFromLeft(width));
    pSlider.setBounds(sliderZone.removeFromLeft(width));
    iSlider.setBounds(sliderZone.removeFromLeft(width));
    dSlider.setBounds(sliderZone.removeFromLeft(width));
}