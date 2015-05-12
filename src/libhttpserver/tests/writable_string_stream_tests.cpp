#include <gtest/gtest.h>

#include "../writable_string_stream.h"

class WritableStringStreamTests : public ::testing::Test {
protected:
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
        
    }
    
    bool SanityCheckWhatMessage(const char* msg);
};

bool WritableStringStreamTests::SanityCheckWhatMessage(const char* msg) {
    while (*msg != '\0') {
        if (*msg < 0x0d || *msg > 0x7e) {
            return false;
        }
        msg++;
    }
    return true;
}

TEST_F(WritableStringStreamTests, test1) {
    rs::httpserver::WritableStringStream stream;
    ASSERT_EQ(0, stream.getLength());
    ASSERT_EQ(0, stream.getPosition());
}

TEST_F(WritableStringStreamTests, test2) {
    rs::httpserver::WritableStringStream stream;
    stream.Write("1234", 0, 4);
    
    ASSERT_EQ(4, stream.getLength());
    ASSERT_EQ(4, stream.getPosition());
    ASSERT_STREQ("1234", stream.str().c_str());
}

TEST_F(WritableStringStreamTests, test3) {
    rs::httpserver::WritableStringStream stream;
    stream.Write("1234", 0, 4);
    
    ASSERT_EQ(4, stream.getLength());
    ASSERT_EQ(4, stream.getPosition());
    ASSERT_STREQ("1234", stream.str().c_str());
    
    stream.Write("5678", 0, 4);
    
    ASSERT_EQ(8, stream.getLength());
    ASSERT_EQ(8, stream.getPosition());
    ASSERT_STREQ("12345678", stream.str().c_str());
}

TEST_F(WritableStringStreamTests, test4) {
    rs::httpserver::WritableStringStream stream;
    stream.Write("1234", 0, 4);
    ASSERT_EQ(4, stream.getLength());
    ASSERT_EQ(4, stream.getPosition());
    
    bool thrown = false;
    try {
        rs::httpserver::Stream::byte buffer[256];
        stream.Read(buffer, 0, sizeof(buffer));
    } catch (const rs::httpserver::InvalidStreamOperationException& ex) {
        ASSERT_TRUE(SanityCheckWhatMessage(ex.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(WritableStringStreamTests, test5) {
    rs::httpserver::WritableStringStream stream;
    stream.Flush();
    ASSERT_TRUE(true);
}