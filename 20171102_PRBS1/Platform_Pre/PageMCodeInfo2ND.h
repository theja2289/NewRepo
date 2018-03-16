#if !defined(AFX_PAGEMCODEINFO2ND_H__33ECAE59_43F7_44F9_8115_E09925CDFD6C__INCLUDED_)
#define AFX_PAGEMCODEINFO2ND_H__33ECAE59_43F7_44F9_8115_E09925CDFD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageMCodeInfo2ND.h : header file
//
#include "BtnEnh.h"
#include "DefSystem.h"
#include "MLCNetData.h"
/////////////////////////////////////////////////////////////////////////////
// CPageMCodeInfo2ND dialog
class MLCNet;
class MTrsAutoManager;

class CPageMCodeInfo2ND : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageMCodeInfo2ND)

private:
	HWND m_hAutoMainWnd;

	MLCNet*				m_plnkLCNet;
	MTrsAutoManager*	m_plnkAutoManager;

	CBtnEnh		m_lblWorkOrder[DEF_MAX_PRODUCT_PLAN];
	CBtnEnh		m_lblDeviceID[DEF_MAX_PRODUCT_PLAN];
	CBtnEnh		m_lblStep[DEF_MAX_PRODUCT_PLAN][DEF_MAX_TABFEEDER];
	CBtnEnh		m_lblKind[DEF_MAX_PRODUCT_PLAN][DEF_MAX_TABFEEDER];
	CBtnEnh		m_lblMCode[DEF_MAX_PRODUCT_PLAN][DEF_MAX_TABFEEDER][DEF_MAX_MCODE];

private:
	void clearDisplay();
	void updateDisplay();

	void materialCodeInfoRequest(int iPlanType, EMaterialStep eStep);
public:
	void SetAutoMainWnd(HWND hMainView);	
	void RenewMaterialCode();

// Construction
public:
	CPageMCodeInfo2ND();
	~CPageMCodeInfo2ND();

// Dialog Data
	//{{AFX_DATA(CPageMCodeInfo2ND)
	enum { IDD = IDD_PAGE_MCODE_INFO_2ND };
	CBtnEnh		m_btnRequestCurrentS;
	CBtnEnh		m_btnRequestCurrentG;
	CBtnEnh		m_btnRequestNextS;
	CBtnEnh		m_btnRequestNextG;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageMCodeInfo2ND)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageMCodeInfo2ND)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickRequestSCurrent();
	afx_msg void OnClickRequestGCurrent();
	afx_msg void OnClickRequestSNext();
	afx_msg void OnClickRequestGNext();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEMCODEINFO2ND_H__33ECAE59_43F7_44F9_8115_E09925CDFD6C__INCLUDED_)