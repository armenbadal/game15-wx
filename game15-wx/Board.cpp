#include "Board.h"
#include "Game15.h"

#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>


/**/
Board::Board()
    : wxFrame(nullptr, wxID_ANY, wxT("Game 15"), 
        wxDefaultPosition, wxDefaultSize, 
        wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION)
{
    SetIcon(wxICON(GAME15_ICO));

    _logic = std::make_shared<Game15>();

    // չափերի կարգավորում
    auto size = GetSize();
    const auto w = size.GetWidth();
    const auto h = size.GetHeight();
    const auto wh = (w > h ? w : h) * 1;
    size.SetWidth(wh);
    size.SetHeight(wh);
    SetSize(size);

    createMenus();
    CreateStatusBar(2);

    createButtons();
    updateView();


    Centre();
}


/**/
void Board::createMenus()
{
    _mainMenuBar = new wxMenuBar;

    _gameMenu = new wxMenu;

    auto* _newGame = new wxMenuItem(_gameMenu, wxNewId(), wxT("Նոր"));
    Bind(wxEVT_COMMAND_MENU_SELECTED, 
        [this](auto& ev)
        {
            this->_logic = std::make_shared<Game15>();
            this->updateView();
        },
        _newGame->GetId());
    _gameMenu->Append(_newGame);

    _gameMenu->Append(new wxMenuItem(_gameMenu, wxID_SEPARATOR));

    auto* _exitGame = new wxMenuItem(_gameMenu, wxNewId(), wxT("Ելք"));
    Bind(wxEVT_COMMAND_MENU_SELECTED,
        [this](auto& ev)
        {
            this->Close(true);
        },
        _exitGame->GetId());
    _gameMenu->Append(_exitGame);

    _mainMenuBar->Append(_gameMenu, wxT("Խաղ"));

    SetMenuBar(_mainMenuBar);
}


/**/
void Board::createButtons()
{
    auto font = GetFont();
    font.SetPointSize(2 * font.GetPointSize());

    auto* grid = new wxGridSizer(4, 4, wxSize(0, 0));

    const auto side = _logic->side();
    for( int i = 0; i < side * side; ++i ) {
        auto* b = new wxButton(this, wxNewId(), "*");
        b->SetFont(font);
        b->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
            [this](auto& ev) { this->OnOneStep(ev); });
        _buttons[b] = wxPoint(i / side, i % side);
        grid->Add(b, i, wxEXPAND);
    }

    SetSizer(grid);
}


/**/
void Board::updateView()
{
    for( auto[b, p] : _buttons ) {
        auto nv = _logic->field(p.x, p.y);
        wxString label;
        if( nv != 0 )
            label << nv;
        b->SetLabel(label);
    }

    SetStatusText(wxT("Քայլ: ") + wxString::Format("%i", _logic->step()), 0);
}


/**/
void Board::OnOneStep(wxCommandEvent& ev)
{
    auto* b = dynamic_cast<wxButton*>(ev.GetEventObject());
    auto s = _buttons[b];
    _logic->play(s.x, s.y);
    updateView();
    if( _logic->isOver() )
        SetStatusText(wxT("Հաղթանա՛կ"), 1);
}
