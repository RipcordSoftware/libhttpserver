#include <gtest/gtest.h>

#include "../null_stream.h"

class NullStreamTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
    rs::httpserver::Stream::byte buffer_[1024];
};

TEST_F(NullStreamTests, test1) {
    rs::httpserver::NullStream stream;
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());
    
    stream.Flush();
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());  
}

TEST_F(NullStreamTests, test2) {
    rs::httpserver::NullStream stream;
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());
    
    ASSERT_EQ(0, stream.Read(buffer_, 0, sizeof(buffer_), true));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());    
        
    ASSERT_EQ(0, stream.Read(buffer_, 0, sizeof(buffer_), false));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());    
}

TEST_F(NullStreamTests, test3) {
    rs::httpserver::NullStream stream;
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());
    
    ASSERT_EQ(0, stream.Write(buffer_, 0, sizeof(buffer_)));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());    
}

TEST_F(NullStreamTests, test4) {
    rs::httpserver::NullStream stream;
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());
    
    ASSERT_EQ(0, stream.Write(buffer_, 0, sizeof(buffer_)));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());   
    
    ASSERT_EQ(0, stream.Read(buffer_, 0, sizeof(buffer_), false));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());    
}