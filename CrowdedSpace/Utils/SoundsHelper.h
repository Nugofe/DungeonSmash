#pragma once

#include <dsound.h>
#include <map>

class SoundsHelper
{
public:
	static SoundsHelper& GetInstance();

	bool LoadWaveFile(const char* filename);
	bool PlaySound(const char* filename, int volume, DWORD flags = 0);
	bool StopSound(const char* filename);
	bool IsSoundPlaying(const char* filename);
	void SetSoundVolume(const char* filename, int volume);

private:
	struct WaveHeaderType
	{
		char			m_chunkId[4];
		unsigned long	m_chunkSize;
		char			m_format[4];
		char			m_subChunkId[4];
		unsigned long	m_subChunkSize;
		unsigned short	m_audioFormat;
		unsigned short	m_numChannels;
		unsigned long	m_sampleRate;
		unsigned long	m_bytesPerSecond;
		unsigned short	m_blockAlign;
		unsigned short	m_bitsPerSample;
		char			m_dataChunkId[4];
		unsigned long	m_dataSize;
	};

private:
	IDirectSound8* m_directSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer1;
	std::map<const char*, IDirectSoundBuffer8*> m_sounds;
};