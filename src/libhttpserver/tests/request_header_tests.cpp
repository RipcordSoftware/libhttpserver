#include <gtest/gtest.h>

#include <cstring>

#include "../request_headers.h"

class RequestHeaderTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
    bool SanityCheckWhatMessage(const char* msg);    
};

bool RequestHeaderTests::SanityCheckWhatMessage(const char* msg) {
    while (*msg != '\0') {
        if (*msg < 0x0d || *msg > 0x7e) {
            return false;
        }
        msg++;
    }
    return true;
}

TEST_F(RequestHeaderTests, test1) {
    rs::httpserver::HeaderBuffer buffer;
    ASSERT_TRUE(!rs::httpserver::RequestHeaders::Create(buffer));
}

TEST_F(RequestHeaderTests, test2) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        return 0;
    });
    
    ASSERT_TRUE(!rs::httpserver::RequestHeaders::Create(buffer));
}

TEST_F(RequestHeaderTests, test3) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    auto headers = rs::httpserver::RequestHeaders::Create(buffer);
    ASSERT_TRUE(!!headers);
    ASSERT_STREQ("GET", headers->getMethod().c_str());
    ASSERT_STREQ("/", headers->getUri().c_str());
    ASSERT_STREQ("HTTP/1.1", headers->getVersion().c_str());
    ASSERT_STREQ("localhost", headers->getHost().c_str());
}

TEST_F(RequestHeaderTests, test3b) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET / HTTP/1.1\r\n\r\n";        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    auto headers = rs::httpserver::RequestHeaders::Create(buffer);
    ASSERT_TRUE(!!headers);
    ASSERT_STREQ("GET", headers->getMethod().c_str());
    ASSERT_STREQ("/", headers->getUri().c_str());
    ASSERT_STREQ("HTTP/1.1", headers->getVersion().c_str());
}

TEST_F(RequestHeaderTests, test4) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET / HTTP/1.1\r\n";        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "Host: localhost\r\n\r\n";        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    auto headers = rs::httpserver::RequestHeaders::Create(buffer);
    ASSERT_TRUE(!!headers);
    ASSERT_STREQ("GET", headers->getMethod().c_str());
    ASSERT_STREQ("/", headers->getUri().c_str());
    ASSERT_STREQ("HTTP/1.1", headers->getVersion().c_str());
    ASSERT_STREQ("localhost", headers->getHost().c_str());
    ASSERT_FALSE(headers->IsChunked());
}

TEST_F(RequestHeaderTests, test5) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET / HTTP/1.1\r\n";        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    auto headers = rs::httpserver::RequestHeaders::Create(buffer);
    ASSERT_TRUE(!headers);
}

TEST_F(RequestHeaderTests, test6) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET / HTTP/1.1\r\n";        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "Host: localhost\r\n";        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    auto headers = rs::httpserver::RequestHeaders::Create(buffer);
    ASSERT_TRUE(!headers);
}

TEST_F(RequestHeaderTests, test7) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = 
            "GET /test?redirect=true HTTP/1.1\r\n"
            "Host: localhost\r\n"
            "Accept: text/*\r\n"
            "Accept-Encoding: gzip, deflate\r\n"
            "Content-Type: text/plain\r\n"
            "Transfer-Encoding: chunked\r\n"
            "User-Agent: test\r\n"
            "Connection: Keep-Alive\r\n"
            "Content-Length: 127\r\n"
            "\r\n";
        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    auto headers = rs::httpserver::RequestHeaders::Create(buffer);
    ASSERT_TRUE(!!headers);
    
    ASSERT_STREQ("GET", headers->getMethod().c_str());
    ASSERT_STREQ("/test?redirect=true", headers->getRawUri().c_str());
    ASSERT_STREQ("/test", headers->getUri().c_str());
    ASSERT_STREQ("redirect=true", headers->getQueryString().c_str());
    ASSERT_STREQ("HTTP/1.1", headers->getVersion().c_str());
    ASSERT_STREQ("localhost", headers->getHost().c_str());
    ASSERT_STREQ("text/plain", headers->getContentType().c_str());
    ASSERT_STREQ("text/*", headers->getAccept().c_str());
    ASSERT_STREQ("gzip, deflate", headers->getAcceptEncoding().c_str());
    ASSERT_STREQ("chunked", headers->getTransferEncoding().c_str());
    ASSERT_STREQ("Keep-Alive", headers->getConnection().c_str());    
    ASSERT_STREQ("test", headers->getUserAgent().c_str());    
    ASSERT_EQ(127, headers->getContentLength());
    ASSERT_TRUE(headers->IsChunked());
}

TEST_F(RequestHeaderTests, test8) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = 
            "GET   /test?redirect=true  HTTP/1.1    \r\n"
            "Host:      localhost\r\n"
            "Accept: text/*   \r\n"
            "Accept-Encoding: gzip, deflate\r\n"
            "Content-Type: text/plain\r\n"
            "Transfer-Encoding: chunked\r\n"
            "User-Agent: test\r\n"
            "Connection   :      Keep-Alive     \r\n"
            "Content-Length: 127\r\n"
            "\r\n";
        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    auto headers = rs::httpserver::RequestHeaders::Create(buffer);
    ASSERT_TRUE(!!headers);
    
    ASSERT_STREQ("GET", headers->getMethod().c_str());
    ASSERT_STREQ("/test?redirect=true", headers->getRawUri().c_str());
    ASSERT_STREQ("/test", headers->getUri().c_str());
    ASSERT_STREQ("redirect=true", headers->getQueryString().c_str());
    ASSERT_STREQ("HTTP/1.1", headers->getVersion().c_str());
    ASSERT_STREQ("localhost", headers->getHost().c_str());
    ASSERT_STREQ("text/plain", headers->getContentType().c_str());
    ASSERT_STREQ("text/plain", headers->getHeader("content-type").c_str());
    ASSERT_STREQ("text/*", headers->getAccept().c_str());
    ASSERT_STREQ("gzip, deflate", headers->getAcceptEncoding().c_str());
    ASSERT_STREQ("chunked", headers->getTransferEncoding().c_str());
    ASSERT_STREQ("Keep-Alive", headers->getConnection().c_str());
    ASSERT_STREQ("test", headers->getUserAgent().c_str());
    ASSERT_EQ(127, headers->getContentLength());
    ASSERT_STREQ("127", headers->getHeader("content-length").c_str());
    ASSERT_TRUE(headers->IsChunked());
}

TEST_F(RequestHeaderTests, test10) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GE\r\n\r\n";
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    bool thrown = false;
    try {
        rs::httpserver::RequestHeaders::Create(buffer);        
    } catch (const rs::httpserver::HeaderMalformedException& ex) {
        ASSERT_TRUE(SanityCheckWhatMessage(ex.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(RequestHeaderTests, test11) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET / \r\n\r\n";
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    bool thrown = false;
    try {
        rs::httpserver::RequestHeaders::Create(buffer);        
    } catch (const rs::httpserver::HeaderMalformedException& ex) {
        ASSERT_TRUE(SanityCheckWhatMessage(ex.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(RequestHeaderTests, test12) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET / HTTP/1.\r\n\r\n";
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    bool thrown = false;
    try {
        rs::httpserver::RequestHeaders::Create(buffer);        
    } catch (const rs::httpserver::HeaderMalformedException& ex) {
        ASSERT_TRUE(SanityCheckWhatMessage(ex.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(RequestHeaderTests, test13) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET / HTTP/1.1\r\nHost\r\n\r\n";
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    bool thrown = false;
    try {
        rs::httpserver::RequestHeaders::Create(buffer);        
    } catch (const rs::httpserver::HeaderMalformedException& ex) {
        ASSERT_TRUE(SanityCheckWhatMessage(ex.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(RequestHeaderTests, test14) {
    rs::httpserver::HeaderBuffer buffer;
    buffer.Receive([](rs::httpserver::Stream::byte* buffer, int length, bool peek) {
        const char request[] = "GET /?test=%22true%22&simple=false&percent=%&hash=%23&malformed=%2&colon=%3a HTTP/1.1\r\nHost: localhost\r\n\r\n";        
        std::memcpy(buffer, request, sizeof(request) - 1);        
        return sizeof(request) - 1;
    });
    
    auto headers = rs::httpserver::RequestHeaders::Create(buffer);
    ASSERT_TRUE(!!headers);
    ASSERT_STREQ("GET", headers->getMethod().c_str());
    ASSERT_STREQ("/", headers->getUri().c_str());
    ASSERT_STREQ("/?test=%22true%22&simple=false&percent=%&hash=%23&malformed=%2&colon=%3a", headers->getRawUri().c_str());
    ASSERT_STREQ(R"(test="true"&simple=false&percent=%&hash=#&malformed=%2&colon=:)", headers->getQueryString().c_str());
    ASSERT_STREQ("HTTP/1.1", headers->getVersion().c_str());
    ASSERT_STREQ("localhost", headers->getHost().c_str());
}