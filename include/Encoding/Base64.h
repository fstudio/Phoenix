/*********************************************************************************************************
*   Base64.h
*   Thanks Nick Galbreath -- nickg.modp.com
*   Note: Phoenix Universial Chardet Library
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2014 The ForceStudio All Rights Reserved.
**********************************************************************************************************/

bool Base64Encode(const std::string& input, std::string* output);

/////////This
bool Base64Decode(const std::string& input, std::string* output);

#ifdef __cplusplus
extern "C"{
#endif
int modp_b64_encode(char* dest, const char* str, int len);
int modp_b64_decode(char* dest, const char* src, int len);
#ifdef __cplusplus
extern }
#endif
