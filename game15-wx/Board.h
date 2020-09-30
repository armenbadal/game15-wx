#ifndef __BOARD_H__
#define __BOARD_H__

#include <wx/frame.h>

#include <map>
#include <memory>

class Game15;

class wxButton;
class wxMenuBar;
class wxMenu;

class Board : public wxFrame {
public:
    Board();

private:
    void createMenus();
    void createButtons();

    void updateView();

    void OnOneStep(wxCommandEvent&);

private:
    wxMenuBar* _mainMenuBar = nullptr;
    wxMenu* _gameMenu = nullptr;

    std::map<wxButton*,wxPoint> _buttons;

    std::shared_ptr<Game15> _logic;
};

#endif // __BOARD_H__
