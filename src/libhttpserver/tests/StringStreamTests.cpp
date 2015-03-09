#include <algorithm>

#include <gtest/gtest.h>

#include "../string_stream.h"

class StringStreamTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        ResetBuffer();
    }
    
    virtual void TearDown() {
        
    }
    
    void ResetBuffer() { std::fill_n(buffer_, sizeof(buffer_), resetValue_); }
    
    const rs::httpserver::Stream::byte resetValue_ = 0xff;
    rs::httpserver::Stream::byte buffer_[1024];
};

TEST_F(StringStreamTests, TestEmptyStream) {
    rs::httpserver::StringStream stream("");
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(stream.getPosition(), 0);
    
    int bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(stream.getPosition(), 0);
    
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(stream.getPosition(), 0);
    
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_), true);
    ASSERT_EQ(bytesRead, 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(stream.getPosition(), 0);    
}

TEST_F(StringStreamTests, TestShortStream1) {
    ASSERT_EQ(buffer_[0], resetValue_);
    
    std::string testData = "1234";
    rs::httpserver::StringStream stream("1234");
    ASSERT_EQ(stream.getLength(), 4);
    ASSERT_EQ(stream.getPosition(), 0);
    
    // read all the available data
    int bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 4);    
    ASSERT_EQ(stream.getLength(), 4);
    ASSERT_EQ(stream.getPosition(), 4);
    ASSERT_EQ(buffer_[0], testData[0]);
    ASSERT_EQ(buffer_[1], testData[1]);
    ASSERT_EQ(buffer_[2], testData[2]);
    ASSERT_EQ(buffer_[3], testData[3]);
    ASSERT_EQ(buffer_[4], resetValue_);
    
    // read over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 0);
    ASSERT_EQ(stream.getLength(), 4);
    ASSERT_EQ(stream.getPosition(), 4);
    ASSERT_EQ(buffer_[0], testData[0]);
    ASSERT_EQ(buffer_[1], testData[1]);
    ASSERT_EQ(buffer_[2], testData[2]);
    ASSERT_EQ(buffer_[3], testData[3]);
    ASSERT_EQ(buffer_[4], resetValue_);
    
    // peek over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_), true);
    ASSERT_EQ(bytesRead, 0);
    ASSERT_EQ(stream.getLength(), 4);
    ASSERT_EQ(stream.getPosition(), 4);
    ASSERT_EQ(buffer_[0], testData[0]);
    ASSERT_EQ(buffer_[1], testData[1]);
    ASSERT_EQ(buffer_[2], testData[2]);
    ASSERT_EQ(buffer_[3], testData[3]);
    ASSERT_EQ(buffer_[4], resetValue_);
}

TEST_F(StringStreamTests, TestShortStream2) {
    ASSERT_EQ(buffer_[0], resetValue_);
    
    std::string testData = "12345678";
    rs::httpserver::StringStream stream(testData);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 0);
    
    // read the first N bytes of the available data
    int bytesRead = stream.Read(buffer_, 0, 4);
    ASSERT_EQ(bytesRead, 4);    
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 4);
    ASSERT_EQ(buffer_[0], testData[0]);
    ASSERT_EQ(buffer_[1], testData[1]);
    ASSERT_EQ(buffer_[2], testData[2]);
    ASSERT_EQ(buffer_[3], testData[3]);
    ASSERT_EQ(buffer_[4], resetValue_);
    
    // read the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 4);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 8);
    ASSERT_EQ(buffer_[0], testData[4]);
    ASSERT_EQ(buffer_[1], testData[5]);
    ASSERT_EQ(buffer_[2], testData[6]);
    ASSERT_EQ(buffer_[3], testData[7]);
    ASSERT_EQ(buffer_[4], resetValue_);
    
    // read over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 0);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 8);
    ASSERT_EQ(buffer_[0], testData[4]);
    ASSERT_EQ(buffer_[1], testData[5]);
    ASSERT_EQ(buffer_[2], testData[6]);
    ASSERT_EQ(buffer_[3], testData[7]);
    ASSERT_EQ(buffer_[4], resetValue_);
    
    // peek over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_), true);
    ASSERT_EQ(bytesRead, 0);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 8);
    ASSERT_EQ(buffer_[0], testData[4]);
    ASSERT_EQ(buffer_[1], testData[5]);
    ASSERT_EQ(buffer_[2], testData[6]);
    ASSERT_EQ(buffer_[3], testData[7]);
    ASSERT_EQ(buffer_[4], resetValue_);
}

TEST_F(StringStreamTests, TestShortStream3) {
    ASSERT_EQ(buffer_[0], resetValue_);
    
    std::string testData = "12345678";
    rs::httpserver::StringStream stream(testData);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 0);
    
    // peek the first N bytes of the available data
    int bytesRead = stream.Read(buffer_, 0, 4, true);
    ASSERT_EQ(bytesRead, 4);    
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(buffer_[0], testData[0]);
    ASSERT_EQ(buffer_[1], testData[1]);
    ASSERT_EQ(buffer_[2], testData[2]);
    ASSERT_EQ(buffer_[3], testData[3]);
    ASSERT_EQ(buffer_[4], resetValue_);
    
    // peek all remaining bytes of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_), true);
    ASSERT_EQ(bytesRead, 8);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(buffer_[0], testData[0]);
    ASSERT_EQ(buffer_[1], testData[1]);
    ASSERT_EQ(buffer_[2], testData[2]);
    ASSERT_EQ(buffer_[3], testData[3]);
    ASSERT_EQ(buffer_[4], testData[4]);
    ASSERT_EQ(buffer_[5], testData[5]);
    ASSERT_EQ(buffer_[6], testData[6]);
    ASSERT_EQ(buffer_[7], testData[7]);
    ASSERT_EQ(buffer_[8], resetValue_);
    
    // read all bytes of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 8);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 8);
    ASSERT_EQ(buffer_[0], testData[0]);
    ASSERT_EQ(buffer_[1], testData[1]);
    ASSERT_EQ(buffer_[2], testData[2]);
    ASSERT_EQ(buffer_[3], testData[3]);
    ASSERT_EQ(buffer_[4], testData[4]);
    ASSERT_EQ(buffer_[5], testData[5]);
    ASSERT_EQ(buffer_[6], testData[6]);
    ASSERT_EQ(buffer_[7], testData[7]);
    ASSERT_EQ(buffer_[8], resetValue_);
}

TEST_F(StringStreamTests, TestShortStream4) {
    ASSERT_EQ(buffer_[0], resetValue_);
    
    std::string testData = "12345678";
    rs::httpserver::StringStream stream(testData);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 0);
    
    // read the first N bytes of the available data at offset M
    int bytesRead = stream.Read(buffer_, 4, 4);
    ASSERT_EQ(bytesRead, 4);    
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 4);
    ASSERT_EQ(buffer_[0], resetValue_);
    ASSERT_EQ(buffer_[1], resetValue_);
    ASSERT_EQ(buffer_[2], resetValue_);
    ASSERT_EQ(buffer_[3], resetValue_);
    ASSERT_EQ(buffer_[4], testData[0]);
    ASSERT_EQ(buffer_[5], testData[1]);
    ASSERT_EQ(buffer_[6], testData[2]);
    ASSERT_EQ(buffer_[7], testData[3]);
    ASSERT_EQ(buffer_[8], resetValue_);
    
    // read the next N bytes of the available data at offset 0
    bytesRead = stream.Read(buffer_, 0, 4);
    ASSERT_EQ(bytesRead, 4);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 8);
    ASSERT_EQ(buffer_[0], testData[4]);
    ASSERT_EQ(buffer_[1], testData[5]);
    ASSERT_EQ(buffer_[2], testData[6]);
    ASSERT_EQ(buffer_[3], testData[7]);
    ASSERT_EQ(buffer_[4], testData[0]);
    ASSERT_EQ(buffer_[5], testData[1]);
    ASSERT_EQ(buffer_[6], testData[2]);
    ASSERT_EQ(buffer_[7], testData[3]);
    ASSERT_EQ(buffer_[8], resetValue_);
 
    // read over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 0);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 8);
    ASSERT_EQ(buffer_[0], testData[4]);
    ASSERT_EQ(buffer_[1], testData[5]);
    ASSERT_EQ(buffer_[2], testData[6]);
    ASSERT_EQ(buffer_[3], testData[7]);
    ASSERT_EQ(buffer_[4], testData[0]);
    ASSERT_EQ(buffer_[5], testData[1]);
    ASSERT_EQ(buffer_[6], testData[2]);
    ASSERT_EQ(buffer_[7], testData[3]);
    ASSERT_EQ(buffer_[8], resetValue_);
}

TEST_F(StringStreamTests, TestShortStream5) {
    ASSERT_EQ(buffer_[0], resetValue_);
    
    std::string testData = "12345678";
    rs::httpserver::StringStream stream(testData);
    ASSERT_EQ(stream.getLength(), 8);
    ASSERT_EQ(stream.getPosition(), 0);
    
    stream.AppendData("90123456");
    ASSERT_EQ(stream.getLength(), 16);
    ASSERT_EQ(stream.getPosition(), 0);
    
    // read the first N bytes of the available data at offset M
    int bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 16);    
    ASSERT_EQ(stream.getLength(), 16);
    ASSERT_EQ(stream.getPosition(), 16);
    
    stream.AppendData("78901234");
    ASSERT_EQ(stream.getLength(), 24);
    ASSERT_EQ(stream.getPosition(), 16);
    
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    ASSERT_EQ(bytesRead, 8);    
    ASSERT_EQ(stream.getLength(), 24);
    ASSERT_EQ(stream.getPosition(), 24);
}
