//
// Created by Gabriele on 06/07/2020.
//

#include "View.h"
#include <sstream>
#include <iomanip>

View::View(Model* model, Controller* controller, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ), numRows(model->getWidth()),numCols(model->getHeight()){

    this->model = model;
    this->model->addObserver(this);
    this->controller = controller;

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* frameSizer;
    frameSizer = new wxBoxSizer( wxHORIZONTAL );

    grid = new wxGrid(this,-1,wxPoint(0,0),wxSize(700,500));
    grid->CreateGrid(numRows,numCols);

    // Connect Events
    grid->Connect(wxEVT_GRID_CELL_CHANGED,wxCommandEventHandler(View::onChangeCell),NULL,this);

    frameSizer->Add(grid,1,wxEXPAND|wxALL,5);
    this->SetSizer(frameSizer);
    this->Layout();

    this->Centre( wxBOTH );

}

View::~View() {
    // Disconnect Events
    grid->Disconnect(wxEVT_GRID_CELL_CHANGED,wxCommandEventHandler(View::onChangeCell),NULL,this);

    // unsubscribe from model
    model->removeObserver(this);
}

void View::onChangeCell(wxCommandEvent &event){
    controller->checkOperation(grid->GetCursorRow(),grid->GetCursorColumn(),string(grid->GetCellValue(grid->GetCursorRow(),grid->GetCursorColumn()).mb_str(wxConvUTF8)));
}

void View::update(int x,int y,float value) {
    stringstream s;
    s << fixed << setprecision(2) << value;

    grid->SetCellValue(x,y,s.str());
}