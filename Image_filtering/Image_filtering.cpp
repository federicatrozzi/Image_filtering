// Image_filtering.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include <wx\wxprec.h>
#include <wx\wx.h>
#include "wxImagePanel.h"
#include <wx\sizer.h>
#include <windows.h>
#include <string.h>
#include <iostream>
#include "util.h"
#include "edges.h"

using namespace std;
using namespace cv;

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
	
};
class MyFrame : public wxFrame
{
public:
	MyFrame();
	wxStaticBitmap *jpeg_img;
	Mat imcv1;
private:
	void OnEdges_canny(wxCommandEvent& event);
	void OnEdges_sobel(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};
enum
{
	ID_Edges_Canny = 1,
	ID_Edges_Sobel = 2
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}

MyFrame::MyFrame()
	: wxFrame(NULL, wxID_ANY, "Filtraggio spaziale", wxPoint(50, 50), wxSize(800, 600))
{
	// Inizializza handler delle immagini in wx/image.h
	wxInitAllImageHandlers();

	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Edges_Canny, "&Estrazione bordi Canny\tCtrl-C",
		"Help string shown in status bar for this menu item");
	menuFile->Append(ID_Edges_Sobel, "&Estrazione bordi Sobel\tCtrl-S",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	CreateStatusBar();

	wxFileDialog *OpenDialog = new wxFileDialog(this, _("Scegli un file da aprire"), wxEmptyString, wxEmptyString, _(" Image files(*.jpg) | *.jpg"), wxFD_OPEN, wxDefaultPosition);
	wxString Currentpath = "";
	// Crea la finestra di scelta dei file da aprire
	if (OpenDialog->ShowModal() == wxID_OK) // se l'utente non cancella l'azione
	{
		Currentpath = OpenDialog->GetPath();
		//crea il pannello immagine ridimensionabile
		//wxImagePanel * drawPane;
		//drawPane = new wxImagePanel(this, Currentpath, wxBITMAP_TYPE_JPEG);
	}
	Centre();

	jpeg_img = new wxStaticBitmap(this, wxID_ANY, wxBitmap(Currentpath,
		wxBITMAP_TYPE_JPEG), wxPoint(256, 0), wxSize(512, 512));

	//From opencv to wx
	imcv1 = imread(string(Currentpath), IMREAD_UNCHANGED);
	//string str = "Channels:" + to_string(imcv1.channels());
	//putText(imcv1, str, Point(100, 100), FONT_HERSHEY_PLAIN, 4.0, CV_RGB(128, 0, 128), 4.0);
	wxBitmap imwx1 = wx_from_mat(imcv1);
	jpeg_img->SetBitmap(imwx1);

	SetStatusText("Benvenuti!");
	Bind(wxEVT_MENU, &MyFrame::OnEdges_canny, this, ID_Edges_Canny);
	Bind(wxEVT_MENU, &MyFrame::OnEdges_sobel, this, ID_Edges_Sobel);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets Hello World example",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnEdges_canny(wxCommandEvent& event)
{

	Edges edges_calc(imcv1,3,1);
	Mat out= edges_calc.getOutImage();

	wxBitmap imwxOut = wx_from_mat(out);
	jpeg_img->SetBitmap(imwxOut);

}

void MyFrame::OnEdges_sobel(wxCommandEvent& event)
{

	Edges edges_calc(imcv1, 3,2);
	Mat out = edges_calc.getOutImage();

	wxBitmap imwxOut = wx_from_mat(out);
	jpeg_img->SetBitmap(imwxOut);

}

