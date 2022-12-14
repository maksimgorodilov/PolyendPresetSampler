#include "samplerApp.h"

void Sampler::init() {
    for (int i = 0; i < Sampler::TRACKS_COUNT; i++) {
        this->tracks[i].state = TrackState::VOLTAGE;
        this->tracks[i].steps = Track::DEFAULT_LENGTH;
        this->tracks[i].playingSteps = Track::DEFAULT_LENGTH;
        this->tracks[i].currentStep = 0;
    }
    this->currentTrack = 0;
    this->clockPeriod = -1;
    this->clockElapsedTime = 0;
}

bool Sampler::isRecording() {
    return this->currentMode == SamplerMode::RECORDING;
}

void Sampler::toggleSamplerMode() {
    this->currentMode = this->isRecording() ? SamplerMode::PLAYING : SamplerMode::RECORDING;
    this->isClockRecordingStarted = false;
    for (int i = 0; i < Sampler::TRACKS_COUNT; i++) {
        TrackState state = this->isRecording() ? TrackState::CLOCK : TrackState::VOLTAGE;
        this->tracks[i].state = state;
        this->tracks[i].playingSteps = this->tracks[i].steps;
        this->tracks[i].currentStep = 0;
    }
};

void Sampler::toggleTrack(int trackIndex) {
    if (this->isRecording()) {
        this->tracks[trackIndex].state = this->tracks[trackIndex].state == TrackState::CLOCK ? TrackState::VOLTAGE : TrackState::CLOCK;
    }
}

void Sampler::setSteps(int steps) {
    if (this->isRecording()) {
        this->tracks[this->currentTrack].steps = steps;
    } else if (steps <= this->tracks[this->currentTrack].steps) {
        this->tracks[this->currentTrack].playingSteps = steps;
    }
}

void Sampler::handleClockStep() {
    Track* track = &this->tracks[this->currentTrack];
    int playingStep = track->currentStep + 1;
    if (playingStep + 1 > track->steps) {
        playingStep = 0;
    }
    track->currentStep = playingStep;
}

void Sampler::recordClockStep() {
    if (this->clockPeriod == -1) {
        if (!this->isClockRecordingStarted) {
            this->isClockRecordingStarted = true;
            this->clockElapsedTime = 0;
        } else {
            this->clockPeriod = this->clockElapsedTime;
            this->clockElapsedTime = 0;
        }
    }
}

void Sampler::checkClockProgress() {
    if (this->clockPeriod != -1 && this->clockElapsedTime >= this->clockPeriod) {
        this->handleClockStep();
        this->clockElapsedTime = 0;
    }
}
