#include "MyPanelImpl.h"
#include <wx/image.h>
#include <wx/dcbuffer.h>
#include <wx/sizer.h>
#include <ctime>

MyPanelImpl::MyPanelImpl(wxWindow* parent) 
    : m_panelAnimazione(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize) 
{
    srand(time(NULL));
    wxInitAllImageHandlers();
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    if (!m_logoOriginale.LoadFile("logo.png", wxBITMAP_TYPE_PNG)) {
        m_logoOriginale.Create(150, 70);
        m_logoOriginale.SetRGB(wxRect(0, 0, 150, 70), 255, 255, 255);
    }
    
    
    m_attualeR = 255; m_attualeG = 255; m_attualeB = 255;

    
    m_logoRescaled = m_logoOriginale.Copy();
    m_logoRescaled.Rescale(150, 70, wxIMAGE_QUALITY_HIGH);
    ApplicaColoreCorrente(); 

    m_x = 0; m_y = 0;
    m_vX = 2; m_vY = 2;

    this->Bind(wxEVT_PAINT, &MyPanelImpl::OnPanelPaint, this);
    this->Bind(wxEVT_SIZE, &MyPanelImpl::OnSize, this);
    m_timer.Bind(wxEVT_TIMER, &MyPanelImpl::OnTimerTick, this);
    m_timer.Start(16); 
}


void MyPanelImpl::CambiaColoreLogo() {
    m_attualeR = rand() % 200 + 55;
    m_attualeG = rand() % 200 + 55;
    m_attualeB = rand() % 200 + 55;
    ApplicaColoreCorrente();
}


void MyPanelImpl::ApplicaColoreCorrente() {
    if (!m_logoRescaled.IsOk()) return;
    wxImage img = m_logoRescaled.Copy();
    unsigned char* data = img.GetData();
    int numPixels = img.GetWidth() * img.GetHeight();
    for (int i = 0; i < numPixels * 3; i += 3) {
        if (data[i] > 0 || data[i+1] > 0 || data[i+2] > 0) {
            data[i] = m_attualeR; data[i+1] = m_attualeG; data[i+2] = m_attualeB;
        }
    }
    m_logoBitmap = wxBitmap(img);
}

void MyPanelImpl::OnSize(wxSizeEvent& event) {
    wxSize size = GetClientSize();
    if (size.x < 50 || size.y < 50) { event.Skip(); return; }

    int nuovaLarghezza = size.x * 0.20; 
    if (nuovaLarghezza < 50) nuovaLarghezza = 50;
    int nuovaAltezza = m_logoOriginale.GetHeight() * nuovaLarghezza / m_logoOriginale.GetWidth();

    
    if (!m_logoBitmap.IsOk() || m_logoBitmap.GetWidth() != nuovaLarghezza) {
        m_logoRescaled = m_logoOriginale.Copy();
        m_logoRescaled.Rescale(nuovaLarghezza, nuovaAltezza, wxIMAGE_QUALITY_FAST); 
        ApplicaColoreCorrente(); // Mantiene il colore vecchio
    }

    if (m_x + m_logoBitmap.GetWidth() > size.x) m_x = size.x - m_logoBitmap.GetWidth();
    if (m_y + m_logoBitmap.GetHeight() > size.y) m_y = size.y - m_logoBitmap.GetHeight();
    
    event.Skip();
}

void MyPanelImpl::OnTimerTick(wxTimerEvent& event) {
    m_x += m_vX;
    m_y += m_vY;
    wxSize size = this->GetClientSize();

    bool rimbalzo = false;
    if (m_x <= 0) { m_x = 0; m_vX = abs(m_vX); rimbalzo = true; } 
    else if (m_x + m_logoBitmap.GetWidth() >= size.x) { m_x = size.x - m_logoBitmap.GetWidth(); m_vX = -abs(m_vX); rimbalzo = true; }

    if (m_y <= 0) { m_y = 0; m_vY = abs(m_vY); rimbalzo = true; } 
    else if (m_y + m_logoBitmap.GetHeight() >= size.y) { m_y = size.y - m_logoBitmap.GetHeight(); m_vY = -abs(m_vY); rimbalzo = true; }

    if (rimbalzo) CambiaColoreLogo();
    Refresh(false);
}

void MyPanelImpl::OnPanelPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();
    if (m_logoBitmap.IsOk()) dc.DrawBitmap(m_logoBitmap, (int)m_x, (int)m_y, true);
}
