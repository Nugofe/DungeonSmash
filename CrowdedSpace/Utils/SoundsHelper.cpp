#include "SoundsHelper.h"
#include "../App/SimpleSound.h"

SoundsHelper& SoundsHelper::GetInstance()
{
	return reinterpret_cast<SoundsHelper&>(CSimpleSound::GetInstance());
}

bool SoundsHelper::LoadWaveFile(const char* filename)
{
	int error;
	FILE* filePtr = nullptr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;
	// Find entry in map.
	IDirectSoundBuffer8** secondaryBuffer = &m_sounds[filename];

	// Open the wave file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the wave file header.
	count = (unsigned int)fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if ((waveFileHeader.m_chunkId[0] != 'R') || (waveFileHeader.m_chunkId[1] != 'I') ||
		(waveFileHeader.m_chunkId[2] != 'F') || (waveFileHeader.m_chunkId[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if ((waveFileHeader.m_format[0] != 'W') || (waveFileHeader.m_format[1] != 'A') ||
		(waveFileHeader.m_format[2] != 'V') || (waveFileHeader.m_format[3] != 'E'))
	{
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if ((waveFileHeader.m_subChunkId[0] != 'f') || (waveFileHeader.m_subChunkId[1] != 'm') ||
		(waveFileHeader.m_subChunkId[2] != 't') || (waveFileHeader.m_subChunkId[3] != ' '))
	{
		return false;
	}

	// Check for the data chunk header.
	if ((waveFileHeader.m_dataChunkId[0] != 'd') || (waveFileHeader.m_dataChunkId[1] != 'a') ||
		(waveFileHeader.m_dataChunkId[2] != 't') || (waveFileHeader.m_dataChunkId[3] != 'a'))
	{
		return false;
	}

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = waveFileHeader.m_audioFormat;
	waveFormat.nSamplesPerSec = waveFileHeader.m_sampleRate;
	waveFormat.wBitsPerSample = waveFileHeader.m_bitsPerSample;
	waveFormat.nChannels = waveFileHeader.m_numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.m_dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.m_dataSize];
	if (!waveData)
	{
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = (unsigned int)fread(waveData, 1, waveFileHeader.m_dataSize, filePtr);
	if (count != waveFileHeader.m_dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	result = (*secondaryBuffer)->Lock(0, waveFileHeader.m_dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.m_dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = 0;

	// play and stop the sound with no volume to make it play directly when PlaySound is called ingame
	PlaySound(filename, DSBVOLUME_MIN);
	StopSound(filename);

	return true;
}

bool SoundsHelper::PlaySound(const char* filename, int volume, DWORD flags)
{
	HRESULT result;

	// Set position at the beginning of the sound buffer.
	if (m_sounds[filename] == nullptr)
	{
		result = LoadWaveFile(filename);
		if (FAILED(result))
		{
			return false;
		}
	}

	if (m_sounds[filename])
	{
		result = m_sounds[filename]->SetCurrentPosition(0);
		if (FAILED(result))
		{
			return false;
		}

		// Set volume of the buffer to 100%.
		result = m_sounds[filename]->SetVolume(volume);
		if (FAILED(result))
		{
			return false;
		}

		// Play the contents of the secondary sound buffer.
		result = m_sounds[filename]->Play(0, 0, flags);
		if (FAILED(result))
		{
			return false;
		}
		return true;
	}
	return false;
}

bool SoundsHelper::StopSound(const char* filename)
{
	return CSimpleSound::GetInstance().StopSound(filename);
}

bool SoundsHelper::IsSoundPlaying(const char* filename)
{
	return CSimpleSound::GetInstance().IsPlaying(filename);
}

void SoundsHelper::SetSoundVolume(const char* filename, int volume)
{
	if (m_sounds[filename] != nullptr)
	{
		m_sounds[filename]->SetVolume(volume);
	}
}