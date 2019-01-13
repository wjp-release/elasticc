#pragma once

#include <iostream>
#include <string>
#include "curl/curl.h"

// Header-only Elastic Search C++ API (C++0x Compatible)

/*
curl examples

curl -X PUT "localhost:9200/twitter/_doc/1" -H 'Content-Type: application/json' -d '{"user":"kimchy","post_date":"2009-11-15T14:12:12","message":"try eslaticc"}'

CurlPutJson("localhost:9200/twitter/_doc/1",
	"{ \"user\":\"kimchy\",\"post_date\":\"2019-11-15T14:12:12\",\"message\":\"try elasticc\"}",
	result);
	
*/

namespace elasticc {
	// [0] Curl API
	static size_t CurlWriter(char *data, size_t size, size_t nmemb, std::string*writerData) {
		size_t sizes = size * nmemb;
		if (writerData == NULL) {
			return 0;
		}
		writerData->append(data, sizes);
		return sizes;
	}
	enum : int {
		HTTP_PUT = 1,
		HTTP_GET = 2,
		HTTP_POST = 3,
		HTTP_DELETE = 4
	};
	static inline bool Curl(int httpmode, const std::string& url, std::string& result, bool verbose = false) 
	{
		CURL*    conn = NULL;
		CURLcode code = CURLE_FAILED_INIT;
		char     errorBuffer[CURL_ERROR_SIZE];
		conn = curl_easy_init();
		if (conn == NULL) goto CurlPostExit;
		// 设置verbose模式
		code = curl_easy_setopt(conn, CURLOPT_VERBOSE, verbose ? 1 : 0);
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置url
		code = curl_easy_setopt(conn, CURLOPT_URL, url.c_str());
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置put/post/get/delete
		switch (httpmode) {
		case HTTP_PUT:
			code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "PUT"); 
			if (code != CURLE_OK) goto CurlPostExit;
			break;
		case HTTP_GET:
			code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "GET");
			if (code != CURLE_OK) goto CurlPostExit;
			break;
		case HTTP_POST:
			code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "POST");
			if (code != CURLE_OK) goto CurlPostExit;
			break;
		case HTTP_DELETE:
			code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "DELETE");
			if (code != CURLE_OK) goto CurlPostExit;
			break;
		default:
			return false;
		}
		// 设置useragent
		code = curl_easy_setopt(conn, CURLOPT_USERAGENT, "libcrp/0.1");
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置error buffer
		code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
		if (code != CURLE_OK) goto CurlPostExit;
		// 支持http 3xx重定向
		code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1);
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置response回写函数
		code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, CurlWriter);
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置返回response的字符串容器
		code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &result);
		if (code != CURLE_OK) goto CurlPostExit;
		// 开始执行curl post
		code = curl_easy_perform(conn);
		if (code != CURLE_OK) goto CurlPostExit;
	CurlPostExit:
		if (conn) {
			curl_easy_cleanup(conn);
		}
		return (code == CURLE_OK);
	}
	static inline bool CurlJson(int httpmode,const std::string& url, const std::string& json, std::string& result, bool verbose = false) 
	{
		CURL*    conn = NULL;
		CURLcode code = CURLE_FAILED_INIT;
		char     errorBuffer[CURL_ERROR_SIZE];
		conn = curl_easy_init();
		if (conn == NULL) goto CurlPostExit;
		// 设置verbose模式
		code = curl_easy_setopt(conn, CURLOPT_VERBOSE, verbose ? 1 : 0);
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置url
		code = curl_easy_setopt(conn, CURLOPT_URL, url.c_str());
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置put/post/get/delete
		switch (httpmode) {
		case HTTP_PUT:
			code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "PUT"); 
			if (code != CURLE_OK) goto CurlPostExit;
			break;
		case HTTP_GET:
			code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "GET");
			if (code != CURLE_OK) goto CurlPostExit;
			break;
		case HTTP_POST:
			code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "POST");
			if (code != CURLE_OK) goto CurlPostExit;
			break;
		case HTTP_DELETE:
			code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "DELETE");
			if (code != CURLE_OK) goto CurlPostExit;
			break;
		default:
			return false;
		}
		// 设置json header
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "charsets: utf-8");
		code = curl_easy_setopt(conn, CURLOPT_HTTPHEADER, headers);
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置postfileds内容
		code = curl_easy_setopt(conn, CURLOPT_POSTFIELDS, json.c_str());
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置useragent
		code = curl_easy_setopt(conn, CURLOPT_USERAGENT, "libcrp/0.1");
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置error buffer
		code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
		if (code != CURLE_OK) goto CurlPostExit;
		// 支持http 3xx重定向
		code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1);
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置response回写函数
		code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, CurlWriter);
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置返回response的字符串容器
		code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &result);
		if (code != CURLE_OK) goto CurlPostExit;
		// 开始执行curl post
		code = curl_easy_perform(conn);
		if (code != CURLE_OK) goto CurlPostExit;
	CurlPostExit:
		if (conn) {
			curl_easy_cleanup(conn);
		}
		return (code == CURLE_OK);
	}

	// [1] Index API
	// 将文档放入index/type/id处，使之可搜索。若目标索引不存在，则创建该索引。id若为-1（默认值），则采用自动生成的id。
	// 参数host是Elastic Search的host:ip字符串，必须包含端口号，例如"localhost:9200"。
	// 参数documentJson字符串中的json变量必须用双引号，例如："{ \"user\":\"kimchy\",\"post_date\":\"2019-11-15T14:12:12\",\"message\":\"try elasticc\"}"。
	static inline void Index(std::string& result, const std::string& host, const std::string& index, const std::string& type, const std::string& documentJson, int id = -1)
	{
		std::string url= host + "/" + index + "/" + type + "/";
		if (id != -1) url += std::to_string(id);
		if (!CurlJson(HTTP_PUT, url, documentJson, result)) std::cerr << "Index failed\n";
	}
	// 功能同Index，只不过不会覆盖指定位置已存在的文档，而是返回操作失败信息。
	static inline void TryIndex(std::string& result, const std::string& host, const std::string& index, const std::string& type, const std::string& documentJson, int id=-1)
	{
		std::string url = host + "/" + index + "/" + type+"/";
		if (id != -1) url += std::to_string(id);
		url += "?op_type=create";
		if(!CurlJson(HTTP_PUT, url, documentJson, result)) std::cerr << "TryIndex failed\n";
	}

	// [2] Get API
	// 获取index/type/id处的文档。
	// 例如 curl -X GET "localhost:9200/twitter/_doc/0"
	static inline void Get(std::string& result, const std::string& host, const std::string& index, const std::string& type, int id)
	{
		std::string url = host + "/" + index + "/" + type + "/" + std::to_string(id);
		if(!Curl(HTTP_GET, url, result)) std::cerr << "Get failed\n";
	}
	// 获取index/type/id处的文档的field值。
	// 例如 curl -X GET "localhost:9200/twitter/_doc/1/_source"
	static inline void GetField(std::string& result, const std::string& host, const std::string& index, const std::string& type, int id, const std::string& field)
	{
		std::string url = host + "/" + index + "/" + type + "/" + std::to_string(id) +"/"+ field;
		if(!Curl(HTTP_GET, url, result)) std::cerr << "GetField failed\n";
	}

	// [3] Delete API
	// 删除index/type/id处的文档。
	// 例如 curl -X DELETE "localhost:9200/twitter/_doc/1"
	static inline void Delete(std::string& result, const std::string& host, const std::string& index, const std::string& type, int id)
	{
		std::string url = host + "/" + index + "/" + type + "/" + std::to_string(id);
		if(!Curl(HTTP_DELETE, url, result)) std::cerr << "Delete failed\n";
	}

	// [4] Update API
	// POST一个更新脚本，对目标文档进行修改。
	// 例如 curl -X POST "localhost:9200/test/_doc/1/_update" -H 'Content-Type: application/json' -d' { "script" : "ctx._source.new_field = \u0027value_of_new_field\u0027" } '
	static inline void Update(std::string& result, const std::string& host, const std::string& index, const std::string& type, const std::string& updateScriptJson, int id)
	{
		std::string url = host + "/" + index + "/" + type + "/" + std::to_string(id)+"/_update";
		if(!CurlJson(HTTP_POST, url, updateScriptJson, result)) std::cerr << "Update failed\n";
	}



}