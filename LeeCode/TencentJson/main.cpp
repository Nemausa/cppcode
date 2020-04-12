#include <iostream>
#include <codecvt>
#include <string>
#include <cstdio>
#include <memory>
#include <afx.h>

#include "rapidjson/encodings.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"   // FileReadStream
#include "rapidjson/encodedstream.h"    // AutoUTFInputStream
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
using namespace std;
using namespace rapidjson;

#define _CRT_SECURE_NO_WARNINGS

// convert UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}

// convert wstring to UTF-8 string
std::string wstring_to_utf8(const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

static std::string ConvertCStringToUTF8(CString strValue)
{
	std::wstring wbuffer;
#ifdef _UNICODE
	wbuffer.assign(strValue.GetString(), strValue.GetLength());
#else
	/*
	* 转换ANSI到UNICODE
	* 获取转换后长度
	*/
	int length = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
	wbuffer.resize(length);
	/* 转换 */
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif

	/* 获取转换后长度 */
	int length = WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), wbuffer.size(), NULL, 0, NULL, NULL);
	/* 获取转换后内容 */
	std::string buffer;
	buffer.resize(length);

	WideCharToMultiByte(CP_UTF8, 0, strValue, -1, (LPSTR)(buffer.data()), length, NULL, NULL);
	return(buffer);
}


static CString ConvertUTF8ToCString(std::string utf8str)
{
	/* 预转换，得到所需空间的大小 */
	int nLen = ::MultiByteToWideChar(CP_UTF8, NULL,
		utf8str.data(), utf8str.size(), NULL, 0);
	/* 转换为Unicode */
	std::wstring wbuffer;
	wbuffer.resize(nLen);
	::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
		(LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
	return(CString(wbuffer.data(), wbuffer.length()));
#else
	/*
	* 转换为ANSI
	* 得到转换后长度
	*/
	nLen = WideCharToMultiByte(CP_ACP, 0,
		wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

	std::string ansistr;
	ansistr.resize(nLen);

	/* 把unicode转成ansi */
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
		(LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
	return(CString(ansistr.data(), ansistr.length()));
#endif
}

int main()
{
	setlocale(LC_CTYPE, "");
	FILE* fp = fopen("data.txt", "rb"); // 非 Windows 平台使用 "r"

	char readBuffer[256];
	FileReadStream bis(fp, readBuffer, sizeof(readBuffer));

	AutoUTFInputStream<unsigned, FileReadStream> eis(bis);  // 用 eis 包装 bis

	Document d;         // Document 为 GenericDocument<UTF8<> > 
	d.ParseStream<0, AutoUTF<unsigned> >(eis); // 把任何 UTF 编码的文件解析至内存中的 UTF-8

	fclose(fp);

	std::wstring ws = utf8_to_wstring(readBuffer);
	std::string utf8 = wstring_to_utf8(ws);

	rapidjson::Document json;
	json.Parse<0>(readBuffer);


	//StringBuffer buffer;
	//Writer<StringBuffer, Document::EncodingType, ASCII<> > writer(buffer);
	//d.Accept(writer);
	//std::cout << buffer.GetString();
	//const char * buff = buffer.GetString();
	//json.Parse<0>(buff);

	std::string ws_key = u8"";
	CString cs_value = _T("中文：？m³");
	std::string value = ConvertCStringToUTF8(cs_value);
	const char* name = json[value.c_str()].GetString();

	string str(name);
	CString a = ConvertUTF8ToCString(str);
	return 0;
}



