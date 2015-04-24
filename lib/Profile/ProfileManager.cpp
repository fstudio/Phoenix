/*********************************************************************************************************
*   Phoneix Profile  Features
*   Note: ProfileManager.cpp
*   Date: 2015.01.17
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include "XmlLiteInternal.h"
#include <Profile/ProfileManager.h>
#include <Encoding/Encode.h>
#include <Shlwapi.h>
using namespace Force;

class ProfileStructure{
public:
  ProfileStructure(){}
};


class XMLAnalyzer {
private:
  struct ConfigSettingMark {
    bool cfg;
    bool set;
  };
  IStream *pXmlStream;
  IXmlReader *pReader;
  std::wstring m_xmlfile;
  bool XmlAttributesResolve(IXmlReader *pReader,
    std::unordered_map<std::wstring, std::wstring> &kv) {
    const WCHAR *pwszPrefix;
    const WCHAR *pwszLocalName;
    const WCHAR *pwszValue;
    const WCHAR *pwszKey = nullptr;
    HRESULT hr = pReader->MoveToFirstAttribute();
    if (hr != S_OK) {
      return false;
    } else {
      while (TRUE) {
        if (!pReader->IsDefault()) {
          UINT cwchPrefix;
          if ((hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)) != S_OK) {
            return false;
          }
          if ((hr = pReader->GetLocalName(&pwszLocalName, NULL)) != S_OK) {
            return false;
          }
          if ((hr = pReader->GetValue(&pwszValue, NULL)) != S_OK) {
            return false;
          }
          if (cwchPrefix > 0) {
            ///
          } else {
            if (wcscmp(pwszLocalName, L"key") == 0) {
              pwszKey = pwszValue;
            } else {
              if (wcscmp(pwszLocalName, L"value") == 0) {
                // wprintf(L"Insert %s === %s \n", pwszKey, pwszValue);
                kv.insert(std::map<std::wstring, std::wstring>::value_type(
                    pwszKey, pwszValue));
              }
            }
          }
        }
        if (S_OK != pReader->MoveToNextAttribute())
          break;
      }
    }
    return true;
  }
  HRESULT XmlReaderInternal(std::map<std::wstring, std::wstring> &kv) {
    XmlNodeType xmlnode;
    const WCHAR *pwszPrefix;
    const WCHAR *pwszLocalName;
    const WCHAR *pwszValue;
    UINT cwchPrefix;
    UINT c = 0;
    ConfigSettingMark csm = {false, false};
    HRESULT hr = S_OK;
    if ((hr = SHCreateStreamOnFile(m_xmlfile.c_str(), STGM_READ,
                                   &pXmlStream)) != S_OK)
      return hr;
    if ((hr = CreateXmlReader(__uuidof(IXmlReader), (void **)&pReader, NULL)) !=
        S_OK)
      return hr;
    if ((hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing,
                                   DtdProcessing_Prohibit)) != S_OK)
      return hr;
    if ((hr = pReader->SetInput(pXmlStream)) != S_OK)
      return hr;
    while (S_OK == pReader->Read(&xmlnode)) {
      switch (xmlnode) {
      case XmlNodeType_Element:
        pReader->GetPrefix(&pwszPrefix, &cwchPrefix);
        pReader->GetLocalName(&pwszLocalName, NULL);
        if (wcscmp(pwszLocalName, L"configuration") == 0) {
          csm.cfg = true;
        }
        if (wcscmp(pwszLocalName, L"appSettings") == 0 && csm.cfg) {
          csm.set = true;
        }
        if (wcscmp(pwszLocalName, L"add") == 0 && csm.set && csm.cfg) {
          if (!XmlAttributesResolve(pReader, kv))
            hr = 1;
        }
        break;
      case XmlNodeType_EndElement:
        break;
      case XmlNodeType_Attribute:
        break;
      case XmlNodeType_Text:
        pReader->GetValue(&pwszValue, NULL);
        break;
      case XmlNodeType_Whitespace:
        break;
      default:
        break;
      }
    }
    return hr;
  }

public:
  XMLAnalyzer(std::wstring xmlfile)
      : m_xmlfile(xmlfile), pXmlStream(nullptr), pReader(nullptr) {
        /////Resource Initialize
      }
  ~XMLAnalyzer() {
    // Release COM Interface
    if (pReader)
      pReader->Release();
    if (pXmlStream)
      pXmlStream->Release();
  }
  bool Reader(std::map<std::wstring, std::wstring> &appsettingkv) {
    if (!PathFileExistsW(m_xmlfile.c_str())) {
      return false;
    }

    return (this->XmlReaderInternal(appsettingkv) == S_OK);
  }
  bool Writer(std::map<std::wstring, std::wstring> &appsettingkv) {
    return true;
  }
};
