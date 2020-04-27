﻿#include "MSXMLRead.hpp"
#include "GetErrorMessage.h"
#include <Windows.h>
#include <comdef.h>
#include <stdexcept>

namespace MSXML {
	Read::Read(const std::wstring& FilePath) : lpXmlDoc() {
		{
			WIN32_FIND_DATAW FindData{};
			if (
				HANDLE hFind = FindFirstFileW(FilePath.c_str(), &FindData);
				 [&hFind] (){
					const bool Flag = (INVALID_HANDLE_VALUE == hFind);
					CloseHandle(hFind);
					return Flag;
				 }
			()) throw std::runtime_error(GetErrorMessageA());
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) throw std::runtime_error("Reserved path is directory");
		}
		VARIANT_BOOL Result{};
		if (const HRESULT hr = this->lpXmlDoc->put_async(VARIANT_FALSE); FAILED(hr)) throw std::runtime_error(GetErrorMessageA(hr));
		if (const HRESULT hr = this->lpXmlDoc->load(_variant_t(FilePath.c_str()), &Result); FAILED(hr)) throw std::runtime_error(GetErrorMessageA(hr));
	}

	XmlDataManager::wstring Read::GetW(const std::wstring& Path) {
		if (Base::find(Path) == Base::end()) Base::emplace(Path, XmlDataManager::wstring(this->lpXmlDoc, Path));
		return Base::operator[](Path);
	}
}
