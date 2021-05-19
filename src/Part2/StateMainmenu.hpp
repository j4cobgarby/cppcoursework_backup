#ifndef STATEMAINMENU_HPP
#define STATEMAINMENU_HPP
#include "GameState.hpp"
#include "MiningGame.hpp"
#include "Form.hpp"

class StateMainmenu : public GameState {
protected:
    Form *menu;
public:
    StateMainmenu(MiningGameEngine *eng);

    void onChangeTo() override;

    void virtMouseDown(int btn, int x, int y) override;
    void virtKeyDown(int key) override;

    void virtSetupBackgroundBuffer() override;
};
#endif