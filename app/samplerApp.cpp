#include "samplerApp.h"

void SamplerApp::updateEncoders() {
    for (int i = 0; i < PresetApp::encoderCount; i++) {
        if (this->sampler.currentTrack == i) {
            PresetApp::EncoderLedColors color = !this->sampler.isRecording()
                ? PresetApp::EncoderLedColors::Blue
                : this->sampler.tracks[i].state == TrackState::CLOCK
                    ? PresetApp::EncoderLedColors::Green
                    : PresetApp::EncoderLedColors::Cyan;
            this->setEncoderLED(i, color, 100);
        } else {
            this->setEncoderLED(i, PresetApp::EncoderLedColors::Off, 0);
        }
    }
}

void SamplerApp::updatePads() {
    for (int i = 0; i < Track::TRACK_LENGTH; i++) {
        int colorIntensity = 0;
        Track* track = &this->sampler.tracks[this->sampler.currentTrack];
        if (i == track->currentStep) {
            colorIntensity = SamplerApp::ACTIVE_PAD_INTENSITY;
        } else if (i < track->steps) {
            if (
                this->sampler.isRecording()
                || i < track->playingSteps
            ) {
                colorIntensity = SamplerApp::MAIN_PAD_INTENSITY;
            } else {
                colorIntensity = SamplerApp::FADE_PAD_INTENSITY;
            }
        } else {
            colorIntensity = 0;
        }
        this->setPadLED(i, colorIntensity);
    } 
}

void SamplerApp::init() {
    this->sampler.init();
    this->updateEncoders();
    this->updatePads();
}

void SamplerApp::update() {
    this->sampler.checkClockProgress();
    this->updateEncoders();
    this->updatePads();
}

void SamplerApp::onEncoderPress(int encoderIdx) {
    if (encoderIdx == this->sampler.currentTrack) {
        this->sampler.toggleTrack(encoderIdx);
    }
    this->sampler.currentTrack = encoderIdx;
}

void SamplerApp::onEncoderRelease(int encoderIdx) {}

void SamplerApp::onEncoderRotate(int encoderIdx, int delta) {}

void SamplerApp::onCVInputChange(int value) {
    if (value > PresetApp::cv_4V && this->lastClockDirection == ClockDirection::DOWN) {
        if (this->sampler.isRecording()) {
            this->sampler.recordClockStep();
        } else {
            this->sampler.handleClockStep();
        }
        this->lastClockDirection = ClockDirection::UP;
    }
    if (value < PresetApp::cv_4V) {
        this->lastClockDirection = ClockDirection::DOWN;
    }
}

void SamplerApp::onButtonPress(Buttons button) {
    if (button == PresetApp::Buttons::Rec) {
        this->sampler.toggleSamplerMode();
    }
}

void SamplerApp::onButtonRelease(Buttons button) {}

void SamplerApp::onPadPress(int padIdx) {
    this->sampler.setSteps(padIdx + 1);
}

void SamplerApp::onPadRelease(int padIdx) {}