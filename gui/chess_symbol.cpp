#include "chess_symbol.h"

ChessSymbol::ChessSymbol(const wxString path)
{
    captured = false;
    dragging = false;
    img = wxImage(path, wxBITMAP_TYPE_ANY);
}

void ChessSymbol::Draw(wxDC& dc, int length)
{
    spacingLength = length;
    symbolSize = length * 0.8;
    spacingOffset = length * 0.1;
    if(dragging){
        dc.DrawBitmap(
            wxBitmap(img.Scale(symbolSize, symbolSize)),
            pixelX, pixelY, false
        );
    } else if(!captured){
        dc.DrawBitmap(
            wxBitmap(img.Scale(symbolSize, symbolSize)),
            boardX * length + spacingOffset, boardY * length + spacingOffset, false
        );
    }
}

bool ChessSymbol::BeginMove(wxPoint pt)
{
    if(captured){
        return false;
    }
    pixelX = boardX * spacingLength + spacingOffset;
    pixelY = boardY * spacingLength + spacingOffset;
    if(pixelX <= pt.x && pt.x <= pixelX + symbolSize && pixelY <= pt.y && pt.y <= pixelY + symbolSize){
        pixelX = pt.x - symbolSize / 2;
        pixelY = pt.y - symbolSize / 2;
        dragging = true;
        return true;
    } else {
        return false;
    }
}

void ChessSymbol::FinishMove(wxPoint pt)
{
    if(dragging){
        boardX = pt.x / spacingLength;
        boardY = pt.y / spacingLength;
        dragging = false;
    }
}

void ChessSymbol::Move(wxPoint pt)
{
    if(dragging){
        pixelX = pt.x - symbolSize / 2;
        pixelY = pt.y - symbolSize / 2;
    }
}
