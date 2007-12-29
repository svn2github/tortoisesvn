// LogCacheStatisticsDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "TortoiseProc.h"
#include "LogCacheStatisticsDlg.h"
#include "LogCacheStatistics.h"
#include "RepositoryInfo.h"
#include "SVN.h"

// CLogCacheStatisticsDlg-Dialogfeld

IMPLEMENT_DYNAMIC(CLogCacheStatisticsDlg, CDialog)

CLogCacheStatisticsDlg::CLogCacheStatisticsDlg 
    ( const LogCache::CLogCacheStatisticsData& data)
	: CDialog(CLogCacheStatisticsDlg::IDD, NULL)
{
    sizeRAM = ToString (data.ramSize / 1024);
    sizeDisk = ToString (data.fileSize / 1024);

    switch (data.connectionState)
    {
    case LogCache::CRepositoryInfo::online:
        connectionState.LoadString (IDS_CONNECTIONSTATE_ONLINE);
        break;
    case LogCache::CRepositoryInfo::tempOffline:
        connectionState.LoadString (IDS_CONNECTIONSTATE_TEMPOFFLINE);
        break;
    case LogCache::CRepositoryInfo::offline:
        connectionState.LoadString (IDS_CONNECTIONSTATE_OFFLINE);
        break;
    }

    lastRead = DateToString (data.lastReadAccess);
    lastWrite = DateToString (data.lastWriteAccess);
    lastHeadUpdate = DateToString (data.headTimeStamp);

    authors = ToString (data.authorCount);
    paths = ToString (data.pathCount);
	pathElements = ToString (data.pathElementCount);
    skipRanges = ToString (data.skipDeltaCount);
    wordTokens = ToString (data.wordTokenCount);
    pairTokens = ToString (data.pairTokenCount);
    textSize = ToString (data.textSize);
	uncompressedSize = ToString (data.uncompressedSize);

    maxRevision = ToString (data.maxRevision);
    revisionCount = ToString (data.revisionCount);

    changesTotal = ToString (data.changesCount);
    changedRevisions = ToString (data.changesRevisionCount);
    changesMissing = ToString (data.changesMissingRevisionCount);
    mergesTotal = ToString (data.mergeInfoCount);
    mergesRevisions = ToString (data.mergeInfoRevisionCount);
    mergesMissing = ToString (data.mergeInfoMissingRevisionCount);
    userRevpropsTotal = ToString (data.userRevPropCount);
    userRevpropsRevisions = ToString (data.userRevPropRevisionCount);
    userRevpropsMissing = ToString (data.userRevPropMissingRevisionCount);
}

CLogCacheStatisticsDlg::~CLogCacheStatisticsDlg()
{
}

void CLogCacheStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SIZERAM, sizeRAM);
    DDX_Text(pDX, IDC_SIZEDISK, sizeDisk);
    DDX_Text(pDX, IDC_CONNECTIONSTATE, connectionState);
    DDX_Text(pDX, IDC_LASTREAD, lastRead);
    DDX_Text(pDX, IDC_LASTWRITE, lastWrite);
    DDX_Text(pDX, IDC_LASTHEADUPDATE, lastHeadUpdate);
    DDX_Text(pDX, IDC_AUTHORS, authors);
    DDX_Text(pDX, IDC_PATHELEMENTS, pathElements);
    DDX_Text(pDX, IDC_PATHS, paths);
    DDX_Text(pDX, IDC_SKIPRANGES, skipRanges);
    DDX_Text(pDX, IDC_WORDTOKENS, wordTokens);
    DDX_Text(pDX, IDC_PAIRTOKENS, pairTokens);
    DDX_Text(pDX, IDC_TEXTSIZE, textSize);
    DDX_Text(pDX, IDC_UNCOMPRESSEDSIZE, uncompressedSize);
    DDX_Text(pDX, IDC_MAXREVISION, maxRevision);
    DDX_Text(pDX, IDC_REVISIONCOUNT, revisionCount);
    DDX_Text(pDX, IDC_CHANGESTOTAL, changesTotal);
    DDX_Text(pDX, IDC_CHANGEDREVISIONS, changedRevisions);
    DDX_Text(pDX, IDC_CHANGESMISSING, changesMissing);
    DDX_Text(pDX, IDC_MERGESTOTAL, mergesTotal);
    DDX_Text(pDX, IDC_MERGESREVISIONS, mergesRevisions);
    DDX_Text(pDX, IDC_MERGESMISSING, mergesMissing);
    DDX_Text(pDX, IDC_USERREVPROPSTOTAL, userRevpropsTotal);
    DDX_Text(pDX, IDC_USERREVPROPSREVISISONS, userRevpropsRevisions);
    DDX_Text(pDX, IDC_USERREVPROPSMISSING, userRevpropsMissing);
}


BEGIN_MESSAGE_MAP(CLogCacheStatisticsDlg, CDialog)
END_MESSAGE_MAP()

CString CLogCacheStatisticsDlg::DateToString (__time64_t time)
{
    // transform to 1-second base

    __time64_t systime = time / 1000000L;
    __time64_t now = CTime::GetCurrentTime().GetTime();

    // return time when younger than 1 day
    // return date otherwise

    return (now - systime >= 0) && (now - systime < 86400)
        ? SVN::formatTime (time)
        : SVN::formatDate (time);
}

CString CLogCacheStatisticsDlg::ToString (__int64 value)
{
    TCHAR buffer[20];
    _i64tot_s (value, buffer, sizeof (buffer) / sizeof (TCHAR), 10); 
    return buffer;
}