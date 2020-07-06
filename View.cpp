//
// Created by Gabriele on 06/07/2020.
//

#include "View.h"

View::View(Model* model, Controller* controller, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ) {
    numRows = 100;
    numCols = 50;

    this->model = model;
    this->model->addObserver(this);
    this->controller = controller;

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* frameSizer;
    frameSizer = new wxBoxSizer( wxHORIZONTAL );

    grid = new wxGrid(this,-1,wxPoint(0,0),wxSize(700,500));
    grid->CreateGrid(numRows,numCols);

    frameSizer->Add(grid,1,wxEXPAND|wxALL,5);
    this->SetSizer(frameSizer);
    this->Layout();

    this->Centre( wxBOTH );

    // Connect Events


    update();
}

View::~View() {
    // Disconnect Events

    // unsubscribe from model
    model->removeObserver(this);
}

void View::update() {

}