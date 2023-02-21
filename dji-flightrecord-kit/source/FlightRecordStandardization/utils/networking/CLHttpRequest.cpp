#include "CLHttpRequest.h"
#include <mutex>
#include <map>
#include <list>
#include <thread>
#include <curl/curl.h>
#include <algorithm>
#include <cctype> 
#include <string.h>

BEGIN_CORE_NAMESPACE

#if WIN32
#define TO_LOWER static_cast<int(*)(int)>(std::tolower)
#elif __linux__
#define TO_LOWER static_cast<int(*)(int)>(std::tolower)
#else
#define TO_LOWER std::tolower
#endif

#if defined(DELETE)
#undef DELETE
#endif

static std::once_flag s_curl_init_once_flag;

CLHttpRequest::CLHttpRequest(std::string url, CLHttpRequestMethod method)
{
    m_pPostBuffer = NULL;
    m_iPostBufferSize = 0;
    
    m_pRecvBuffer = NULL;
    m_iRecvBufferSize = 0;
    m_iRecvBufferOffset = 0;
    
    m_bNetworkError = false;
    m_iResponseCode = 0;
    
    m_HttpTimeout = 10;
    m_HttpURL = url;
    m_HttpMethod = method;
    
    std::call_once(s_curl_init_once_flag, [](){ curl_global_init(CURL_GLOBAL_ALL); });
}

CLHttpRequest::~CLHttpRequest()
{
    if (m_pRecvBuffer) {
        free(m_pRecvBuffer);
        m_pRecvBuffer = NULL;
    }
    
    if (m_pPostBuffer) {
        free(m_pPostBuffer);
        m_pPostBuffer = NULL;
    }
}

CLHttpRequest* CLHttpRequest::Post(const std::string& url, char* buffer, size_t size)
{
    CLHttpRequest* request = new CLHttpRequest(url, CLHttpRequestMethod::POST);
    request->SetPostData(buffer, size);
    
    return request;
}

CLHttpRequest* CLHttpRequest::Get(const std::string& url)
{
    CLHttpRequest* request = new CLHttpRequest(url, CLHttpRequestMethod::GET);
    
    return request;
}

CLHttpRequest* CLHttpRequest::Put(const std::string& url)
{
    CLHttpRequest* request = new CLHttpRequest(url, CLHttpRequestMethod::PUT);
    
    return request;
}

CLHttpRequest* CLHttpRequest::Download(const std::string& url) {
    CLHttpRequest* request = new CLHttpRequest(url, CLHttpRequestMethod::GET);
    
    return request;
}

void CLHttpRequest::SetRequestHeader(std::string key, std::string value)
{
    m_HttpHeaders[key] = value;
}

std::string CLHttpRequest::GetRequestHeader(std::string key)
{
	if (m_HttpHeaders.find(key) != m_HttpHeaders.end())
	{
		return m_HttpHeaders[key];
	}

    return "";
}

void CLHttpRequest::SetTimeout(int seconds)
{
    m_HttpTimeout = seconds;
}

void CLHttpRequest::SendRequest(CLHttpRequestCallback callback)
{
    std::thread th([this, callback](){
        
        CURL* pCurl = curl_easy_init();
        if (pCurl)
        {
            CURLcode code;
            
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
            curl_easy_setopt(pCurl, CURLOPT_HEADER, 0L);
            curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, CLHttpRequest::OnHttpHeaderCallback);
            curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, this);
            curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, CLHttpRequest::OnHttpDataCallback);
            curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, this);
            
            curl_easy_setopt(pCurl, CURLOPT_URL, m_HttpURL.c_str());
            curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, m_HttpTimeout);
            
            curl_slist* pHeaders = NULL;
            for (auto& item : m_HttpHeaders) {
                std::string value = item.first + ":" + item.second;
                pHeaders = curl_slist_append(pHeaders, value.c_str());
            }
            code = curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pHeaders);
            
            // Set Http Method And Data
            switch (m_HttpMethod) {
            case CLHttpRequestMethod::GET:
                {

                    break;
                }
             case CLHttpRequestMethod::POST:
                {
                    curl_easy_setopt(pCurl, CURLOPT_POST, 1L);
                    if (m_pPostBuffer && m_iPostBufferSize > 0) {
                        curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, m_pPostBuffer);
                        curl_easy_setopt(pCurl, CURLOPT_POSTFIELDSIZE, m_iPostBufferSize);
                    }
                    break;
                }
             case CLHttpRequestMethod::PUT:
                {
                    curl_easy_setopt(pCurl, CURLOPT_PUT, 1L);
                    break;
                }
                default:
                    break;
            }
            
            // Start Perform Http Request
            code = curl_easy_perform(pCurl);
            if (code == CURLE_OK) {
                m_bNetworkError = false;
                curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &m_iResponseCode);
//                printf("Http Response Code: %d\n", m_iResponseCode);
                if (callback) {
                    callback(this, true);
                }
            }
            else
            {
                printf("Http Error: %s\n", curl_easy_strerror(code));
                m_bNetworkError = true;
                if (callback) {
                    callback(this, false);
                }
            }
            
            curl_easy_cleanup(pCurl);
        }
    });
    
    th.join();
}

void CLHttpRequest::SendDownloadRequest(const std::string& file_path, CLHttpRequestCallback callback, CLHttpDownloadProgressCallback download_progress_callback) {
    std::thread th([this, file_path, callback, download_progress_callback](){
        
        FILE *fp;
        if ((fp = fopen(file_path.c_str(), "wt+")) == NULL){
            if (callback) {
                callback(this, false);
            }
            return;
        }

        CURL* pCurl = curl_easy_init();
        if (pCurl)
        {
            CURLcode code;
            
            curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 0L);
            curl_easy_setopt(pCurl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
            curl_easy_setopt(pCurl, CURLOPT_SSL_ENABLE_ALPN, 0L);
            
            curl_easy_setopt(pCurl, CURLOPT_HEADER, 0L);
            curl_easy_setopt(pCurl, CURLOPT_HEADERFUNCTION, CLHttpRequest::OnHttpHeaderCallback);
            curl_easy_setopt(pCurl, CURLOPT_HEADERDATA, this);
            
            curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, CLHttpRequest::OnDownLoadPackageCallback);
            curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, fp);//Set to write DATA to the file stream FP
            
            curl_easy_setopt(pCurl, CURLOPT_NOPROGRESS, 0);
            curl_easy_setopt(pCurl, CURLOPT_PROGRESSDATA, this);
            curl_easy_setopt(pCurl, CURLOPT_PROGRESSFUNCTION, CLHttpRequest::OnDownloadProgressCallback);
            curl_easy_setopt(pCurl, CURLOPT_URL, m_HttpURL.c_str());
            download_progress_callback_ = download_progress_callback;
            curl_slist* pHeaders = NULL;
            for (auto& item : m_HttpHeaders) {
                std::string value = item.first + ":" + item.second;
                pHeaders = curl_slist_append(pHeaders, value.c_str());
            }
            code = curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pHeaders);
            
            code = curl_easy_perform(pCurl);
            if (code == CURLE_OK) {
                m_bNetworkError = false;
                curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &m_iResponseCode);
//                printf("Http Response Code: %d\n", m_iResponseCode);
                if (callback) {
                    callback(this, true);
                }
            }
            else
            {
                printf("Http Error: %s\n", curl_easy_strerror(code));
                m_bNetworkError = true;
                if (callback) {
                    callback(this, false);
                }
            }
            fclose(fp);
            curl_easy_cleanup(pCurl);
        }
    });
    
    th.detach();
}

void CLHttpRequest::SetPostData(char* buffer, size_t size)
{
    if (m_pPostBuffer) {
        free(m_pPostBuffer);
        m_pPostBuffer = NULL;
        m_iPostBufferSize = 0;
    }
    
    if (buffer && size > 0) {
        m_pPostBuffer = (char*)malloc(size);
        if (m_pPostBuffer) {
            memset(m_pPostBuffer, 0, size);
            memcpy(m_pPostBuffer, buffer, size);
            m_iPostBufferSize = size;
        }
    }
}

void CLHttpRequest::OnPorogressUpdate(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow) {
    if (download_progress_callback_) {
        download_progress_callback_(this, dltotal, dlnow, ultotal, ulnow);
    }
}

void CLHttpRequest::OnRecvData(char *ptr, size_t size)
{
//    printf("Http: Recv Data: %s\n", ptr);
    
    bool hasMemory = m_iRecvBufferSize - m_iRecvBufferOffset >= size;
    if (m_pRecvBuffer && hasMemory) {
        memcpy(m_pRecvBuffer + m_iRecvBufferOffset, ptr, size);
        m_iRecvBufferOffset += size;
    }

    if (m_iRecvBufferOffset == m_iRecvBufferSize) {
//        printf("Http Recv Completed...\n");
    }
}

void CLHttpRequest::OnRecvHeader(char *ptr, size_t size)
{
//    printf("Http: Recv Header: %s  Size = %zu\n", ptr, size);
    if (ptr && size > 0) {
        std::string content = std::string(ptr, size);
        content.erase(content.find_last_not_of(" \n\r\t") + 1);
        if (content.size() > 0) {
            std::transform(content.begin(), content.end(), content.begin(), TO_LOWER);
            
            std::string::size_type npos = content.find_first_of(":");
            if (npos != std::string::npos) {
                std::string key = content.substr(0, npos);
                std::string value = content.substr(npos + 1);
                
                if (key == "content-length" && value.length() > 0) {
                    m_iRecvBufferSize = std::atoi(value.c_str());
                    m_iRecvBufferOffset = 0;
                    if (m_pRecvBuffer) {
                        free(m_pRecvBuffer);
                        m_pRecvBuffer = NULL;
                    }
                    
                    m_pRecvBuffer = (char*)malloc(m_iRecvBufferSize + 1);
                    if (m_pRecvBuffer) {
                        memset(m_pRecvBuffer, 0, m_iRecvBufferSize + 1);
                    }
                }
                else if (key == "transfer-encoding" && value == "chunked")
                {
                    // Http uses chunking to transfer, at this time can not get the data length in advance
                    m_iRecvBufferSize = 0;
                    m_iRecvBufferOffset = 0;
                    if (m_pRecvBuffer) {
                        free(m_pRecvBuffer);
                        m_pRecvBuffer = NULL;
                    }
                }
            }
        }
    }
}

size_t CLHttpRequest::OnHttpDataCallback(char* ptr, size_t size, size_t nitems, void* userdata)
{
    CLHttpRequest* pThis = (CLHttpRequest*)userdata;
    if (pThis) {
        pThis->OnRecvData(ptr, nitems);
    }
    
    return nitems;
}

size_t CLHttpRequest::OnHttpHeaderCallback(char* ptr, size_t size, size_t nitems, void* userdata)
{
    CLHttpRequest* pThis = (CLHttpRequest*)userdata;
    if (pThis) {
        pThis->OnRecvHeader(ptr, nitems);
    }
    
    return nitems;
}

size_t CLHttpRequest::OnDownloadProgressCallback(void *ptr, double dltotal, double dlnow, double ultotal, double ulnow)
{
    CLHttpRequest* pThis = (CLHttpRequest*)ptr;
    if (pThis) {
        pThis->OnPorogressUpdate(ptr, dltotal, dlnow, ultotal, ulnow);
    }
    return 0;
}

size_t CLHttpRequest::OnDownLoadPackageCallback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

END_CORE_NAMESPACE
