#pragma once

struct TSVNCacheResponse;
#define CACHETIMEOUT	600000
extern DWORD cachetimeout;

class CStatusCacheEntry
{
public:
	CStatusCacheEntry();
	CStatusCacheEntry(const svn_wc_status2_t* pSVNStatus, __int64 lastWriteTime, bool bReadOnly);
	bool HasExpired(long now) const;
	void BuildCacheResponse(TSVNCacheResponse& response, DWORD& responseLength) const;
	bool IsVersioned() const;
	bool DoesFileTimeMatch(__int64 testTime) const;
	bool ForceStatus(svn_wc_status_kind forcedStatus);
	svn_wc_status_kind GetEffectiveStatus() const { return m_highestPriorityLocalStatus; }
	void SetStatus(const svn_wc_status2_t* pSVNStatus);
	bool HasBeenSet() const;
	bool IsDirectory() const {return m_kind == svn_node_dir;}
	bool SaveToDisk(HANDLE hFile);
	bool LoadFromDisk(HANDLE hFile);
private:
	void SetAsUnversioned();

private:
	long				m_discardAtTime;
	svn_wc_status_kind	m_highestPriorityLocalStatus;
	svn_wc_status2_t		m_svnStatus;
	__int64				m_lastWriteTime;
	bool				m_bSet;
	svn_node_kind_t		m_kind;
	bool				m_bReadOnly;

	// Values copied from the 'entries' structure
	bool				m_bSVNEntryFieldSet;
	CStringA			m_sUrl;
	CStringA			m_sOwner;
	CStringA			m_sAuthor;
	svn_revnum_t		m_commitRevision;

//	friend class CSVNStatusCache;
};
