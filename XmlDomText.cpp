#include "SafeRelease.hpp"
#include "XmlDomText.hpp"
#include "ComString.hpp"
#include "GetErrorMessage.h"

namespace MSXML {
	XmlDomText::XmlDomText() : XmlDomText(nullptr) {}

	XmlDomText::XmlDomText(const XmlDomDocument& lpDoc, const std::wstring& Data) {
		ComString str(Data);
		if (const HRESULT hr = lpDoc->createTextNode(str.get(), &this->lpText); FAILED(hr)) throw std::runtime_error(GetErrorMessageA(hr));
	}
	
	XmlDomText::XmlDomText(std::nullptr_t) : lpText(nullptr) {}

	XmlDomText::~XmlDomText() { SafeRelease(this->lpText); }

	XmlDomText::XmlDomText(XmlDomText&& x) noexcept : lpText(x.lpText) { x.lpText = nullptr; }

	XmlDomText& XmlDomText::operator = (XmlDomText&& x) noexcept {
		this->lpText = x.lpText;
		x.lpText = nullptr;
		return *this;
	}

	IXMLDOMText* XmlDomText::operator -> () noexcept { return this->lpText; }

	IXMLDOMText* XmlDomText::operator -> () const noexcept { return this->lpText; }

	XmlDomText::operator IXMLDOMText* () const noexcept { return this->lpText; }

	IXMLDOMText** XmlDomText::operator & () noexcept { return &this->lpText; }
}
