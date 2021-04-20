#include "../header.h"

#include "AnimatedImage.hpp"

AnimatedImage::AnimatedImage(BaseEngine *eng, int playing, int loop, float time_per_frame, int start_frame)
    : SimpleImage(),
    playing(playing),
    loop(loop),
    frame_index(start_frame),
    eng(eng) {

    this->last_update_tick = eng->getRawTime();
}

AnimatedImage::~AnimatedImage() {
}

void AnimatedImage::update() {
    if (eng->getRawTime() - last_update_tick > spritesheets[current_animation].time_per_frame) {
        last_update_tick = eng->getRawTime();
        frame_index = (frame_index + 1) % spritesheets[current_animation].frame_count;
    }
}

void AnimatedImage::setFrame(int frame) {
    this->frame_index = frame;
}

int AnimatedImage::getFrame() {
    return this->frame_index;
}

int AnimatedImage::getFrameWidth() {
    return spritesheets[current_animation].frame_width;
}

void AnimatedImage::togglePlaying() {
    setPlaying(!this->playing);
}

void AnimatedImage::setPlaying(bool playing) {
    this->playing = playing;
}

bool AnimatedImage::isPlaying() {
    return this->playing;
}

void AnimatedImage::setLooping(bool loop) {
    this->loop = loop;
}

bool AnimatedImage::isLooping() {
    return this->loop;
}

void AnimatedImage::setImage() {
    theData = spritesheets[current_animation].spritesheet;
    setTransparencyColour(0x000000);
}

void AnimatedImage::draw(DrawingSurface *target, int x, int y) {
    renderImage(target, 
        spritesheets[current_animation].frame_width * frame_index, 
        0, x, y, 
        spritesheets[current_animation].frame_width, 
        spritesheets[current_animation].frame_height);
}

void AnimatedImage::addAnimation(std::string s, animation_t anim) {
    spritesheets[s] = anim;
}

int AnimatedImage::getAnimationLength(std::string s) {
    return spritesheets[s].frame_count;
}

void AnimatedImage::setCurrentAnimation(std::string s) {
    current_animation = s;
    setFrame(0);
    setImage();
}

std::string AnimatedImage::getCurrentAnimation() {
    return current_animation;
}