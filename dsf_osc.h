// Copyright 2024 Craig Corvin
//
// Author: Craig Corvin
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------

#pragma once

#include <math.h>

// Discrete Summation Formula Oscillator
class DSFOscillator
{
    public:
        DSFOscillator() {}
        ~DSFOscillator() {}

        /*
         @param sample_rate the sample rate of the audio engine
         */
        void Init(float sample_rate);

        /*
        @param return 
        */
        float Process();

        /*
        @param center_frequency
        */
        void SetCenterFrequency(float center_frequecy);

        /*
        @param modulation_frequency
        */
        void SetModulationFrequency(float modulation_frequency);

        /*
        @param ratio 0.0f to 1.0f;
        */
        void SetRatio(float ratio);

        /*
        @param spectra 0.0f to 1.0f for "one-sided" spectra to "two-sided" spectra
        */
        void SetSpectra(float spectra);

        /*
        @param sync
        */
        void SetSync(bool sync);

        /*
        @param return
        */
        float linearMap(float x, float in_min, float in_max, float out_min, float out_max);

    private:
        float sample_rate_;
        float theta_;
        float beta_;
        // sync of beta to theta
        bool sync_;
        float center_frequency_;
        float modulation_frequency_;
        // We will call a "the ratio" because the amplitude of each partial is
        // related to the amplitudes of adjacent partials by factors of a
        // 0.0f to 1.0f;
        float ratio_;
        // 0.0f to 1.0f for "one-sided" spectra to "two-sided" spectra
        float spectra_;
};