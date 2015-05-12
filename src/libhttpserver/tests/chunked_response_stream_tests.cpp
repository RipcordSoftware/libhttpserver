#include <gtest/gtest.h>

#include "../writable_string_stream.h"
#include "../chunked_response_stream.h"
#include "../exceptions.h"
#include "../config.h"

class ChunkedResponseStreamTests : public ::testing::Test {
protected:
    ChunkedResponseStreamTests() {        
        std::fill_n(buffer1_, sizeof(buffer1_), '1');
        std::fill_n(buffer2_, sizeof(buffer2_), '2');
    }
    
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
    bool SanityCheckWhatMessage(const char* msg);    
    
    rs::httpserver::Stream::byte buffer1_[2048];
    rs::httpserver::Stream::byte buffer2_[sizeof(buffer1_) * 2];
};

bool ChunkedResponseStreamTests::SanityCheckWhatMessage(const char* msg) {
    while (*msg != '\0') {
        if (*msg < 0x0d || *msg > 0x7e) {
            return false;
        }
        msg++;
    }
    return true;
}

TEST_F(ChunkedResponseStreamTests, test0) {
    ASSERT_EQ(sizeof(buffer1_), rs::httpserver::Config::MaxResponseChunkSize);
    ASSERT_EQ(sizeof(buffer2_), rs::httpserver::Config::MaxResponseChunkSize * 2);
}

TEST_F(ChunkedResponseStreamTests, test1) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    
    ASSERT_EQ(0, responseStream.Write(nullptr, 0, 0));
    ASSERT_EQ(0, responseStream.getLength());
    ASSERT_EQ(0, responseStream.getPosition());
    
    ASSERT_EQ(0, stream.getLength());
    ASSERT_EQ(0, stream.getPosition());
}

TEST_F(ChunkedResponseStreamTests, test2) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    
    ASSERT_EQ(0, responseStream.Write(nullptr, 0, 0));
    ASSERT_EQ(0, responseStream.getLength());
    ASSERT_EQ(0, responseStream.getPosition());
    responseStream.Flush();
    ASSERT_EQ(0, responseStream.getLength());
    ASSERT_EQ(0, responseStream.getPosition());
    
    ASSERT_EQ(5, stream.getLength());
    ASSERT_EQ(5, stream.getPosition());
    ASSERT_STREQ("0\r\n\r\n", stream.str().c_str());
}

TEST_F(ChunkedResponseStreamTests, test3) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    
    ASSERT_EQ(4, responseStream.Write((const rs::httpserver::Stream::byte*)"1234", 0, 4));
    ASSERT_EQ(4, responseStream.getLength());
    ASSERT_EQ(4, responseStream.getPosition());
    responseStream.Flush();
    ASSERT_EQ(4, responseStream.getLength());
    ASSERT_EQ(4, responseStream.getPosition());
    
    ASSERT_EQ(14, stream.getLength());
    ASSERT_EQ(14, stream.getPosition());
    ASSERT_STREQ("4\r\n1234\r\n0\r\n\r\n", stream.str().c_str());
}

TEST_F(ChunkedResponseStreamTests, test4) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    
    ASSERT_EQ(4, responseStream.Write((const rs::httpserver::Stream::byte*)"1234", 0, 4));
    ASSERT_EQ(4, responseStream.getLength());
    ASSERT_EQ(4, responseStream.getPosition());    
    
    ASSERT_EQ(4, responseStream.Write((const rs::httpserver::Stream::byte*)"5678", 0, 4));
    ASSERT_EQ(8, responseStream.getLength());
    ASSERT_EQ(8, responseStream.getPosition());
    responseStream.Flush();
    ASSERT_EQ(8, responseStream.getLength());
    ASSERT_EQ(8, responseStream.getPosition());
    
    ASSERT_EQ(23, stream.getLength());
    ASSERT_EQ(23, stream.getPosition());
    ASSERT_STREQ("4\r\n1234\r\n4\r\n5678\r\n0\r\n\r\n", stream.str().c_str());
}

TEST_F(ChunkedResponseStreamTests, test5) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    
    ASSERT_EQ(8, responseStream.Write((const rs::httpserver::Stream::byte*)"12345678", 0, 8));
    ASSERT_EQ(8, responseStream.getLength());
    ASSERT_EQ(8, responseStream.getPosition());    
    
    responseStream.Flush();
    ASSERT_EQ(8, responseStream.getLength());
    ASSERT_EQ(8, responseStream.getPosition());
    
    ASSERT_EQ(18, stream.getLength());
    ASSERT_EQ(18, stream.getPosition());
    ASSERT_STREQ("8\r\n12345678\r\n0\r\n\r\n", stream.str().c_str());
}

TEST_F(ChunkedResponseStreamTests, test6) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    
    ASSERT_EQ(sizeof(buffer1_), responseStream.Write(buffer1_, 0, sizeof(buffer1_)));
    ASSERT_EQ(sizeof(buffer1_), responseStream.getLength());
    ASSERT_EQ(sizeof(buffer1_), responseStream.getPosition());
    
    ASSERT_EQ(3 + 2 + sizeof(buffer1_) + 2, stream.getLength());
    ASSERT_EQ(3 + 2 + sizeof(buffer1_) + 2, stream.getPosition());
    
    auto& str = stream.str();
    ASSERT_EQ('8', str[0]);
    ASSERT_EQ('0', str[1]);
    ASSERT_EQ('0', str[2]);
    ASSERT_EQ('\r', str[3]);
    ASSERT_EQ('\n', str[4]);
    ASSERT_EQ(buffer1_[0], str[5]);
    
    ASSERT_EQ('\n', *(str.cend() - 1));
    ASSERT_EQ('\r', *(str.cend() - 2));
    ASSERT_EQ(buffer1_[sizeof(buffer1_) - 1], *(str.cend() - 3));
    
    responseStream.Flush();
    ASSERT_EQ(3 + 2 + sizeof(buffer1_) + 2 + 5, stream.getLength());
    ASSERT_EQ(3 + 2 + sizeof(buffer1_) + 2 + 5, stream.getPosition());
    
    ASSERT_EQ('\n', *(str.cend() - 1));
    ASSERT_EQ('\r', *(str.cend() - 2));
    ASSERT_EQ('\n', *(str.cend() - 3));
    ASSERT_EQ('\r', *(str.cend() - 4));
    ASSERT_EQ('0', *(str.cend() - 5));
    ASSERT_EQ('\n', *(str.cend() - 6));
    ASSERT_EQ('\r', *(str.cend() - 7));
    ASSERT_EQ(buffer1_[sizeof(buffer1_) - 1], *(str.cend() - 8));
}

TEST_F(ChunkedResponseStreamTests, test7) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    
    ASSERT_EQ(sizeof(buffer2_), responseStream.Write(buffer2_, 0, sizeof(buffer2_)));
    ASSERT_EQ(sizeof(buffer2_), responseStream.getLength());
    ASSERT_EQ(sizeof(buffer2_), responseStream.getPosition());
    
    ASSERT_EQ((3 + 2 + (sizeof(buffer2_) / 2) + 2) * 2, stream.getLength());
    ASSERT_EQ((3 + 2 + (sizeof(buffer2_) / 2) + 2) * 2, stream.getPosition());
    
    auto& str = stream.str();
    ASSERT_EQ('8', str[0]);
    ASSERT_EQ('0', str[1]);
    ASSERT_EQ('0', str[2]);
    ASSERT_EQ('\r', str[3]);
    ASSERT_EQ('\n', str[4]);
    ASSERT_EQ(buffer2_[0], str[5]);
    
    ASSERT_EQ('\n', *(str.cend() - 1));
    ASSERT_EQ('\r', *(str.cend() - 2));
    
    responseStream.Flush();
    ASSERT_EQ(((3 + 2 + (sizeof(buffer2_) / 2) + 2) * 2) + 5, stream.getLength());
    ASSERT_EQ(((3 + 2 + (sizeof(buffer2_) / 2) + 2) * 2) + 5, stream.getPosition());
    
    ASSERT_EQ('\n', *(str.cend() - 1));
    ASSERT_EQ('\r', *(str.cend() - 2));
    ASSERT_EQ('\n', *(str.cend() - 3));
    ASSERT_EQ('\r', *(str.cend() - 4));
    ASSERT_EQ('0', *(str.cend() - 5));
    ASSERT_EQ('\n', *(str.cend() - 6));
    ASSERT_EQ('\r', *(str.cend() - 7));
    ASSERT_EQ(buffer2_[sizeof(buffer2_) - 1], *(str.cend() - 8));
}

TEST_F(ChunkedResponseStreamTests, test8) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    responseStream.Flush();
    ASSERT_TRUE(true);
}

TEST_F(ChunkedResponseStreamTests, test9) {
    rs::httpserver::WritableStringStream stream;
    rs::httpserver::ChunkedResponseStream responseStream(stream);
    
    bool thrown = false;
    try {
        responseStream.Read(nullptr, 0, 0);
    } catch (rs::httpserver::InvalidStreamOperationException& ex) {
        ASSERT_TRUE(SanityCheckWhatMessage(ex.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}