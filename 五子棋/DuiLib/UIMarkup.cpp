#include "StdAfx.h"
#include "XUnZip.h"

#define MAX_FILE_SIZE (4*1024*1024)		// 4G

namespace DuiLib {
///////////////////////////////////////////////////////////////////////////////////////

CMarkupNode::CMarkupNode() :
m_pOwner(NULL),
m_iPos(0),
m_nAttributes(0)
{
}

CMarkupNode::CMarkupNode(CMarkup* pOwner, int iPos):
m_pOwner(pOwner),
m_iPos(iPos),
m_nAttributes(0)
{
}

CMarkupNode CMarkupNode::GetSibling()
{
	if( NULL == m_pOwner )
	{
		return CMarkupNode();
	}

	ULONG iPos = m_pOwner->m_pElements[m_iPos].iNext;
	if( iPos == 0 )
	{
		return CMarkupNode();
	}

	return CMarkupNode(m_pOwner, iPos);
}

bool CMarkupNode::HasSiblings() const
{
	if( NULL == m_pOwner )
	{
		return false;
	}

	ULONG iPos = m_pOwner->m_pElements[m_iPos].iNext;
	return (iPos > 0);
}

CMarkupNode CMarkupNode::GetChild()
{
	if( NULL == m_pOwner )
	{
		return CMarkupNode();
	}

	ULONG iPos = m_pOwner->m_pElements[m_iPos].iChild;
	if( iPos == 0 )
	{
		return CMarkupNode();
	}

	return CMarkupNode(m_pOwner, iPos);
}

CMarkupNode CMarkupNode::GetChild(LPCTSTR pstrName)
{
	if( NULL == m_pOwner )
	{
		return CMarkupNode();
	}

	ULONG iPos = m_pOwner->m_pElements[m_iPos].iChild;
	while( 0 != iPos )
	{
		if( 0 == _tcscmp(m_pOwner->m_pstrXML + m_pOwner->m_pElements[iPos].iStart, pstrName) )
		{
			return CMarkupNode(m_pOwner, iPos);
		}
		iPos = m_pOwner->m_pElements[iPos].iNext;
	}
	return CMarkupNode();
}

bool CMarkupNode::HasChildren() const
{
	if( NULL == m_pOwner )
	{
		return false;
	}

	ULONG iPos = m_pOwner->m_pElements[m_iPos].iChild;
	return (iPos > 0);
}

CMarkupNode CMarkupNode::GetParent()
{
	if( NULL == m_pOwner )
	{
		return CMarkupNode();
	}

	ULONG iPos = m_pOwner->m_pElements[m_iPos].iParent;
	if( iPos == 0 )
	{
		return CMarkupNode();
	}

	return CMarkupNode(m_pOwner, iPos);
}

bool CMarkupNode::IsValid() const
{
	if ( NULL == m_pOwner )
	{
		return false;
	}
	return true;
}

LPCTSTR CMarkupNode::GetName() const
{
	if ( NULL == m_pOwner )
	{
		return NULL;
	}
	return m_pOwner->m_pstrXML + m_pOwner->m_pElements[m_iPos].iStart;
}

LPCTSTR CMarkupNode::GetValue() const
{
	if ( NULL == m_pOwner )
	{
		return NULL;
	}
	return m_pOwner->m_pstrXML + m_pOwner->m_pElements[m_iPos].iData;
}

LPCTSTR CMarkupNode::GetAttributeName(int iIndex)
{
	if ( NULL == m_pOwner )
	{
		return NULL;
	}
	if( 0 == m_nAttributes )
	{
		_MapAttributes();
	}
	if( iIndex < 0 || iIndex >= m_nAttributes )
	{
		return _T("");
	}

	return m_pOwner->m_pstrXML + m_aAttributes[iIndex].iName;
}

LPCTSTR CMarkupNode::GetAttributeValue(int iIndex)
{
	if ( NULL == m_pOwner )
	{
		return NULL;
	}
	if( 0 == m_nAttributes )
	{
		_MapAttributes();
	}
	if( iIndex < 0 || iIndex >= m_nAttributes )
	{
		return _T("");
	}

	return m_pOwner->m_pstrXML + m_aAttributes[iIndex].iValue;
}

LPCTSTR CMarkupNode::GetAttributeValue(LPCTSTR pstrName)
{
	if ( NULL == m_pOwner )
	{
		return NULL;
	}
	if( 0 == m_nAttributes )
	{
		_MapAttributes();
	}

	for( int i = 0; i < m_nAttributes; i++ )
	{
		if( 0 == _tcscmp(m_pOwner->m_pstrXML + m_aAttributes[i].iName, pstrName) )
		{
			return m_pOwner->m_pstrXML + m_aAttributes[i].iValue;
		}
	}
	return _T("");
}

bool CMarkupNode::GetAttributeValue(int iIndex, LPTSTR pstrValue, SIZE_T cchMax)
{
	if ( NULL == m_pOwner )
	{
		return false;
	}
	if( 0 == m_nAttributes )
	{
		_MapAttributes();
	}
	if( iIndex < 0 || iIndex >= m_nAttributes )
	{
		return false;
	}

	_tcsncpy(pstrValue, m_pOwner->m_pstrXML + m_aAttributes[iIndex].iValue, cchMax);
	return true;
}

bool CMarkupNode::GetAttributeValue(LPCTSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax)
{
	if ( NULL == m_pOwner )
	{
		return false;
	}
	if( 0 == m_nAttributes )
	{
		_MapAttributes();
	}

	for( int i = 0; i < m_nAttributes; i++ )
	{
		if( 0 == _tcscmp(m_pOwner->m_pstrXML + m_aAttributes[i].iName, pstrName) )
		{
			_tcsncpy(pstrValue, m_pOwner->m_pstrXML + m_aAttributes[i].iValue, cchMax);
			return true;
		}
	}
	return false;
}

int CMarkupNode::GetAttributeCount()
{
	if ( NULL == m_pOwner )
	{
		return 0;
	}
	if( 0 == m_nAttributes )
	{
		_MapAttributes();
	}

	return m_nAttributes;
}

bool CMarkupNode::HasAttributes()
{
	if ( NULL == m_pOwner )
	{
		return false;
	}
	if( 0 == m_nAttributes )
	{
		_MapAttributes();
	}

	return (m_nAttributes > 0);
}

bool CMarkupNode::HasAttribute(LPCTSTR pstrName)
{
	if ( NULL == m_pOwner )
	{
		return false;
	}
	if( 0 == m_nAttributes )
	{
		_MapAttributes();
	}

	for( int i = 0; i < m_nAttributes; i++ )
	{
		if( 0 == _tcscmp(m_pOwner->m_pstrXML + m_aAttributes[i].iName, pstrName) )
		{
			return true;
		}
	}
	return false;
}

void CMarkupNode::_MapAttributes()
{
	m_nAttributes = 0;
	LPCTSTR pstr = m_pOwner->m_pstrXML + m_pOwner->m_pElements[m_iPos].iStart;
	LPCTSTR pstrEnd = m_pOwner->m_pstrXML + m_pOwner->m_pElements[m_iPos].iData;
	pstr += _tcslen(pstr) + 1;
	while( pstr < pstrEnd )
	{
		m_pOwner->_SkipWhitespace(pstr);
		m_aAttributes[m_nAttributes].iName = pstr - m_pOwner->m_pstrXML;
		pstr += _tcslen(pstr) + 1;
		m_pOwner->_SkipWhitespace(pstr);
		if( *pstr++ != _T('\"') )
		{
			return;
		}
		/*if( *pstr != _T('\"') )
		{
			pstr = ::CharNext(pstr); 
			return; 
		}*/
		m_aAttributes[m_nAttributes++].iValue = pstr - m_pOwner->m_pstrXML;
		if( m_nAttributes >= MAX_XML_ATTRIBUTES )
		{
			return;
		}
		pstr += _tcslen(pstr) + 1;
	}
}


///////////////////////////////////////////////////////////////////////////////////////
//
//
//

CMarkup::CMarkup(LPCTSTR pstrXML)
{
	m_pstrXML = NULL;
	m_pElements = NULL;
	m_nElements = 0;
	m_bPreserveWhitespace = true;
	if( pstrXML != NULL )
	{
		Load(pstrXML);
	}
}

CMarkup::~CMarkup()
{
	Release();
}

bool CMarkup::IsValid() const
{
	if ( NULL == m_pElements )
	{
		return false;
	}
	return true;
}

void CMarkup::SetPreserveWhitespace(bool bPreserve)
{
	m_bPreserveWhitespace = bPreserve;
}

bool CMarkup::Load(LPCTSTR pstrXML)
{
	Release();
	SIZE_T cchLen = _tcslen(pstrXML) + 1;
	m_pstrXML = static_cast<LPTSTR>(malloc(cchLen * sizeof(TCHAR)));
	::CopyMemory(m_pstrXML, pstrXML, cchLen * sizeof(TCHAR));
	bool bRes = _Parse();
	if( !bRes )
	{
		Release();
	}
	return bRes;
}

bool CMarkup::LoadFromMem(BYTE* pByte, DWORD dwSize, int encoding)
{
#ifdef _UNICODE
	if (encoding == XMLFILE_ENCODING_UTF8)
	{
		if( dwSize >= 3 && pByte[0] == 0xEF && pByte[1] == 0xBB && pByte[2] == 0xBF ) 
		{
			pByte += 3;
			dwSize -= 3;
		}
		DWORD nWide = ::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pByte, dwSize, NULL, 0 );

		m_pstrXML = static_cast<LPTSTR>(malloc((nWide + 1)*sizeof(TCHAR)));
		::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pByte, dwSize, m_pstrXML, nWide );
		m_pstrXML[nWide] = _T('\0');
	}
	else if (encoding == XMLFILE_ENCODING_ASNI)
	{
		DWORD nWide = ::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)pByte, dwSize, NULL, 0 );

		m_pstrXML = static_cast<LPTSTR>(malloc((nWide + 1)*sizeof(TCHAR)));
		::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)pByte, dwSize, m_pstrXML, nWide );
		m_pstrXML[nWide] = _T('\0');
	}
	else
	{
		if ( dwSize >= 2 && ( ( pByte[0] == 0xFE && pByte[1] == 0xFF ) || ( pByte[0] == 0xFF && pByte[1] == 0xFE ) ) )
		{
			dwSize = dwSize / 2 - 1;

			if ( pByte[0] == 0xFE && pByte[1] == 0xFF )
			{
				pByte += 2;

				for ( DWORD nSwap = 0 ; nSwap < dwSize ; nSwap ++ )
				{
					register CHAR nTemp = pByte[ ( nSwap << 1 ) + 0 ];
					pByte[ ( nSwap << 1 ) + 0 ] = pByte[ ( nSwap << 1 ) + 1 ];
					pByte[ ( nSwap << 1 ) + 1 ] = nTemp;
				}
			}
			else
			{
				pByte += 2;
			}

			m_pstrXML = static_cast<LPTSTR>(malloc((dwSize + 1)*sizeof(TCHAR)));
			::CopyMemory( m_pstrXML, pByte, dwSize * sizeof(TCHAR) );
			m_pstrXML[dwSize] = _T('\0');

			pByte -= 2;
		}
	}
#else // !_UNICODE
	if (encoding == XMLFILE_ENCODING_UTF8)
	{
		if( dwSize >= 3 && pByte[0] == 0xEF && pByte[1] == 0xBB && pByte[2] == 0xBF ) 
		{
			pByte += 3;
			dwSize -= 3;
		}
		DWORD nWide = ::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pByte, dwSize, NULL, 0 );

		LPWSTR w_str = static_cast<LPWSTR>(malloc((nWide + 1)*sizeof(WCHAR)));
		::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pByte, dwSize, w_str, nWide );
		w_str[nWide] = L'\0';

		DWORD wide = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)w_str, nWide, NULL, 0, NULL, NULL);

		m_pstrXML = static_cast<LPTSTR>(malloc((wide + 1)*sizeof(TCHAR)));
		::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)w_str, nWide, m_pstrXML, wide, NULL, NULL);
		m_pstrXML[wide] = _T('\0');

		free(w_str);
	}
	else if (encoding == XMLFILE_ENCODING_UNICODE)
	{
		if ( dwSize >= 2 && ( ( pByte[0] == 0xFE && pByte[1] == 0xFF ) || ( pByte[0] == 0xFF && pByte[1] == 0xFE ) ) )
		{
			dwSize = dwSize / 2 - 1;

			if ( pByte[0] == 0xFE && pByte[1] == 0xFF )
			{
				pByte += 2;

				for ( DWORD nSwap = 0 ; nSwap < dwSize ; nSwap ++ )
				{
					register CHAR nTemp = pByte[ ( nSwap << 1 ) + 0 ];
					pByte[ ( nSwap << 1 ) + 0 ] = pByte[ ( nSwap << 1 ) + 1 ];
					pByte[ ( nSwap << 1 ) + 1 ] = nTemp;
				}
			}
			else
			{
				pByte += 2;
			}

			DWORD nWide = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pByte, dwSize, NULL, 0, NULL, NULL);
			m_pstrXML = static_cast<LPTSTR>(malloc((nWide + 1)*sizeof(TCHAR)));
			::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)pByte, dwSize, m_pstrXML, nWide, NULL, NULL);
			m_pstrXML[nWide] = _T('\0');

			pByte -= 2;
		}
	}
	else
	{
		m_pstrXML = static_cast<LPTSTR>(malloc((dwSize + 1)*sizeof(TCHAR)));
		::CopyMemory( m_pstrXML, pByte, dwSize * sizeof(TCHAR) );
		m_pstrXML[dwSize] = _T('\0');
	}
#endif // _UNICODE

	bool bRes = _Parse();
	if( !bRes )
	{
		Release();
	}
	return bRes;
}

bool CMarkup::LoadFromFile(LPCTSTR pstrFilename, int encoding)
{
	Release();
	CStdString sFile = CPaintManagerUI::GetResourcePath();
	if( CPaintManagerUI::GetResourceZip().IsEmpty() )
	{
		sFile += pstrFilename;
		HANDLE hFile = ::CreateFile(sFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if( hFile == INVALID_HANDLE_VALUE )
		{
			return _Failed(_T("Error opening file"));
		}
		DWORD dwSize = ::GetFileSize(hFile, NULL);
		if( dwSize == 0 )
		{
			return _Failed(_T("File is empty"));
		}
		if ( dwSize > MAX_FILE_SIZE )
		{
			// > 4G
			return _Failed(_T("File too large"));
		}

		DWORD dwRead = 0;
		BYTE* pByte = new BYTE[ dwSize ];
		// 读取xml内容到pByte;
		::ReadFile( hFile, pByte, dwSize, &dwRead, NULL );
		::CloseHandle( hFile );

		if( dwRead != dwSize )
		{
			delete[] pByte;
			Release();
			return _Failed(_T("Could not read file"));
		}
		bool ret = LoadFromMem(pByte, dwSize, encoding);
		delete[] pByte;

		return ret;
	}
	else
	{
		sFile += CPaintManagerUI::GetResourceZip();
		HZIP hz = NULL;
		if( CPaintManagerUI::IsCachedResourceZip() )
		{
			hz = (HZIP)CPaintManagerUI::GetResourceZipHandle();
		}
		else
		{
			hz = OpenZip((void*)sFile.GetData(), 0, 2);
		}
		if( hz == NULL )
		{
			return _Failed(_T("Error opening zip file"));
		}

		ZIPENTRY ze; 
		int i; 
		if( FindZipItem(hz, pstrFilename, true, &i, &ze) != 0 )
		{
			return _Failed(_T("Could not find ziped file"));
		}
		DWORD dwSize = ze.unc_size;
		if( dwSize == 0 )
		{
			return _Failed(_T("File is empty"));
		}
		if ( dwSize > MAX_FILE_SIZE )
		{
			return _Failed(_T("File too large"));
		}

		BYTE* pByte = new BYTE[ dwSize ];
		int res = UnzipItem(hz, i, pByte, dwSize, 3);
		if( res != 0x00000000 && res != 0x00000600)
		{
			delete[] pByte;
			if( !CPaintManagerUI::IsCachedResourceZip() ) 
			{
				CloseZip(hz);
			}
			return _Failed(_T("Could not unzip file"));
		}
		if( !CPaintManagerUI::IsCachedResourceZip() )
		{
			CloseZip(hz);
		}
		bool ret = LoadFromMem(pByte, dwSize, encoding);
		delete[] pByte;

		return ret;
	}
}

void CMarkup::Release()
{
	if( m_pstrXML != NULL )
	{
		free(m_pstrXML);
		m_pstrXML = NULL;
	}
	if( m_pElements != NULL )
	{
		free(m_pElements);
		m_pElements = NULL;
	}

	m_nElements = 0;
}

void CMarkup::GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const
{
	_tcsncpy(pstrMessage, m_szErrorMsg, cchMax);
}

void CMarkup::GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const
{
	_tcsncpy(pstrSource, m_szErrorXML, cchMax);
}

CMarkupNode CMarkup::GetRoot()
{
	if( m_nElements == 0 )
	{
		return CMarkupNode();
	}
	return CMarkupNode(this, 1);
}

bool CMarkup::_Parse()
{
	_ReserveElement(); // Reserve index 0 for errors
	::ZeroMemory(m_szErrorMsg, sizeof(m_szErrorMsg));
	::ZeroMemory(m_szErrorXML, sizeof(m_szErrorXML));
	LPTSTR pstrXML = m_pstrXML;
	return _Parse(pstrXML, 0);
}

bool CMarkup::_Parse(LPTSTR& pstrText, ULONG iParent)
{
	_SkipWhitespace(pstrText);
	ULONG iPrevious = 0;
	for( ; ; ) 
	{
		if( *pstrText == _T('\0') && iParent <= 1 )
		{
			return true;
		}
		_SkipWhitespace(pstrText);
		if( *pstrText != _T('<') )
		{
			return _Failed(_T("Expected start tag"), pstrText);
		}
		if( pstrText[1] == _T('/') )
		{
			return true;
		}
		*pstrText++ = _T('\0');
		_SkipWhitespace(pstrText);
		// 跳过注释或处理指令;
		if( *pstrText == _T('!') || *pstrText == _T('?') )
		{
			TCHAR ch = *pstrText;
			if( *pstrText == _T('!') )
			{
				ch = _T('-');
			}
			while( *pstrText != _T('\0') && !(*pstrText == ch && *(pstrText + 1) == _T('>')) )
			{
				pstrText = ::CharNext(pstrText);
			}
			if( *pstrText != _T('\0') )
			{
				pstrText += 2;
			}
			_SkipWhitespace(pstrText);
			continue;
		}
		_SkipWhitespace(pstrText);
		// 填元素结构;
		XMLELEMENT* pEl = _ReserveElement();
		ULONG iPos = pEl - m_pElements;
		pEl->iStart = pstrText - m_pstrXML;
		pEl->iParent = iParent;
		pEl->iNext = pEl->iChild = 0;
		if( iPrevious != 0 )
		{
			m_pElements[iPrevious].iNext = iPos;
		}
		else if( iParent > 0 )
		{
			m_pElements[iParent].iChild = iPos;
		}
		iPrevious = iPos;
		// 解析名字;
		LPCTSTR pstrName = pstrText;
		_SkipIdentifier(pstrText);
		LPTSTR pstrNameEnd = pstrText;
		if( *pstrText == _T('\0') )
		{
			return _Failed(_T("Error parsing element name"), pstrText);
		}
		// 解析属性;
		if( !_ParseAttributes(pstrText) )
		{
			return false;
		}
		_SkipWhitespace(pstrText);
		if( pstrText[0] == _T('/') && pstrText[1] == _T('>') )
		{
			pEl->iData = pstrText - m_pstrXML;
			*pstrText = _T('\0');
			pstrText += 2;
		}
		else
		{
			if( *pstrText != _T('>') )
			{
				return _Failed(_T("Expected start-tag closing"), pstrText);
			}
			// 解析节点数据;
			pEl->iData = ++pstrText - m_pstrXML;
			LPTSTR pstrDest = pstrText;
			if( !_ParseData(pstrText, pstrDest, _T('<')) )
			{
				return false;
			}
			// 确定下一个元素的类型;
			if( *pstrText == _T('\0') && iParent <= 1 )
			{
				return true;
			}
			if( *pstrText != _T('<') )
			{
				return _Failed(_T("Expected end-tag start"), pstrText);
			}
			if( pstrText[0] == _T('<') && pstrText[1] != _T('/') ) 
			{
				if( !_Parse(pstrText, iPos) )
				{
					return false;
				}
			}
			if( pstrText[0] == _T('<') && pstrText[1] == _T('/') ) 
			{
				*pstrDest = _T('\0');
				*pstrText = _T('\0');
				pstrText += 2;
				_SkipWhitespace(pstrText);
				SIZE_T cchName = pstrNameEnd - pstrName;
				if( _tcsncmp(pstrText, pstrName, cchName) != 0 )
				{
					return _Failed(_T("Unmatched closing tag"), pstrText);
				}
				pstrText += cchName;
				_SkipWhitespace(pstrText);
				if( *pstrText++ != _T('>') )
				{
					return _Failed(_T("Unmatched closing tag"), pstrText);
				}
			}
		}
		*pstrNameEnd = _T('\0');
		_SkipWhitespace(pstrText);
	}
}

CMarkup::XMLELEMENT* CMarkup::_ReserveElement()
{
	if( m_nElements == 0 )
	{
		m_nReservedElements = 0;
	}
	if( m_nElements >= m_nReservedElements )
	{
		m_nReservedElements += (m_nReservedElements / 2) + 500;
		m_pElements = static_cast<XMLELEMENT*>(realloc(m_pElements, m_nReservedElements * sizeof(XMLELEMENT)));
	}
	return &m_pElements[m_nElements++];
}

void CMarkup::_SkipWhitespace(LPCTSTR& pstr) const
{
	while( *pstr > _T('\0') && *pstr <= _T(' ') )
	{
		pstr = ::CharNext(pstr);
	}
}

void CMarkup::_SkipWhitespace(LPTSTR& pstr) const
{
	while( *pstr > _T('\0') && *pstr <= _T(' ') )
	{
		pstr = ::CharNext(pstr);
	}
}

void CMarkup::_SkipIdentifier(LPCTSTR& pstr) const
{
	// 属性只能用英文，所以这样处理没有问题;
	while( *pstr != _T('\0') && (*pstr == _T('_') || *pstr == _T(':') || _istalnum(*pstr)) )
	{
		pstr = ::CharNext(pstr);
	}
}

void CMarkup::_SkipIdentifier(LPTSTR& pstr) const
{
	// 属性只能用英文，所以这样处理没有问题;
	while( *pstr != _T('\0') && (*pstr == _T('_') || *pstr == _T(':') || _istalnum(*pstr)) )
	{
		pstr = ::CharNext(pstr);
	}
}

bool CMarkup::_ParseAttributes(LPTSTR& pstrText)
{
	if( *pstrText == _T('>') )
	{
		return true;
	}

	*pstrText++ = _T('\0');
	_SkipWhitespace(pstrText);
	while( *pstrText != _T('\0') && *pstrText != _T('>') && *pstrText != _T('/') )
	{
		_SkipIdentifier(pstrText);
		LPTSTR pstrIdentifierEnd = pstrText;
		_SkipWhitespace(pstrText);
		if( *pstrText != _T('=') )
		{
			return _Failed(_T("Error while parsing attributes"), pstrText);
		}
		*pstrText++ = _T(' ');
		*pstrIdentifierEnd = _T('\0');
		_SkipWhitespace(pstrText);
		if( *pstrText++ != _T('\"') )
		{
			return _Failed(_T("Expected attribute value"), pstrText);
		}
		LPTSTR pstrDest = pstrText;
		if( !_ParseData(pstrText, pstrDest, _T('\"')) )
		{
			return false;
		}
		if( *pstrText == _T('\0') )
		{
			return _Failed(_T("Error while parsing attribute string"), pstrText);
		}
		*pstrDest = _T('\0');
		if( pstrText != pstrDest )
		{
			*pstrText = _T(' ');
		}
		pstrText++;
		_SkipWhitespace(pstrText);
	}
	return true;
}

bool CMarkup::_ParseData(LPTSTR& pstrText, LPTSTR& pstrDest, char cEnd)
{
	while( *pstrText != _T('\0') && *pstrText != cEnd )
	{
		if( *pstrText == _T('&') )
		{
			while( *pstrText == _T('&') )
			{
				_ParseMetaChar(++pstrText, pstrDest);
			}
			if (*pstrText == cEnd)
			{
				break;
			}
		}

		if( *pstrText == _T(' ') )
		{
			*pstrDest++ = *pstrText++;
			if( !m_bPreserveWhitespace ) _SkipWhitespace(pstrText);
		}
		else
		{
			LPTSTR pstrTemp = ::CharNext(pstrText);
			while( pstrText < pstrTemp)
			{
				*pstrDest++ = *pstrText++;
			}
		}
	}
	// 解析时,确保MapAttributes()正常工作
	// over a value that has been transformed.
	LPTSTR pstrFill = pstrDest + 1;
	while( pstrFill < pstrText )
	{
		*pstrFill++ = _T(' ');
	}
	return true;
}

void CMarkup::_ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest)
{
	if( pstrText[0] == _T('a') && pstrText[1] == _T('m') && pstrText[2] == _T('p') && pstrText[3] == _T(';') )
	{
		*pstrDest++ = _T('&');
		pstrText += 4;
	}
	else if( pstrText[0] == _T('l') && pstrText[1] == _T('t') && pstrText[2] == _T(';') )
	{
		*pstrDest++ = _T('<');
		pstrText += 3;
	}
	else if( pstrText[0] == _T('g') && pstrText[1] == _T('t') && pstrText[2] == _T(';') )
	{
		*pstrDest++ = _T('>');
		pstrText += 3;
	}
	else if( pstrText[0] == _T('q') && pstrText[1] == _T('u') && pstrText[2] == _T('o') && pstrText[3] == _T('t') && pstrText[4] == _T(';') )
	{
		*pstrDest++ = _T('\"');
		pstrText += 5;
	}
	else if( pstrText[0] == _T('a') && pstrText[1] == _T('p') && pstrText[2] == _T('o') && pstrText[3] == _T('s') && pstrText[4] == _T(';') )
	{
		*pstrDest++ = _T('\'');
		pstrText += 5;
	}
	else
	{
		*pstrDest++ = _T('&');
	}
}

bool CMarkup::_Failed(LPCTSTR pstrError, LPCTSTR pstrLocation)
{
	// 寄存最后一个错误;
	TRACE(_T("XML Error: %s"), pstrError);
	if( pstrLocation != NULL )
	{
		TRACE(pstrLocation);
	}
	_tcsncpy(m_szErrorMsg, pstrError, (sizeof(m_szErrorMsg) / sizeof(m_szErrorMsg[0])) - 1);
	_tcsncpy(m_szErrorXML, pstrLocation != NULL ? pstrLocation : _T(""), lengthof(m_szErrorXML) - 1);
	
	return false;	// 总是返回false;
}

} // namespace DuiLib
