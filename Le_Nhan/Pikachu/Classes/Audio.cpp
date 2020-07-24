#include "Audio.h"
#include "AudioEngine.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;

using namespace experimental;
using namespace cocos2d;

int Audio::backgroundMusic = -1;
float Audio::backgroundVolume = 1.0f;
float Audio::effectVolume = 1.0f;

void Audio::playBackgroundMusic()
{
	//backgroundMusic = AudioEngine::play2d("removePokemonSoundEffect.mp3", true, backgroundVolume);
}

void Audio::stopBackgroundMusic()
{
	AudioEngine::stop(backgroundMusic);
}

void Audio::setBackgroundVolume(float volume)
{
	backgroundVolume = volume;
	AudioEngine::setVolume(backgroundMusic, volume);
}

void Audio::playSelectPokemonSoundEffect()
{
	AudioEngine::play2d("removePokemonSoundEffect.mp3", false, effectVolume);
}

void Audio::playRemovePokemonSoundEffeect()
{
	AudioEngine::play2d("removePokemonSoundEffect.mp3", false, effectVolume);
}

void Audio::setEffectVolume(float volume)
{
	effectVolume = volume;
}