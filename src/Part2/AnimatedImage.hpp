#ifndef ANIMATEDIMAGE_HPP
#define ANIMATEDIMAGE_HPP

#include "../BaseEngine.h"
#include "../ImageManager.h"
#include "../DisplayableObject.h"

#include "../RawImageData.h"
#include <map>
#include <memory>
#include <vector>

typedef struct {
    std::shared_ptr<RawImageData> spritesheet;
    int frame_width;
    int frame_height;
    int frame_count;
    int time_per_frame;
} animation_t;

class AnimatedImage : public SimpleImage {
public:
    AnimatedImage(BaseEngine *eng, int playing=1, int loop=1, float time_per_frame=1, int start_frame = 0);
    ~AnimatedImage();

    void update();

    void setFrame(int frame);
    int getFrame();

    int getFrameWidth();

    void togglePlaying();
    void setPlaying(bool playing);
    bool isPlaying();

    void setLooping(bool loop);
    bool isLooping();

    void draw(DrawingSurface *target, int x, int y);

    void addAnimation(std::string s, animation_t anim);
    int getAnimationLength(std::string s);
    void setCurrentAnimation(std::string s);
    std::string getCurrentAnimation();
protected:
    bool playing;
    bool loop;
    int frame_index;
    std::map<std::string, animation_t> spritesheets;
    std::string current_animation;
    BaseEngine *eng;
    int last_update_tick;

    void setImage();
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
            image.draw(getEngine()->getForegroundSurface(), m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY);
			//image.renderImageWithMask(getEngine()->getForegroundSurface(), image.getFrame(), 0, m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight);
		}
	}

    virtual void virtDoUpdate(int iCurrentTime) override {
        image.update();
        if (image.getRawImageData() != nullptr) {
            this->m_iDrawWidth = image.getFrameWidth();
            this->m_iDrawHeight = image.getHeight();
        }
        redrawDisplay();
    }

    AnimatedImage *getImage() {return &image;}
};

#endif