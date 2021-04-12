#ifndef ANIMATEDIMAGE_HPP
#define ANIMATEDIMAGE_HPP

#include "../BaseEngine.h"
#include "../ImageManager.h"
#include "../DisplayableObject.h"

#include "../RawImageData.h"
#include <map>
#include <memory>
#include <vector>

typedef std::shared_ptr<RawImageData> frame_t;
typedef std::vector<frame_t> animation_t;

class AnimatedImage : public SimpleImage {
private:
    int last_update_tick;

    void setImage();
public:
    AnimatedImage(BaseEngine *eng, int playing=1, int loop=1, float time_per_frame=1, int start_frame = 0);
    ~AnimatedImage();

    void update();

    void setFrame(int frame);
    int getFrame();

    void setFrameWidth(int width);
    int getFrameWidth();

    void togglePlaying();
    void setPlaying(bool playing);
    bool isPlaying();

    void setLooping(bool loop);
    bool isLooping();

    void setTimePerFrame(int tpf);
    int getTimePerFrame();

    void addAnimation(std::string s, animation_t anim);
    int getAnimationLength(std::string s);
    void setCurrentAnimation(std::string s);
protected:
    bool playing;
    bool loop;
    int frame_index;
    int time_per_frame;
    int frame_width;
    animation_t *current_animation;
    std::map<std::string, animation_t> frame_map;
    BaseEngine *eng;
};

class AnimatedImageObject : public DisplayableObject {
private:
    bool topleftorigin;
    AnimatedImage image;
public:
    AnimatedImageObject(BaseEngine *eng, int x, int y, float scale, bool topleftorigin = true, bool visible = true)
        : DisplayableObject(eng, x, y, topleftorigin), topleftorigin(topleftorigin),
        image(eng) {
        this->m_iDrawWidth = 0;
        this->m_iDrawHeight = 0;

        m_iStartDrawPosX = 0;
		m_iStartDrawPosY = 0;
		setVisible(visible);
    }

    virtual void virtDraw() override
	{
		if (isVisible() && image.getRawImageData())
		{
			image.renderImageWithMask(getEngine()->getForegroundSurface(), image.getFrame(), 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
		}
	}

    virtual void virtDoUpdate(int iCurrentTime) override {
        image.update();
        if (image.getRawImageData() != nullptr) {
            this->m_iDrawWidth = image.getWidth();
            this->m_iDrawHeight = image.getHeight();
        }
        redrawDisplay();
    }

    AnimatedImage *getImage() {return &image;}
};

#endif