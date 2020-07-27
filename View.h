/**
 * @author Gabriele D'Alò
 * @version 06/07/2020
 */

#ifndef PROGETTO_LABORATORIO_VIEW_H
#define PROGETTO_LABORATORIO_VIEW_H

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/frame.h>

#include "Observer.h"
#include "Model.h"
#include "Controller.h"

class View : public wxFrame, public Observer {  // Concrete Observer

public:
    View(Model* model, Controller* controller, wxWindow* parent=NULL, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
    virtual ~View();
    void update(int x,int y,float value) override;
    void update(int x,int y,string value) override;
    void onSelectCell(wxCommandEvent &event);
    void onChangeCell(wxCommandEvent &event);

private:
    Model* model;
    Controller* controller;

    wxGrid* grid;

    int numRows;
    int numCols;
};


#endif //PROGETTO_LABORATORIO_VIEW_H
