#pragma once
#include "dvdlogo.h"
#include <wx/timer.h>
#include <wx/dcbuffer.h>
#include <wx/image.h>

class MyPanelImpl : public m_panelAnimazione 
{
public:
    MyPanelImpl(wxWindow* parent);

private:
    wxTimer m_timer;
    wxImage m_logoOriginale;
    wxImage m_logoRescaled; 
    wxBitmap m_logoBitmap;
    
    
    float m_x, m_y;
    int m_vX, m_vY;

    unsigned char m_attualeR, m_attualeG, m_attualeB;

    void CambiaColoreLogo();
    void ApplicaColoreCorrente();
    
    void OnPanelPaint(wxPaintEvent& event) override;
    void OnTimerTick(wxTimerEvent& event);
    void OnSize(wxSizeEvent& event); 
};
