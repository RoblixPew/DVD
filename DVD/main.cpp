#include <wx/wx.h>
#include "MyPanelImpl.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        wxFrame *frame = new wxFrame(NULL, wxID_ANY, "DVD Logo Bounce", wxDefaultPosition, wxSize(600, 400));
        
        new MyPanelImpl(frame);
        
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
