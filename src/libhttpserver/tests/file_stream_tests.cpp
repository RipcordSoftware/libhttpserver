#include <gtest/gtest.h>

#include <ctime>

#include "../file_stream.h"

class FileStreamTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
    bool SanityCheckWhatMessage(const char* msg);
    
    rs::httpserver::Stream::byte buffer_[4096];
};

bool FileStreamTests::SanityCheckWhatMessage(const char* msg) {
    while (*msg != '\0') {
        if (*msg < 0x0d || *msg > 0x7e) {
            return false;
        }
        msg++;
    }
    return true;
}

TEST_F(FileStreamTests, test1) {
    ASSERT_TRUE(rs::httpserver::FileStream::ValidatePath("/"));
    ASSERT_TRUE(rs::httpserver::FileStream::ValidatePath("/abc"));
    ASSERT_TRUE(rs::httpserver::FileStream::ValidatePath("/abc/pqr"));
    ASSERT_TRUE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz"));
}

TEST_F(FileStreamTests, test2) {
    ASSERT_TRUE(rs::httpserver::FileStream::ValidatePath("/abc/.."));
    ASSERT_TRUE(rs::httpserver::FileStream::ValidatePath("/abc/../pqr"));
    ASSERT_TRUE(rs::httpserver::FileStream::ValidatePath("/abc/../pqr/../xyz"));
}

TEST_F(FileStreamTests, test3) {
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/../../"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/../../../"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/../../../../"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/../../../../../"));
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/../../abc/"));
}

TEST_F(FileStreamTests, test3b) {
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("%2fabc%2f..%2f..%2f"));
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc%2Fpqr/..%2f..%2F../"));
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz%2F../..%2F../..%2f"));
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("%2fabc/pqr%2fxyz/../../..%2f../../"));
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/..%2F../abc/"));
}

TEST_F(FileStreamTests, test4) {
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/%2e%2e/%2e%2e/"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/%2e%2e/%2e%2e/%2e%2e/"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/%2e%2e/%2e%2e/%2e%2e/%2e%2e/"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/%2e%2e/%2e%2e/%2e%2e/%2e%2e/%2e%2e/"));
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/%2e%2e/%2e%2e/abc/"));
}

TEST_F(FileStreamTests, test5) {
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/%2E%2E/%2E%2E/"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/%2e%2e/%2E%2E/%2e%2e/"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/%2e%2e/%2e%2e/%2e%2e/%2E%2E/"));    
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/%2E%2E/%2e%2e/%2E%2E/%2E%2E/%2e%2e/"));
    ASSERT_FALSE(rs::httpserver::FileStream::ValidatePath("/abc/%2e%2e/%2E%2E/abc/"));
}

TEST_F(FileStreamTests, test6) {
    ASSERT_TRUE(rs::httpserver::FileStream::Exists("rfc2616.txt", false));
}

TEST_F(FileStreamTests, test7) {
    rs::httpserver::FileStream stream("rfc2616.txt", false);
    ASSERT_TRUE(stream);
    ASSERT_EQ(422279, stream.getLength());
    
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(sizeof(buffer_), stream.Read(buffer_, 0, sizeof(buffer_)));
    ASSERT_EQ(sizeof(buffer_), stream.getPosition());
    
    ASSERT_EQ(sizeof(buffer_), stream.Read(buffer_, 0, sizeof(buffer_), true));
    ASSERT_EQ(sizeof(buffer_), stream.getPosition());
}

TEST_F(FileStreamTests, test8) {
    rs::httpserver::FileStream stream("rfc2616.txt", false);
    ASSERT_TRUE(stream);
    ASSERT_EQ(422279, stream.getLength());
    ASSERT_EQ(0, stream.getPosition());
    
    int blocks = 422279 / sizeof(buffer_);
    int overflow = 422279 % sizeof(buffer_);
    int position = 0;
    
    for (int i = 0; i < blocks; i++) {
        ASSERT_EQ(sizeof(buffer_), stream.Read(buffer_, 0, sizeof(buffer_)));
        position += sizeof(buffer_);
        ASSERT_EQ(position, stream.getPosition());
    }
    
    if (overflow > 0) {
        ASSERT_EQ(overflow, stream.Read(buffer_, 0, overflow));
        position += overflow;
        ASSERT_EQ(position, stream.getPosition());
    }   
    
    ASSERT_EQ(0, stream.Read(buffer_, 0, sizeof(buffer_)));
}

TEST_F(FileStreamTests, test9) {
    rs::httpserver::FileStream stream("rfc2616.txt", false);
    ASSERT_TRUE(stream);
    
    bool thrown = false;
    try {
        stream.Write(buffer_, 0, sizeof(buffer_));
    } catch (const rs::httpserver::InvalidStreamOperationException& ex) {
        ASSERT_TRUE(ex.what());
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(FileStreamTests, test10) {
    rs::httpserver::FileStream stream("rfc2616.txt", false);
    ASSERT_TRUE(stream);
    
    stream.Flush();
    ASSERT_TRUE(true);
}

TEST_F(FileStreamTests, test11) {
    rs::httpserver::FileStream stream("rfc2616.txt", false);
    ASSERT_TRUE(stream);
    
    auto time = stream.getLastModifiedTime();
    ASSERT_TRUE(!!time);
    ASSERT_LE(2015, std::gmtime(time.get_ptr())->tm_year + 1900);
}