/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AudioManager.h"
#include "AudioEngine.h"

int AudioManager::backgroundMusic = -1;

float AudioManager::backgroundVolume = 1.0f;

float AudioManager::effectVolume = 1.0f;

void AudioManager::playBackgroundMusic()
{
    backgroundMusic = cocos2d::experimental::AudioEngine::play2d("Resources/backgroundMusic.mp3", true, backgroundVolume);
}

void AudioManager::stopBackgroundMusic()
{
    cocos2d::experimental::AudioEngine::stop(backgroundMusic);
}

void AudioManager::setBackgroundVolume(float volume)
{
    backgroundVolume = volume;
    cocos2d::experimental::AudioEngine::setVolume(backgroundMusic, volume);
}

void AudioManager::playSelectPokemonSoundEffect()
{
    cocos2d::experimental::AudioEngine::play2d("Resources/selectPokemonSoundEffect.mp3", false, effectVolume);
}

void AudioManager::playRemovePokemonSoundEffect()
{
    cocos2d::experimental::AudioEngine::play2d("Resources/removePokemonSoundEffect.mp3", false, effectVolume);
}

void AudioManager::setEffectVolume(float volume)
{
    effectVolume = volume;
}
