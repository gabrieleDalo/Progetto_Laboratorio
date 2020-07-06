#include <iostream>

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "View.h"
#include "Model.h"
#include "Controller.h"

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    Model* model = new Model;
    Controller* controller = new Controller(model);
    View *frame = new View(model, controller, NULL, wxID_ANY, "Foglio di calcolo" );
    frame->Show( true );

    return true;
}
