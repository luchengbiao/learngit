#pragma once
#include <string>
#include "json/json.h"
#include <stdint.h>
#include "base/util/string_util.h"

enum API_RESULT_CODE
{
	API_SUCCESS = 0,
	MOBILE_NOT_EXIST
};

class ApiResultPrivate;

// like std::unique_ptr<ApiResultPrivate>
// but even in ApiResult(const ApiResult& right) still move the right
class ApiResult
{
public:
	ApiResult();
	ApiResult(const Json::Value& value);
	ApiResult(ApiResult&&);
	ApiResult& operator=(ApiResult&&);
	
	
	~ApiResult();

	// Ugly to prevent compile error:
	// The problem is that std::function must be CopyConstructible, 
	// which requires its argument(which will be stored by the function) also be CopyConstructible.
	ApiResult(const ApiResult&); 

public:
	ApiResultPrivate*   Get();
	void				Reset(ApiResultPrivate* ptr);
	ApiResultPrivate*	Release();

public:
	static void		Parse(std::string json, ApiResult& api_result);

	bool			Success();
	bool			ParseSuccess();
	int				GetCode();
	std::string		GetMsg();
	std::string		GetOtherMsg();
	Json::Value		GetData() const;
	Json::Value		GetExtraData()const;

	int				GetDataInt(const char* key) const;
	double			GetDataDouble(const char* key) const;
	bool			GetDataBool(const char* key);
	std::string		GetDataString(const char* key) const;
	Json::Value		GetDataJsonValue(const char* key) const;
	uint64_t		GetDataLong(const char* key) const;

	bool			KeyDataNull(const char* key);
	bool			HasKey(const char* key);

	void			SetMsg(std::wstring msg_);
	void			SetCode(int c_);
	bool			NetFailed();

private:
	ApiResultPrivate* _ptr;
};