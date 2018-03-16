/* Generated by Together */

#include "StdAfx.h"
#include "MRollerConveyor.h"
#include "IStatePanelAligner.h"
#include "IStatePanelTransfer.h"
#include "IIO.h"
#include "ICylinder.h"
#include "IInverter.h"
#include "DefPanelTransfer.h"

#include "common.h"

#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
#	include "MPreBonderData.h"
#	include "DefIOAddrPreBonder.h"
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
#	include "DefIOAddrAcf.h"
#	include "MAcfData.h"
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
#	include "DefIOAddrFinal.h"
#	include "MFinalData.h"
#endif

MRollerConveyor::MRollerConveyor()
{
	m_plnkIO = NULL;
	m_plnkInverter = NULL;
	m_plnkStopperUDCyl = NULL;
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_plnkPreBonderData = NULL;
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_plnkACFData = NULL;
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_plnkFinalData = NULL;
#endif
	m_usIAddrPanelDecelDetect = 0;
	m_usIAddrPanelStopDetect = 0;
	m_iRollerConveyorIndex = 0;
	m_dNormalSpeed = 0.0;
	m_dReducedSpeed = 0.0;
	m_dTransferSpeed = 0.0;
	m_dRunningSpeed = 0.0;
}

/** 
 * ������
 *
 * @param commonData : ObjectI�� Log�� ���� Component Common Data
 * @param listRefComponent : ������ Component ������ ����Ʈ
 * @param datComponent : RollerConveyor Data
 */
MRollerConveyor::MRollerConveyor(SCommonAttribute commonData, SRollerConveyorRefCompList listRefComponents, SRollerConveyorData datComponent)
: ICommon(commonData)
{
	//20081110 by kss
	// Data Assign
	int iResult = SetData(datComponent);
	if (iResult)
	{
		//SetErrorLevel(_T("ROLLER CONVEYOR creation"),2, __FILE__, __LINE__);
		//WriteErrorLog("MRollerConveyor() : SetData Error!");
	}

	// Component List Assign
	iResult	= AssignComponents(listRefComponents);
	if (iResult) 
	{
		//SetErrorLevel(_T("ROLLER CONVEYOR creation"),2, __FILE__, __LINE__);
		//WriteErrorLog("MRollerConveyor() : AssignComponent Error!");
	}

	m_dRunningSpeed = 0.0;
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_dNormalSpeed = m_plnkPreBonderData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
	m_dReducedSpeed = m_plnkPreBonderData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
	m_dTransferSpeed = m_plnkPreBonderData->m_rgdConveyorTransferSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_dNormalSpeed = m_plnkACFData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
	m_dReducedSpeed = m_plnkACFData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
	m_dTransferSpeed = m_plnkACFData->m_rgdConveyorTransferSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_dNormalSpeed = m_plnkFinalData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
	m_dReducedSpeed = m_plnkFinalData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
	m_dTransferSpeed = m_plnkFinalData->m_rgdConveyorTransferSpeed[m_iRollerConveyorIndex];
#endif

	if (IsInverterFault())
	{
		iResult = ResetInverterFault();
		if (iResult)
		{
			//SetErrorLevel(_T("ROLLER CONVEYOR creation"),2, __FILE__, __LINE__);
			//WriteErrorLog("MRollerConveyor() : Inverter Fault Clear Failed!");
		}

		Sleep(100);

		if (IsInverterFault())
		{
			//SetErrorLevel(_T("ROLLER CONVEYOR creation"),2, __FILE__, __LINE__);
			//WriteErrorLog("MRollerConveyor() : Inverter Fault!");
		}
	}

	if (FALSE == IsInverterReady())
	{
		iResult = ResetInverterFault();
		if (iResult)
		{
			//SetErrorLevel(_T("ROLLER CONVEYOR creation"),2, __FILE__, __LINE__);
			//WriteErrorLog("MRollerConveyor() : Inverter Fault Clear Failed!");
		}

		Sleep(100);

		if (FALSE == IsInverterReady())
		{
			//SetErrorLevel(_T("ROLLER CONVEYOR creation"),2, __FILE__, __LINE__);
			//WriteErrorLog("MRollerConveyor() : Inverter Not Ready!");
		}
	}
}

/**
 * �Ҹ���
 */
MRollerConveyor::~MRollerConveyor()
{
}

/************************************************************************/
/*        Component ���� ���� Interface                                 */
/************************************************************************/

/**
 * RollerConveyor�� Data Parameter�� �����Ѵ�. 
 *
 * @param	SRollerConveyorParam : ������ RollerConveyor Parameter
 * @return	int : (0 = Success, Error Code = �� ��)
 */
int MRollerConveyor::SetData(SRollerConveyorData datComponent)
{
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_plnkPreBonderData			= datComponent.m_plnkPreBonderData;
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_plnkACFData				= datComponent.m_plnkACFData;
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_plnkFinalData				= datComponent.m_plnkFinalData;
#endif
	m_usIAddrPanelDecelDetect	= datComponent.m_usIAddrPanelDecelDetect;
	m_usIAddrPanelStopDetect	= datComponent.m_usIAddrPanelStopDetect;
	m_iRollerConveyorIndex		= datComponent.m_iRollerConveyorIndex;

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

/**
 * RollerConveyor�� Component List�� �����Ѵ�.
 *
 * @param	SRollerConveyorRefCompList : ������ RollerConveyor Component List
 * @return	int : (0 = Success, Error Code = �� ��)
 */
int MRollerConveyor::AssignComponents(SRollerConveyorRefCompList RollerConveyorCompList)
{
	m_plnkIO			= RollerConveyorCompList.m_plnkIO;
	m_plnkInverter		= RollerConveyorCompList.m_plnkInverter;
	m_plnkStopperUDCyl	= RollerConveyorCompList.m_plnkStopperUDCyl;

	//20081110 by kss
	if(DEF_LOAD_CONVEYOR == GetInstanceNo())
	{
		m_plnkPanelPreAlignFBCyl = RollerConveyorCompList.m_plnkPanelPreAlignFBCyl;
	}

	//20081124 by kss
#ifdef DEF_PLATFORM_FINALBONDER_SYSTEM	
		if(DEF_OUT_CONVEYOR == GetInstanceNo())
		{
			m_plnkPanelPreAlignFBCyl = RollerConveyorCompList.m_plnkPanelPreAlignFBCyl;
		}	
#endif

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

/**
 * RollerConveyor�� State Ȯ���� Component List�� �����Ѵ�.
 *
 * @param	sCompList : ������ State Ȯ���� ���� Component List
 * @return	int : (0 = Success, Error Code = �� ��)
 */
int MRollerConveyor::AssignStateCheckComponents(SStateCheckCompListForRollerConveyor sCompList)
{
	m_plnkStatePanelAligner = sCompList.m_plnkStatePanelAligner;
	m_plnkStatePanelTransfer = sCompList.m_plnkStatePanelTransfer;

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::UpStopperUDCyl(BOOL bSkipSensor, BOOL bUseAuto)
{
	ASSERT(m_plnkStopperUDCyl != NULL);

	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = checkInterlockForMove(DEF_CONVEYOR_STOPPER_UP, bUseAuto);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Stopper Up] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	iResult = m_plnkStopperUDCyl->Up(bSkipSensor);
	if (iResult)
		return iResult;

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Stopper Up] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::DownStopperUDCyl(BOOL bSkipSensor, BOOL bUseAuto)
{
	ASSERT(m_plnkStopperUDCyl != NULL);

	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = checkInterlockForMove(DEF_CONVEYOR_STOPPER_DOWN, bUseAuto);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Stopper Down] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	iResult = m_plnkStopperUDCyl->Down(bSkipSensor);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Stopper Down] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

BOOL MRollerConveyor::IsUpStopperUDCyl(void)
{
	ASSERT(m_plnkStopperUDCyl != NULL);

	return m_plnkStopperUDCyl->IsUp();
}

BOOL MRollerConveyor::IsDownStopperUDCyl(void)
{
	ASSERT(m_plnkStopperUDCyl != NULL);

	return m_plnkStopperUDCyl->IsDown();
}

//20081110 by kss
//------------------------------------------------------------
int MRollerConveyor::ForwardPanelPreAlignFBCyl(BOOL bSkipSensor)
{
	ASSERT(m_plnkPanelPreAlignFBCyl != NULL);

	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

//	iResult = checkInterlockForMove(DEF_CONVEYOR_STOPPER_UP, bUseAuto);
//	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
//		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [PanelPreAligner Forward] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	iResult = m_plnkPanelPreAlignFBCyl->Front(bSkipSensor);
	if (iResult)
		return iResult;

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [PanelPreAligner Forward] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::BackwardPanelPreAlignFBCyl(BOOL bSkipSensor)
{
	ASSERT(m_plnkPanelPreAlignFBCyl != NULL);

	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

//	iResult = checkInterlockForMove(DEF_CONVEYOR_STOPPER_DOWN, bUseAuto);
//	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
//		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [PanelPreAligner Backward] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	iResult = m_plnkPanelPreAlignFBCyl->Back(bSkipSensor);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [PanelPreAligner Backward] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

BOOL MRollerConveyor::IsForwardPanelPreAlignFBCyl(void)
{
	ASSERT(m_plnkPanelPreAlignFBCyl != NULL);

	return m_plnkPanelPreAlignFBCyl->IsFront();
}

BOOL MRollerConveyor::IsBackwardPanelPreAlignFBCyl(void)
{
	ASSERT(m_plnkStopperUDCyl != NULL);

	return m_plnkPanelPreAlignFBCyl->IsBack();
}
//-----------------------------------------------------------------------------

int MRollerConveyor::MoveForward(BOOL bUseAuto)
{
	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = checkInterlockForMove(DEF_CONVEYOR_MOVE_FORWARD, bUseAuto);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Forward] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	double dNormalFreq;

	// �ӵ� ����
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_dNormalSpeed = m_plnkPreBonderData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_dNormalSpeed = m_plnkACFData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_dNormalSpeed = m_plnkFinalData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
#endif

	dNormalFreq = m_plnkInverter->CalculateSpeed2Freq(m_dNormalSpeed);
	iResult = m_plnkInverter->SetSpeed((unsigned short)(dNormalFreq*10), DEF_CONVEYOR_NORMAL_SPEED);	// ���ļ�*10
	if (iResult)
		return iResult;

	m_dRunningSpeed = m_dNormalSpeed;

	//���� ����
	iResult = m_plnkInverter->ForwardDirection();
	if (iResult)
		return iResult;

	iResult = m_plnkInverter->Start();
	if (iResult)
	{
		m_plnkInverter->Stop();
		return iResult;
	}

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Forward] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::MoveBackward(BOOL bUseAuto)
{
	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = checkInterlockForMove(DEF_CONVEYOR_MOVE_BACKWARD, bUseAuto);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Backward] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	double dNormalFreq;

	// �ӵ� ����
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_dNormalSpeed = m_plnkPreBonderData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_dNormalSpeed = m_plnkACFData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_dNormalSpeed = m_plnkFinalData->m_rgdConveyorNormalSpeed[m_iRollerConveyorIndex];
#endif

	dNormalFreq = m_plnkInverter->CalculateSpeed2Freq(m_dNormalSpeed);
	iResult = m_plnkInverter->SetSpeed((unsigned short)(dNormalFreq*10), DEF_CONVEYOR_NORMAL_SPEED);	// ���ļ�*10
	if (iResult)
		return iResult;

	m_dRunningSpeed = m_dNormalSpeed;

	//���� ����
	iResult = m_plnkInverter->BackwardDirection();
	if (iResult)
		return iResult;

	iResult = m_plnkInverter->Start();
	if (iResult)
	{
		m_plnkInverter->Stop();
		return iResult;
	}

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Backward] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::MoveForwardReducedSpeed(BOOL bUseAuto)
{
	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = checkInterlockForMove(DEF_CONVEYOR_MOVE_FORWARD, bUseAuto);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Forward Reduced Speed] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	double dReducedFreq;

	// �ӵ� ����
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_dReducedSpeed = m_plnkPreBonderData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_dReducedSpeed = m_plnkACFData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_dReducedSpeed = m_plnkFinalData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#endif

	dReducedFreq = m_plnkInverter->CalculateSpeed2Freq(m_dReducedSpeed);
	iResult = m_plnkInverter->SetSpeed((unsigned short)(dReducedFreq*10), DEF_CONVEYOR_REDUCED_SPEED);	// ���ļ�*10
	if (iResult)
		return iResult;

	m_dRunningSpeed = m_dReducedSpeed;

	//���� ����
	iResult = m_plnkInverter->ForwardDirection();
	if (iResult)
		return iResult;

	iResult = m_plnkInverter->Start();
	if (iResult)
	{
		m_plnkInverter->Stop();
		return iResult;
	}

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Forward Reduced Speed] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::MoveBackwardReducedSpeed(BOOL bUseAuto)
{
	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = checkInterlockForMove(DEF_CONVEYOR_MOVE_BACKWARD, bUseAuto);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Backward Reduced Speed] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	double dReducedFreq;

	// �ӵ� ����
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_dReducedSpeed = m_plnkPreBonderData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_dReducedSpeed = m_plnkACFData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_dReducedSpeed = m_plnkFinalData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#endif

	dReducedFreq = m_plnkInverter->CalculateSpeed2Freq(m_dReducedSpeed);
	iResult = m_plnkInverter->SetSpeed((unsigned short)(dReducedFreq*10), DEF_CONVEYOR_REDUCED_SPEED);	// ���ļ�*10
	if (iResult)
		return iResult;

	m_dRunningSpeed = m_dReducedSpeed;

	//���� ����
	iResult = m_plnkInverter->BackwardDirection();
	if (iResult)
		return iResult;

	iResult = m_plnkInverter->Start();
	if (iResult)
	{
		m_plnkInverter->Stop();
		return iResult;
	}

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Backward Reduced Speed] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::MoveForwardTransferSpeed(BOOL bUseAuto)
{
	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = checkInterlockForMove(DEF_CONVEYOR_MOVE_FORWARD, bUseAuto);
	if (iResult != ERR_ROLLERCONVEYOR_SUCCESS)
		return iResult;

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Forward Transfer Speed] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	double dTransferFreq;

	// �ӵ� ����
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_dTransferSpeed = m_plnkPreBonderData->m_rgdConveyorTransferSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_dTransferSpeed = m_plnkACFData->m_rgdConveyorTransferSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_dTransferSpeed = m_plnkFinalData->m_rgdConveyorTransferSpeed[m_iRollerConveyorIndex];
#endif

	dTransferFreq = m_plnkInverter->CalculateSpeed2Freq(m_dTransferSpeed);
	iResult = m_plnkInverter->SetSpeed((unsigned short)(dTransferFreq*10), DEF_CONVEYOR_TRANSFER_SPEED);	// ���ļ�*10
	if (iResult)
		return iResult;

	m_dRunningSpeed = m_dTransferSpeed;

	//���� ����
	iResult = m_plnkInverter->ForwardDirection();
	if (iResult)
		return iResult;

	iResult = m_plnkInverter->Start();
	if (iResult)
	{
		m_plnkInverter->Stop();
		return iResult;
	}

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Move Forward Transfer Speed] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::ReduceSpeed()
{
	ASSERT(m_plnkIO != NULL);

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Reduce Speed] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;
	double dReducedFreq;

	// �ӵ� ����
#if defined(DEF_PLATFORM_PREBONDER_SYSTEM)
	m_dReducedSpeed = m_plnkPreBonderData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_ARP_SYSTEM)
	m_dReducedSpeed = m_plnkACFData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#elif defined(DEF_PLATFORM_FINALBONDER_SYSTEM)
	m_dReducedSpeed = m_plnkFinalData->m_rgdConveyorReducedSpeed[m_iRollerConveyorIndex];
#endif

	dReducedFreq = m_plnkInverter->CalculateSpeed2Freq(m_dReducedSpeed);
	iResult = m_plnkInverter->SetSpeed((unsigned short)(dReducedFreq*10), DEF_CONVEYOR_REDUCED_SPEED);	// ���ļ�*10
	if (iResult)
	{
		m_plnkInverter->Stop();
		return iResult;
	}

	m_dRunningSpeed = m_dReducedSpeed;

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Reduce Speed] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

int MRollerConveyor::StopMoving()
{
	ASSERT(m_plnkIO != NULL);

	// jdy sesl
	char szLogMsg[200];

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Stop Moving] [Start]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = m_plnkInverter->Stop();
	if (iResult)
	{
		m_plnkInverter->Stop();
		return iResult;
	}

	memset(szLogMsg, 0, sizeof(szLogMsg));
	sprintf(szLogMsg, "[MRollerConveyor%d] [M] [Stop Moving] [End]", m_iInstanceNo + 1);
	WriteTactTimeLog(szLogMsg);

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

BOOL MRollerConveyor::IsInverterReady()
{
#ifdef SIMULATION
	return TRUE;
#endif

	BOOL bResult;

	bResult = m_plnkInverter->IsReady();

	return bResult;
}

BOOL MRollerConveyor::IsInverterFault()
{
#ifdef SIMULATION
	return FALSE;
#endif

	BOOL bResult;

	bResult = m_plnkInverter->IsFault();

	return bResult;
}

int MRollerConveyor::ResetInverterFault()
{
	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	iResult = m_plnkInverter->ClearFaults();
	if (iResult)
		return iResult;

	return ERR_ROLLERCONVEYOR_SUCCESS;
}

BOOL MRollerConveyor::IsPanelDecelDetected()
{
	ASSERT(m_plnkIO != NULL);

	return m_plnkIO->IsOn(m_usIAddrPanelDecelDetect);
}

BOOL MRollerConveyor::IsPanelStopDetected()
{
	ASSERT(m_plnkIO != NULL);

	return m_plnkIO->IsOn(m_usIAddrPanelStopDetect);
}

BOOL MRollerConveyor::IsPanelDetected()
{
	BOOL bResult1, bResult2;

	bResult1 = IsPanelDecelDetected();
	bResult2 = IsPanelStopDetected();

	return bResult1 || bResult2;
}

BOOL MRollerConveyor::IsInMovingForward(void)
{
	BOOL bResult1, bResult2, bResult3;

	bResult1 = m_plnkInverter->IsForwardDirectionCommand();
	bResult2 = m_plnkInverter->IsForwardDirectionActual();
	bResult3 = m_plnkInverter->IsActive();

	return bResult1 && bResult2 && bResult3;
}

BOOL MRollerConveyor::IsInMovingBackward(void)
{
	BOOL bResult1, bResult2, bResult3;

	bResult1 = m_plnkInverter->IsBackwardDirectionCommand();
	bResult2 = m_plnkInverter->IsBackwardDirectionActual();
	bResult3 = m_plnkInverter->IsActive();

	return bResult1 && bResult2 && bResult3;
}

BOOL MRollerConveyor::IsNormalSpeed(void)
{
	if (m_dRunningSpeed == m_dNormalSpeed)
		return TRUE;
	else
		return FALSE;
}

BOOL MRollerConveyor::IsReducedSpeed(void)
{
	if (m_dRunningSpeed == m_dReducedSpeed)
		return TRUE;
	else
		return FALSE;
}

BOOL MRollerConveyor::IsTransferSpeed(void)
{
	if (m_dRunningSpeed == m_dTransferSpeed)
		return TRUE;
	else
		return FALSE;
}

BOOL MRollerConveyor::IsStopMoving(void)
{
	BOOL bResult;

	bResult = m_plnkInverter->IsActive();

	return !bResult;
}

double MRollerConveyor::GetSpeed(int iSpeedType)
{
	if (iSpeedType == DEF_INVERTER_NORMAL_SPEED)
		return m_dNormalSpeed;
	else if (iSpeedType == DEF_INVERTER_REDUCED_SPEED)
		return m_dReducedSpeed;
	else // DEF_INVERTER_TRANSFER_SPEED
		return m_dTransferSpeed;
}

int MRollerConveyor::checkInterlockForMove(int Direction, BOOL bUseAuto)
{
	int iResult = ERR_ROLLERCONVEYOR_SUCCESS;

	if (FALSE == IsInverterReady())
	{
		iResult = ResetInverterFault();
		if (iResult)
			return iResult;

		Sleep(100);

		if (FALSE == IsInverterReady())
			// 226000 = Inverter�� Ready ���°� �ƴմϴ�.
			return generateErrorCode(226000);
	}

	// Load Conveyor
	if (DEF_LOAD_CONVEYOR == m_iRollerConveyorIndex)
	{
		switch (Direction)
		{
		case DEF_CONVEYOR_MOVE_FORWARD:
			// hongju ����....���� �϶��� Interlock
			if (FALSE == bUseAuto)
			{
				if (FALSE == m_plnkStatePanelTransfer->IsDownPickUpUDCyl())
					//	226003 = Panel Tansfer�� Down ���°� �ƴմϴ�.
					return generateErrorCode(226003);
				
#if ( defined(DEF_MECH_VERSION3) &&  defined(DEF_PLATFORM_ARP_SYSTEM) && defined(DEF_GATE_SYSTEM) )
				if (FALSE == m_plnkIO->IsOn(IN_PANEL_PUSHER_REAR1_UP) 
					|| FALSE == m_plnkIO->IsOn(IN_PANEL_PUSHER_REAR2_UP))
				{
					// 210114 = �̵� �Ұ�. [Pusher Down ������.]
					SetErrorLevel(_T("PANEL ALIGNER check Interlock for XYT"),2, __FILE__, __LINE__);
					return generateErrorCode(210114);
				}
# endif // ACF, GATE System

			}
			
			break;
			
		case DEF_CONVEYOR_MOVE_BACKWARD:
			break;
			
		case DEF_CONVEYOR_STOPPER_UP:
			if (m_plnkStatePanelTransfer->IsPanelAbsorbed() && 
				!m_plnkStatePanelTransfer->IsInXPos(DEF_PANEL_TRANSFER_UNLOAD_POS))
				//Load Conveyor Stopper����� Panel Transfer�� Panel�������¿��� Unloading��ġ�� ���� �ʽ��ϴ�.
				return generateErrorCode(226001);				
			
			// hongju_20090731 : ACF Source�� ��� �ڵ���ü�� Carrier�� ���� ������ �� �� ����..
			if (TRUE == IsPanelDetected())
			{
#if ( defined(DEF_PLATFORM_ARP_SYSTEM) && defined(DEF_GATE_SYSTEM) )
				Sleep(500);
#endif
				Sleep(100);
				if (TRUE == IsPanelDetected())
					// 226002 = Stopper Up �Ұ�. [Conveyor �� Panel ������.]
					return generateErrorCode(226002);
			}
			break;
			
		case DEF_CONVEYOR_STOPPER_DOWN:
			break;
			
		default :
			break;
		}
	}
	// Unload Conveyor
	else if (DEF_UNLOAD_CONVEYOR == m_iRollerConveyorIndex)
	{
		switch (Direction)
		{
		case DEF_CONVEYOR_MOVE_FORWARD:
			break;

		case DEF_CONVEYOR_MOVE_BACKWARD:
			break;

		case DEF_CONVEYOR_STOPPER_UP:
			break;

		case DEF_CONVEYOR_STOPPER_DOWN:
			break;

		default :
			break;
		}
	}
	// Out Conveyor
	else //if (DEF_OUT_CONVEYOR == m_iRollerConveyorIndex)
	{
		switch (Direction)
		{
		case DEF_CONVEYOR_MOVE_FORWARD:
			break;

		case DEF_CONVEYOR_MOVE_BACKWARD:
			break;

		case DEF_CONVEYOR_STOPPER_UP:
			break;

		case DEF_CONVEYOR_STOPPER_DOWN:
			break;

		default :
			break;
		}
	}

	return ERR_ROLLERCONVEYOR_SUCCESS;
}
