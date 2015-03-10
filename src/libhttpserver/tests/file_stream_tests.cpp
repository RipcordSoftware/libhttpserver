#include <gtest/gtest.h>

#include "../file_stream.h"

class FileStreamTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }                
};

TEST_F(FileStreamTests, test1) {
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/"), true);
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc"), true);
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr"), true);
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz"), true);
}

TEST_F(FileStreamTests, test2) {
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/.."), true);
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/../pqr"), true);
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/../pqr/../xyz"), true);
}

TEST_F(FileStreamTests, test3) {
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/../../"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/../../../"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/../../../../"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/../../../../../"), false);
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/../../abc/"), false);
}

TEST_F(FileStreamTests, test4) {
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/%2e%2e/%2e%2e/"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/%2e%2e/%2e%2e/%2e%2e/"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/%2e%2e/%2e%2e/%2e%2e/%2e%2e/"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/%2e%2e/%2e%2e/%2e%2e/%2e%2e/%2e%2e/"), false);
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/%2e%2e/%2e%2e/abc/"), false);
}

TEST_F(FileStreamTests, test5) {
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/%2E%2E/%2E%2E/"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/%2e%2e/%2E%2E/%2e%2e/"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/%2e%2e/%2e%2e/%2e%2e/%2E%2E/"), false);    
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/pqr/xyz/%2E%2E/%2e%2e/%2E%2E/%2E%2E/%2e%2e/"), false);
    ASSERT_EQ(rs::httpserver::FileStream::ValidatePath("/abc/%2e%2e/%2E%2E/abc/"), false);
}