// TortoiseSVN - a Windows shell extension for easy version control

// Copyright (C) 2003-2005 - Stefan Kueng

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#pragma once
#include "SVNPrompt.h"
#include "SVNRev.h"
#include "SVN.h"
#include "TSVNPath.h"

/**
 * \ingroup SVN
 * Provides methods to diff URL's and paths.
 *
 * Note: this class shows messageboxes for errors.
 */
class SVNDiff
{
public:
	SVNDiff(SVN * pSVN = NULL, HWND hWnd = NULL, CTSVNPathList * pTempFileList = NULL);
	~SVNDiff(void);

	/**
	 * Do the conflict-resolving 3-way merge on the specified file
	 */
	static bool StartConflictEditor(const CTSVNPath& conflictedFilePath);

	/**
	 * Diff a single file against its text-base
	 *\param filePath The file to diff
	 *\param temporaryFile If the function creates a temporary file, the name will be returned here
	 */
	bool DiffFileAgainstBase(const CTSVNPath& filePath, CTSVNPath& temporaryFile);

	/**
	 * Produces a unified diff of the \a url1 in \a rev1 and \a url2 in \a rev2 and shows
	 * it in the unified diff viewer.
	 * If \a peg revision isn't specified, then the following algorithm is used to find
	 * the peg revision:\n
	 * If \a url points to a local path, then WC is used as the peg revision, otherwise
	 * HEAD is used for the peg revision.
	 *
	 * Note: the peg revision is only used if \a url1 is the same as \a url2
	 */
	bool ShowUnifiedDiff(const CTSVNPath& url1, const SVNRev& rev1, const CTSVNPath& url2, const SVNRev& rev2, const SVNRev& peg = SVNRev());

	/**
	 * See ShowUnifiedDiff().
	 * Unlike ShowUnifiedDiff(), this method returns the path to the saved unified diff
	 * without starting the diff viewer.
	 */
	bool UnifiedDiff(CTSVNPath& tempfile, const CTSVNPath& url1, const SVNRev& rev1, const CTSVNPath& url2, const SVNRev& rev2, const SVNRev& peg = SVNRev());

	/**
	 * Compares two revisions of a path and shows them in a GUI.
	 *
	 * To compare one url in two revisions, pass the same url for \a url1 
	 * and \a url2.
	 * Note: if you pass two different urls, the \a peg revision is ignored.
	 *
	 * If \a url1 is a working copy path and \a rev1 is REV_WC, then \a rev2 is
	 * compared against the existing working copy.
	 *
	 * In case \a url1 is an URL and not a local path, then the file diff dialog
	 * is used to show the diff.
	 */
	bool ShowCompare(const CTSVNPath& url1, const SVNRev& rev1, 
					 const CTSVNPath& url2, const SVNRev& rev2, 
					 const SVNRev& peg = SVNRev(),
					 bool ignoreancestry = false, bool nodiffdeleted = false);

protected:
private:
	SVN *			m_pSVN;
	bool			m_bDeleteSVN;
	HWND			m_hWnd;
	CTSVNPathList * m_pTempFileList;
};
