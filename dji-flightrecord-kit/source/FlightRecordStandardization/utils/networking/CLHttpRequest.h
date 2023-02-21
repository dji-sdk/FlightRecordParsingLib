//
//  CLHttpRequest.h
//  djifoundation
//
//  Copyright © 2019年 DJI. All rights reserved.
//

#ifndef _CLHttpRequest_H
#define _CLHttpRequest_H

#include "CLCoreLayer.h"
#include <functional>
#include <string>
#include <map>

BEGIN_CORE_NAMESPACE

// Http Method
typedef enum
{
    GET,
    POST,
    PUT,
} CLHttpRequestMethod;

// Http Request
class CLHttpRequest
{
public:
    CLHttpRequest(std::string url, CLHttpRequestMethod method);
    ~CLHttpRequest();
    
    using CLHttpRequestCallback = std::function<void(CLHttpRequest* request, bool succeeded)>;
    using CLHttpDownloadProgressCallback = std::function<int(CLHttpRequest* request, double dltotal, double dlnow, double ultotal, double ulnow)>;
    
    static CLHttpRequest* Post(const std::string& url, char* buffer, size_t size);
    static CLHttpRequest* Get(const std::string& url);
    static CLHttpRequest* Put(const std::string& url);
    static CLHttpRequest* Download(const std::string& url);
    
    void SetRequestHeader(std::string key, std::string value);
    std::string GetRequestHeader(std::string key);
    
    void SetTimeout(int seconds);
    
    void SendRequest(CLHttpRequestCallback callback);
    void SendDownloadRequest(const std::string& file_path, CLHttpRequestCallback callback, CLHttpDownloadProgressCallback download_progress_callback);
    
    bool IsNetworkError() { return m_bNetworkError; }
    
    int GetResponseCode() { return m_iResponseCode; }
    
    void* GetResponseData() {return m_pRecvBuffer; } ;
    size_t GetResponseBytes() { return m_iRecvBufferSize; }
    

    void SetPostData(char* buffer, size_t size);
    
private:
    static size_t OnHttpDataCallback(char* ptr, size_t size, size_t nitems, void* userdata);
    static size_t OnHttpHeaderCallback(char* ptr, size_t size, size_t nitems, void* userdata);
    static size_t OnDownloadProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
    static size_t OnDownLoadPackageCallback(void *ptr, size_t size, size_t nmemb, void *userdata);
    
    void OnRecvData(char* ptr, size_t size);
    void OnRecvHeader(char* ptr, size_t size);
    void OnPorogressUpdate(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
private:
    std::map<std::string, std::string> m_HttpHeaders;
    std::string m_HttpURL;
    
    CLHttpRequestMethod m_HttpMethod;
    
    int m_HttpTimeout;
    
    char* m_pPostBuffer;
    size_t m_iPostBufferSize;
    
    char* m_pRecvBuffer;
    size_t m_iRecvBufferSize;
    size_t m_iRecvBufferOffset;
    
    int m_iResponseCode;
    bool m_bNetworkError;
    CLHttpDownloadProgressCallback download_progress_callback_;
};

END_CORE_NAMESPACE

#endif
