#include "GameApp.h"
#include "Board.h"
#include "Game15.h"

#include <memory>

bool GameApp::OnInit()
{
    auto* board = new Board;
    board->Show(true);
    return true;
}
