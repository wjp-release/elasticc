#pragma once

#include <iostream>
#include <string>
#include "curl/curl.h"

// Header-only Compatible Elastic Search C++ API (C++0x Compatible)

/*
curl examples
	curl -X PUT "localhost:9200/twitter/_doc/1" -H 'Content-Type: application/json' -d '{"user":"kimchy","post_date":"2009-11-15T14:12:12","message":"try eslaticc"}'
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
	static inline bool CurlPutJson(const std::string& url, const std::string& json, std::string& result, bool verbose = false) {
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
		// 设置put
		code = curl_easy_setopt(conn, CURLOPT_CUSTOMREQUEST, "PUT");
		if (code != CURLE_OK) goto CurlPostExit;
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
	static inline bool CurlPost(const std::string& url, const std::string& postFields, std::string& result, bool verbose=false) {
		CURL*    conn = NULL;
		CURLcode code = CURLE_FAILED_INIT;
		char     errorBuffer[CURL_ERROR_SIZE];
		conn = curl_easy_init();
		if (conn == NULL) goto CurlPostExit;
		// 设置verbose模式
		code = curl_easy_setopt(conn, CURLOPT_VERBOSE, verbose?1:0);
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置url
		code = curl_easy_setopt(conn, CURLOPT_URL, url.c_str());
		if (code != CURLE_OK) goto CurlPostExit;
		// 设置post
		code = curl_easy_setopt(conn, CURLOPT_POST, 1);
		if (code != CURLE_OK) goto CurlPostExit;
		code = curl_easy_setopt(conn, CURLOPT_POSTFIELDS, postFields.c_str());
		if (code != CURLE_OK) goto CurlPostExit;
		code = curl_easy_setopt(conn, CURLOPT_POSTFIELDSIZE, postFields.size());
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
	static inline void Index(std::string& result, const std::string& index, const std::string& type, const std::string& documentJson, int id = -1)
	{
		CurlPutJson("localhost:9200/twitter/_doc/1",
					"{ \"user\":\"kimchy\",\"post_date\":\"2019-11-15T14:12:12\",\"message\":\"try elasticc\"}",
					result);
	}
	// 功能同Index，只不过不会覆盖指定位置已存在的文档，而是返回操作失败信息。
	static inline void TryIndex(std::string& result, const std::string& index, const std::string& type, const std::string& documentJson, int id=-1)
	{

	}

	// [2] Get API
	// 获取index/type/id处的文档。
	static inline void Get(std::string& result, const std::string& index, const std::string& type, int id)
	{

	}
	// 获取index/type/id处的文档的field值。
	static inline void GetField(std::string& result, const std::string& index, const std::string& type, int id, const std::string& field)
	{

	}


	// [3] Delete API
	static inline void Delete(std::string& result, const std::string& index, const std::string& type, int id)
	{

	}

	// [4] Update API



}