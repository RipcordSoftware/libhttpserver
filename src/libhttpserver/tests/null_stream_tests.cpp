#include <gtest/gtest.h>

#include "../null_stream.h"

class NullStreamTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
    rs::httpserver::Stream::byte buffer[1024];
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
    
    ASSERT_EQ(0, stream.Read(buffer, 0, sizeof(buffer), true));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());    
        
    ASSERT_EQ(0, stream.Read(buffer, 0, sizeof(buffer), false));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());    
}

TEST_F(NullStreamTests, test3) {
    rs::httpserver::NullStream stream;
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());
    
    ASSERT_EQ(0, stream.Write(buffer, 0, sizeof(buffer)));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());    
}

TEST_F(NullStreamTests, test4) {
    rs::httpserver::NullStream stream;
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());
    
    ASSERT_EQ(0, stream.Write(buffer, 0, sizeof(buffer)));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());   
    
    ASSERT_EQ(0, stream.Read(buffer, 0, sizeof(buffer), false));
    ASSERT_EQ(0, stream.getPosition());
    ASSERT_EQ(0, stream.getLength());    
}