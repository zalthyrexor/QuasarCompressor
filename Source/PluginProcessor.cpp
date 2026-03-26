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
                       )
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
void QuasarCompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
    }
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
