/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

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
    grid->Connect(wxEVT_GRID_EDITOR_SHOWN,wxCommandEventHandler(View::onSelectCell),NULL,this);
    grid->Connect(wxEVT_GRID_CELL_CHANGED,wxCommandEventHandler(View::onChangeCell),NULL,this);

    frameSizer->Add(grid,1,wxEXPAND|wxALL,5);
    this->SetSizer(frameSizer);
    this->Layout();

    this->Centre( wxBOTH );

}

View::~View() {
    // Disconnect Events
    grid->Disconnect(wxEVT_GRID_EDITOR_SHOWN,wxCommandEventHandler(View::onSelectCell),NULL,this);
    grid->Disconnect(wxEVT_GRID_CELL_CHANGED,wxCommandEventHandler(View::onChangeCell),NULL,this);

    // unsubscribe from model
    model->removeObserver(this);
    delete model;
    delete grid;
}

void View::onSelectCell(wxCommandEvent &event){
    controller->checkCell(grid->GetCursorRow(),grid->GetCursorColumn(),string(grid->GetRowLabelValue(grid->GetCursorRow()).mb_str(wxConvUTF8)),string(grid->GetColLabelValue(grid->GetCursorColumn()).mb_str(wxConvUTF8)),string(grid->GetCellValue(grid->GetCursorRow(),grid->GetCursorColumn()).mb_str(wxConvUTF8)));
}

void View::onChangeCell(wxCommandEvent &event){
    // Viene chiamato il metodo che controlla l'operazione da eseguire sulla cella (utilizzo di una formula o aggiunta di un valore)
    controller->checkOperation(grid->GetCursorRow(),grid->GetCursorColumn(),string(grid->GetRowLabelValue(grid->GetCursorRow()).mb_str(wxConvUTF8)),string(grid->GetColLabelValue(grid->GetCursorColumn()).mb_str(wxConvUTF8)),string(grid->GetCellValue(grid->GetCursorRow(),grid->GetCursorColumn()).mb_str(wxConvUTF8)));
}

void View::update(int x,int y,float value) {
    if(!controller->isError()) {
        stringstream s;
        s << fixed << setprecision(2) << value;
        grid->SetCellValue(x,y,s.str());
    }else {
        grid->SetCellValue(x,y,"Error");
    }
}

void View::update(int x,int y,string value) {
        stringstream s;
        s << fixed << value;
        grid->SetCellValue(x,y,s.str());
}