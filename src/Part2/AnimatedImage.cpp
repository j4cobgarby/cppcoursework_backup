#include "../header.h"

#include "AnimatedImage.hpp"

AnimatedImage::AnimatedImage(BaseEngine *eng, int playing, int loop, float time_per_frame, int start_frame)
    : SimpleImage(),
    playing(playing),
    loop(loop),
    time_per_frame(time_per_frame),
    frame_index(start_frame),
    current_animation(nullptr),
    eng(eng) {

    this->last_update_tick = eng->getRawTime();
}

AnimatedImage::~AnimatedImage() {
}

void AnimatedImage::update() {
    if (eng->getRawTime() - this->last_update_tick > this->time_per_frame) {
        last_update_tick = eng->getRawTime();
        if (!current_animation) return;
        frame_index = (frame_index + 1) % current_animation->size();
        setImage();
    }
}

void AnimatedImage::setFrame(int frame) {
    this->frame_index = frame;
    setImage();
}

int AnimatedImage::getFrame() {
    return this->frame_index;
}

void AnimatedImage::setFrameWidth(int width) {
    this->frame_width = width;
}

int AnimatedImage::getFrameWidth() {
    return this->frame_width;
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

void AnimatedImage::setTimePerFrame(int tpf) {
    this->time_per_frame = tpf;
}

int AnimatedImage::getTimePerFrame() {
    return this->time_per_frame;
}

void AnimatedImage::addAnimation(std::string s, animation_t anim) {
    frame_map[s] = anim;
}

int AnimatedImage::getAnimationLength(std::string s) {
    return frame_map[s].size();
}

void AnimatedImage::setCurrentAnimation(std::string s) {
    current_animation = &(frame_map[s]);
    setImage();
}

void AnimatedImage::setImage() {
    theData = (*current_animation)[frame_index];
}