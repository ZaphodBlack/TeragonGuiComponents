/*
Copyright (c) 2013 Teragon Audio. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include "ImageKnob.h"

namespace teragon {

ImageKnob::ImageKnob(ConcurrentParameterSet &parameters, const ParameterString &name,
                     const ResourceCache *resources, const String &imageName) :
Slider(juce::Slider::RotaryVerticalDrag, juce::Slider::NoTextBox),
PluginParameterComponent(parameters, name, resources, imageName) {
    knobWidth = imageStates->normal.getWidth();
    filmstripImageCount = imageStates->normal.getHeight() / knobWidth - 1;
    knobArea.setX(0);
    knobArea.setY(0);
    knobArea.setWidth(knobWidth);
    knobArea.setHeight(knobWidth);

    setRange(0.0, 1.0);
    setValue(parameter->getScaledValue(), NotificationType::dontSendNotification);
}

void ImageKnob::onParameterUpdated(const Parameter* parameter) {
    juce::MessageManagerLock lock;
    setValue(parameter->getScaledValue(), NotificationType::dontSendNotification);
}

void ImageKnob::valueChanged() {
    onValueChanged(getValue());
}

void ImageKnob::paint(Graphics &g) {
    if(isMouseOver() && !isMouseButtonDown()) {
        onMouseOver();
    }

    const int y = (int)(filmstripImageCount * getValue()) * knobWidth;
    knobArea.setY(y);
    const Image knobFrame = imageStates->normal.getClippedImage(knobArea);
    const Image resizedKnobFrame = knobFrame.rescaled(knobWidth, knobWidth, Graphics::highResamplingQuality);
    g.drawImageAt(resizedKnobFrame, 0, 0);
}

} // namespace teragon
