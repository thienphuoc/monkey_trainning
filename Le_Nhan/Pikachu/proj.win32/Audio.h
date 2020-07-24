#pragma once

class Audio
{
public:
	static int backgroundMusic;
	static float backgroundVolume, effectVolume;
	static void playBackgroundMusic();
	static void stopBackgroundMusic();
	static void setBackgroundVolume(float volume);
	static void playSelectPokemonSoundEffect();
	static void playRemovePokemonSoundEffeect();
	static void setEffectVolume(float volume);
};
