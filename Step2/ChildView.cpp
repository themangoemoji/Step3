/**
 * \file ChildView.cpp
 *
 * \author Michael H. Wright
 */

// ChildView.cpp : implementation of the CChildView class

#include "stdafx.h"
#include "Step2.h"
#include "ChildView.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishDory.h"
#include "FishSparty.h"
#include "DecorTreasure.h"
#include "Fish.h"
#include "Item.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

// CChildView

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/** \brief Constructor */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

/** \brief Destructor */
CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
//	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_SPARTYFISH, &CChildView::OnAddfishSpartyfish)
	ON_COMMAND(ID_ADDFISH_DORYFISH, &CChildView::OnAddfishDoryfish)
	ON_COMMAND(ID_FILE_TRASHCAN, &CChildView::OnFileTrashcan)
	ON_COMMAND(ID_ADDDECOR_TREASURE, &CChildView::OnAdddecorTreasure)
	ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
	ON_COMMAND(ID_FILE_OPEN32777, &CChildView::OnFileOpen)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChildView message handlers

/**
 * \brief This function is called before the window is created.
 * \param cs A structure with the window creation parameters.
 * \returns TRUE
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

/** \brief Adds a Beta Fish to the awuarium at the initial location.
*/
void CChildView::OnAddfishBetafish()
{
	// To display the beta fish within the aquarium
	auto fish = make_shared<CFishBeta>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	// Redraws the display.
	Invalidate(); 
}

/** \brief Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGrabbedItem = mAquarium.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{
		mAquarium.MoveToFront(mGrabbedItem);
		mAquarium.Add(mGrabbedItem);
	}
}

/** \brief Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnLButtonDown(nFlags, point);

	if (mAquarium.HitTest(51, 70))
	{
		mAquarium.ActivateTrashcan();
		if (mAquarium.ActivateTrashcan())
		{
			mAquarium.MoveToFront(mGrabbedItem);
			Invalidate();
		}
	}
}

/** \brief Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x, point.y);
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
}

/**
* \brief Erase the background prior to drawing.
* \param pDC A device context to draw on
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// This disabled the default background erase
	return TRUE;
}


/** \brief This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// Get the size of the window
	CRect rect;
	GetClientRect(&rect);

	// Create a memory buffer
	Bitmap memory(rect.Width(), rect.Height(), PixelFormat32bppARGB);

	// And a graphics context for that buffer
	Graphics graphics(&memory);
	graphics.Clear(Color(0, 0, 0));

	/// Allows for graphics to be drawn for Aquarium
	mAquarium.OnDraw(&graphics);


	Graphics graphicsReal(dc.m_hDC);
	graphicsReal.DrawImage(&memory, 0, 0, rect.Width(), rect.Height());

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mAquarium.Update(elapsed);
}

/** \brief Adds a Sparty Fish to the awuarium at the initial location.
*/
void CChildView::OnAddfishSpartyfish()
{
	auto fish = make_shared<CFishSparty>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}


/** \brief Adds a Dory Fish to the awuarium at the initial location.
*/
void CChildView::OnAddfishDoryfish()
{
	auto fish = make_shared<CFishDory>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/** \brief Activates the trashcan, and redisplays the screen after deletion.
*/
void CChildView::OnFileTrashcan()
{
	/// Activate the trashcan
	mAquarium.ActivateTrashcan();
	Invalidate();
}


void CChildView::OnAdddecorTreasure()
{
	// TODO: Add your command handler code here
	auto decor = make_shared<CDecorTreasure>(&mAquarium);
	decor->SetLocation(InitialX, InitialY);
	mAquarium.Add(decor);
	Invalidate();
}


/**
* \brief Handler for the File/Save As menu option
*/
void CChildView::OnFileSaveas()
{
	CFileDialog dlg(false,  // false = Save dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		0,                  // Flags (none)
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");    // Filter          // 
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();

	mAquarium.Save(filename);
}

/** This function is called when an File Open menu item is selected.
*
* It loads the aquarium from a file.
* \param event An object that describes the event.
*/
void CChildView::OnFileOpen()
{
	CFileDialog dlg(true,  // true = Open dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		0,    // Flags
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");    // Filter
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();


	mAquarium.Load(filename);
	Invalidate();

}

/**
* \brief Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}
