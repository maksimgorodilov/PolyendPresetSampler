
#ifndef SAMPLER_EUCLAPP_H_
#define SAMPLER_EUCLAPP_H_
#include "presetApp.h"
#include "elapsedMillis.h"

enum SamplerMode {
    PLAYING,
    RECORDING,
};

enum TrackState {
    VOLTAGE,
    CLOCK,
};

class Track {
    public:
        static constexpr int TRACK_LENGTH = 32;
        static constexpr int DEFAULT_LENGTH = 16;
    
        TrackState state = TrackState::VOLTAGE;
        int steps;
        int playingSteps;
        int currentStep;
};

class Sampler {
    private:
        bool isClockRecordingStarted = false;
        elapsedMillis clockElapsedTime;
        int clockPeriod;
    public:
        static constexpr int TRACKS_COUNT = 9;

        void init();
        void toggleSamplerMode();
        void toggleTrack(int trackIndex);
        void setSteps(int steps);
        void handleClockStep();
        void recordClockStep();
        void checkClockProgress();
        bool isRecording();

        SamplerMode currentMode = SamplerMode::PLAYING;
        Track tracks[Sampler::TRACKS_COUNT];
        int currentTrack = 0;
};

#endif