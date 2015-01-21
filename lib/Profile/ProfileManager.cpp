/*********************************************************************************************************
*   Phoneix XmlLite  Features
*   Note: ProfileManager.cpp
*   Data: 2015.01.17
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include "XmlLiteInternal.h"
#include <Profile/ProfileManager.h>
#include <Encoding/Encode.h>
#include <Shlwapi.h>


/*
  IStream *pXmlStream=nullptr;
  IXmlReader *pReader=nullptr;
  XmlNodeType xmlnode;
  const WCHAR* pwszPrefix;
  const WCHAR* pwszLocalName;
  const WCHAR* pwszValue;
  UINT cwchPrefix;
  std::wstring wsd, wsk, wIsdy;
  HRESULT hr = S_OK;
  if (FAILED(hr = SHCreateStreamOnFile(this->wxml.c_str(), STGM_READ, &pXmlStream)))
    HR(hr);
  if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, NULL)))
    HR(hr);
  if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
    HR(hr);
  if (FAILED(hr = pReader->SetInput(pXmlStream)))
    HR(hr);
  while (S_OK == pReader->Read(&xmlnode))
  {
    switch (xmlnode)
    {
    case XmlNodeType_Element:
      pReader->GetPrefix(&pwszPrefix, &cwchPrefix);
      pReader->GetLocalName(&pwszLocalName, NULL);
      //MessageBox(nullptr, pwszLocalName, L"LocalName", MB_OK);
      break;
    case XmlNodeType_EndElement:
      break;
    case XmlNodeType_Text:
      pReader->GetValue(&pwszValue, NULL);
      kv.insert(std::map<std::wstring, std::wstring>::value_type(pwszLocalName, pwszValue));
      //MessageBox(nullptr, pwszValue, L"Text", MB_OK);
      break;
    case XmlNodeType_Whitespace:
      //pReader->GetValue(&pwszValue, NULL);
      //MessageBox(nullptr, pwszValue, L"xx", MB_OK);
      break;
    default:
      break;
    }
  }

*/


#pragma warning(disable : 4127) // conditional expression is constant
#define CHKHR(stmt)                                                            \
  do {                                                                         \
    hr = (stmt);                                                               \
    if (FAILED(hr))                                                            \
      goto CleanUp;                                                            \
  } while (0)
#define HR(stmt)                                                               \
  do {                                                                         \
    hr = (stmt);                                                               \
    goto CleanUp;                                                              \
  } while (0)
#define SAFE_RELEASE(I)                                                        \
  do {                                                                         \
    if (I) {                                                                   \
      I->Release();                                                            \
    }                                                                          \
    I = NULL;                                                                  \
  } while (0)

const char *configheader = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\
\n<configuration>\
\n   <startup>\
\n     <supportedRuntime version=\"v4.0\" sku=\".NETFramework,Version=v4.5\" />\
\n   </startup>\
\n</configuration>\0";

// implement filestream that derives from IStream
class FileStream : public IStream {
  FileStream(HANDLE hFile) {
    _refcount = 1;
    _hFile = hFile;
  }

  ~FileStream() {
    if (_hFile != INVALID_HANDLE_VALUE) {
      ::CloseHandle(_hFile);
    }
  }

public:
  HRESULT static OpenFile(LPCWSTR pName, IStream **ppStream, bool fWrite) {
    HANDLE hFile = ::CreateFileW(
        pName, fWrite ? GENERIC_WRITE : GENERIC_READ, FILE_SHARE_READ, NULL,
        fWrite ? CREATE_ALWAYS : OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
      return HRESULT_FROM_WIN32(GetLastError());

    *ppStream = new FileStream(hFile);

    if (*ppStream == NULL)
      CloseHandle(hFile);

    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE
  QueryInterface(REFIID iid, __RPC__deref_out _Result_nullonfailure_ void
                                 __RPC_FAR *__RPC_FAR *ppvObject) {
    if (!ppvObject)
      return E_INVALIDARG;
    (*ppvObject) = NULL;

    if (iid == __uuidof(IUnknown) || iid == __uuidof(IStream) ||
        iid == __uuidof(ISequentialStream)) {
      *ppvObject = static_cast<IStream *>(this);
      AddRef();
      return S_OK;
    } else
      return E_NOINTERFACE;
  }

  virtual ULONG STDMETHODCALLTYPE AddRef(void) {
    return (ULONG)InterlockedIncrement(&_refcount);
  }

  virtual ULONG STDMETHODCALLTYPE Release(void) {
    ULONG res = (ULONG)InterlockedDecrement(&_refcount);
    if (res == 0)
      delete this;
    return res;
  }

  // ISequentialStream Interface
public:
  virtual HRESULT STDMETHODCALLTYPE
  Read(_Out_writes_bytes_to_(cb, *pcbRead) void *pv, _In_ ULONG cb,
       _Out_opt_ ULONG *pcbRead) {
    BOOL rc = ReadFile(_hFile, pv, cb, pcbRead, NULL);
    return (rc) ? S_OK : HRESULT_FROM_WIN32(GetLastError());
  }

  virtual HRESULT STDMETHODCALLTYPE Write(_In_reads_bytes_(cb) const void *pv,
                                          _In_ ULONG cb,
                                          _Out_opt_ ULONG *pcbWritten) {
    BOOL rc = WriteFile(_hFile, pv, cb, pcbWritten, NULL);
    return rc ? S_OK : HRESULT_FROM_WIN32(GetLastError());
  }

  // IStream Interface
public:
  virtual HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER) {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE CopyTo(_In_ IStream *, ULARGE_INTEGER,
                                           _Out_opt_ ULARGE_INTEGER *,
                                           _Out_opt_ ULARGE_INTEGER *) {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE Commit(DWORD) { return E_NOTIMPL; }

  virtual HRESULT STDMETHODCALLTYPE Revert(void) { return E_NOTIMPL; }

  virtual HRESULT STDMETHODCALLTYPE
      LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD) {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE
      UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD) {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE Clone(__RPC__deref_out_opt IStream **) {
    return E_NOTIMPL;
  }

  virtual HRESULT STDMETHODCALLTYPE
  Seek(LARGE_INTEGER liDistanceToMove, DWORD dwOrigin,
       _Out_opt_ ULARGE_INTEGER *lpNewFilePointer) {
    DWORD dwMoveMethod;

    switch (dwOrigin) {
    case STREAM_SEEK_SET:
      dwMoveMethod = FILE_BEGIN;
      break;
    case STREAM_SEEK_CUR:
      dwMoveMethod = FILE_CURRENT;
      break;
    case STREAM_SEEK_END:
      dwMoveMethod = FILE_END;
      break;
    default:
      return STG_E_INVALIDFUNCTION;
      break;
    }

    if (SetFilePointerEx(_hFile, liDistanceToMove,
                         (PLARGE_INTEGER)lpNewFilePointer, dwMoveMethod) == 0)
      return HRESULT_FROM_WIN32(GetLastError());
    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE Stat(__RPC__out STATSTG *pStatstg, DWORD) {
    if (GetFileSizeEx(_hFile, (PLARGE_INTEGER)&pStatstg->cbSize) == 0)
      return HRESULT_FROM_WIN32(GetLastError());
    return S_OK;
  }

private:
  HANDLE _hFile;
  LONG _refcount;
};



///////////

namespace Profile {
class XmlIntegratedAnalyzer{
private:
  std::wstring m_xmlfile;
public:
  XmlIntegratedAnalyzer(std::wstring xmlfile):m_xmlfile(xmlfile)
  {
  }
  ~XmlIntegratedAnalyzer()
  {
    //Release COM Interface
  }
  bool Reader(std::map<std::wstring,std::wstring> &appsettingkv)
  {
    if(!PathFileExistsW(m_xmlfile.c_str()))
    {
      return false;
    }
    return true;
  }
  bool Writer(std::map<std::wstring,std::wstring> &appsettingkv)
  {
    return true;
  }
};



ProfileManager::ProfileManager(std::wstring profile)
    : configfile(profile), beFaild(false) {
      xiaptr=new XmlIntegratedAnalyzer(this->configfile);
  if (!BeReadProfile()) {
    beFaild = true;
    return;
  }
}

ProfileManager::~ProfileManager()
{
  xiaptr->Writer(this->appsettingkv);
  if(xiaptr)
    delete xiaptr;
}

bool ProfileManager::BeReadProfile()
{
  return xiaptr->Reader(appsettingkv);
}


bool ProfileManager::BeWriteProfile()
{
  return xiaptr->Writer(appsettingkv);
}

std::wstring ProfileManager::Get(std::wstring& key) {
  // if find key
  auto iter=appsettingkv.find(key);
  if(iter==appsettingkv.end())
    return L"";
  return appsettingkv[key];
}

std::string ProfileManager::Get(std::string &key)
{
  std::wstring wkey=MultiByteToUnicode(key);
  auto iter=appsettingkv.find(wkey);
  if(iter==appsettingkv.end())
    return "";
  return UnicodeToMultiByte(appsettingkv[wkey]);
}

bool ProfileManager::Set(std::wstring& key, std::wstring& value)
{
  appsettingkv[key]=value;
  return true;
}

bool ProfileManager::Set(std::string& key, std::string& value)
{
  std::wstring wkey=MultiByteToUnicode(key);
  kvmap[wkey]=MultiByteToUnicode(value);
  return true;
}

}
