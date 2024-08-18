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

#include "dsf_osc.h"
#include <math.h>

#define PI_DSF 3.1415927410125732421875f
#define TWOPI_DSF (2.0f * PI_DSF)

void DSFOscillator::Init(float sample_rate)
{
    sample_rate_ = sample_rate;
    theta_ = 0.0f;
    beta_ = 0.0f;
    sync_ = true;
    center_frequency_ = 110.0f;
    modulation_frequency_ = 110.0f;
    ratio_ = 0.5f;
    spectra_ = 0.5f;
}

float DSFOscillator::Process()
{

    // update center frequency
    theta_ += TWOPI_DSF * center_frequency_ / sample_rate_;

    beta_ += TWOPI_DSF * modulation_frequency_ / sample_rate_;
    
    // for reverse, perhaps something like this?
    // beta_ -= TWOPI_DSF * modulation_frequency_ / sample_rate_;

    if (theta_ >= TWOPI_DSF)
    {
        theta_ -= TWOPI_DSF;

        // resets the period of the beta_ oscillator when theta_ finishes a cycle
        if (sync_)
        {
            beta_ = TWOPI_DSF * modulation_frequency_ / sample_rate_;
        }
    }

    // reset beta_ when cyle finishes, independent of theta_
    if (!sync_)
    {
        if (beta_ >= TWOPI_DSF)
        {
            beta_ -= TWOPI_DSF;
        }	
    }

	float x = sin(theta_);
	float y = sin(theta_ - beta_);
	float z = cos(beta_);

    // "one-sided" spectra
	// (sin(theta) - a * sin(theta - beta)) / (1 + a * a - 2 * a * cos(beta));
	float onesided = (x - ratio_ * y) / (1 + ratio_ * ratio_ - 2 * ratio_ * z);
	// "two-sided" spectra
	// (1 - a * a) * sin(theta - beta) / (1 + a * a - 2 * a * cos(beta));
	float twosided = (1 - ratio_ * ratio_) * y / (1 + ratio_ * ratio_ - 2 * ratio_ * z);

    return linearMap(spectra_, 0.0f, 1.0f, onesided, twosided); 

}

void DSFOscillator::SetCenterFrequency(float center_frequency)
{
    center_frequency_ = center_frequency;
}

void DSFOscillator::SetModulationFrequency(float modulation_frequency)
{
    modulation_frequency_ = modulation_frequency;
}

void DSFOscillator::SetRatio(float ratio)
{
    ratio_ = ratio;
}

void DSFOscillator::SetSpectra(float spectra)
{
    if (spectra > 1.0f)
    {
        spectra = 1.0f;
    }

    if (spectra < 0.0f)
    {
        spectra = 0.0f;
    }

    spectra_ = spectra;
}

void DSFOscillator::SetSync(bool sync)
{
    sync_ = sync;
}

float DSFOscillator::linearMap(float x, float in_min, float in_max, float out_min, float out_max)
{
	if (x < 0.0f)
	{
		x = 0.0f;
	}

	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}