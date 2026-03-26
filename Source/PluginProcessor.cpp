#include "PluginProcessor.h"
#include "PluginEditor.h"

QuasarCompressorAudioProcessor::QuasarCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameterLayout())
#endif
{
}
QuasarCompressorAudioProcessor::~QuasarCompressorAudioProcessor()
{
}
const juce::String QuasarCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
bool QuasarCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}
bool QuasarCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}
bool QuasarCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
double QuasarCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
int QuasarCompressorAudioProcessor::getNumPrograms()
{
    return 1;
}
int QuasarCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}
void QuasarCompressorAudioProcessor::setCurrentProgram (int index)
{
}
const juce::String QuasarCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}
void QuasarCompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}
void QuasarCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    auto totalNumInputChannels = getTotalNumInputChannels();
    compressors.resize(totalNumInputChannels);
    for (auto& comp : compressors)
    {
        comp.prepare(sampleRate);
        comp.setParameters(-30.0f, 2.0, 1.0f, 1.0f);
    }
}
void QuasarCompressorAudioProcessor::releaseResources()
{
}
#ifndef JucePlugin_PreferredChannelConfigurations
bool QuasarCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}
#endif
void QuasarCompressorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    float thresh = apvts.getRawParameterValue("threshold")->load();
    float ratio = apvts.getRawParameterValue("ratio")->load();
    float p = apvts.getRawParameterValue("pGain")->load();
    float i = apvts.getRawParameterValue("iGain")->load();
    float d = apvts.getRawParameterValue("dGain")->load();

    for (auto& comp : compressors) {
        comp.setParameters(thresh, ratio, p, i);
    }

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    float minGain = 1.0f;
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        auto& comp = compressors[channel];
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = comp.processSample(channelData[sample]);
            minGain = comp.getGainReduction();
        }
    }
    latestGR.store(minGain);
}
bool QuasarCompressorAudioProcessor::hasEditor() const
{
    return true;
}
juce::AudioProcessorEditor* QuasarCompressorAudioProcessor::createEditor()
{
    return new QuasarCompressorAudioProcessorEditor (*this);
}
void QuasarCompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}
void QuasarCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new QuasarCompressorAudioProcessor();
}
juce::AudioProcessorValueTreeState::ParameterLayout QuasarCompressorAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>("threshold", "Threshold", -60.0f, 0.0f, -30.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("ratio", "Ratio", 1.0f, 20.0f, 2.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("pGain", "P Gain", 0.0f, 2000.0f, 500.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("iGain", "I Gain", 0.0f, 10.0f, 0.1f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("dGain", "D Gain", 0.0f, 200.0f, 40.0f));
    return layout;
}