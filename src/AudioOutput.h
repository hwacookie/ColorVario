#ifndef KYSTSOFT_AUDIOOUTPUT_H
#define KYSTSOFT_AUDIOOUTPUT_H

#include "Callback.h"
#include <audio_io.h>
#include <vector>

namespace Kystsoft {

class AudioOutput
{
public:
	AudioOutput(int sampleRate, audio_channel_e channel, audio_sample_type_e type);
	AudioOutput(const AudioOutput& other) = delete;
	AudioOutput& operator=(const AudioOutput& rhs) = delete;
	~AudioOutput() noexcept { audio_out_destroy(output); }
	operator audio_out_h() const { return output; }
	void setSoundStreamInfo(sound_stream_info_h streamInfo); // TODO: Figure out what this function does
	bool isPrepared() const { return prepared; }
	void prepare();
	void unprepare();
	bool isPaused() const { return paused; }
	void pause();
	void resume();
	void drain();
	void flush();
	void write(std::vector<uint8_t>& buffer);
	void write(std::vector<int16_t>& buffer);
	int bufferSize() const;
	int sampleRate() const;
	audio_channel_e channel() const;
	audio_sample_type_e sampleType() const;
	sound_type_e soundType() const;
	using WriteCallback = Callback<AudioOutput&, size_t>;
	const WriteCallback& writeCallback() const { return writeCb; }
private:
	static void streamWriteCallback(audio_out_h handle, size_t nbytes, void* user_data);
	void onStreamWrite(size_t bytesRequested) { writeCb.execute(*this, bytesRequested); }
	audio_out_h output = nullptr;
	bool prepared = false;
	bool paused = false;
	WriteCallback writeCb;
};

} // namespace Kystsoft

#endif // KYSTSOFT_AUDIOOUTPUT_H