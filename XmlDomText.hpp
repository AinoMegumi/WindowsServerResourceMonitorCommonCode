#pragma once
#include "XmlDomDocument.hpp"

namespace MSXML {
	class XmlDomText {
	private:
		IXMLDOMText* lpText;
	public:
		XmlDomText();
		XmlDomText(const XmlDomDocument& lpDoc, const std::wstring& Data);
		XmlDomText(std::nullptr_t);
		~XmlDomText();
		XmlDomText(const XmlDomText&) = delete;
		XmlDomText(XmlDomText&& x) noexcept;
		XmlDomText& operator = (const XmlDomText&) = delete;
		XmlDomText& operator = (XmlDomText&& x) noexcept;
		IXMLDOMText* operator -> () noexcept;
		IXMLDOMText* operator -> () const noexcept;
		operator IXMLDOMText* () const noexcept;
		IXMLDOMText** operator & () noexcept;
	};
}
