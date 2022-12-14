#ifndef SAMPLER_APP_EUCLAPP_H_
#define SAMPLER_APP_EUCLAPP_H_

#include "presetApp.h"
#include "sampler.h"

enum ClockDirection {
    UP,
    DOWN,
};

class SamplerApp: public PresetApp {
    private:
        Sampler sampler;
        void updateEncoders();
        void updatePads();
        ClockDirection lastClockDirection = ClockDirection::DOWN;

    public: 
        void init();
        void update();

        void onEncoderPress(int encoderIdx);
        void onEncoderRelease(int encoderIdx);
        void onEncoderRotate(int encoderIdx, int delta);
        void onCVInputChange(int value);
        void onButtonPress(Buttons button);
        void onButtonRelease(Buttons button);
        void onPadPress(int padIdx);
        void onPadRelease(int padIdx);

        static constexpr int ACTIVE_PAD_INTENSITY = 75;
        static constexpr int MAIN_PAD_INTENSITY = 40;
        static constexpr int FADE_PAD_INTENSITY = 20;
};

#endif /* SAMPLER_APP_EUCLAPP_H_ */