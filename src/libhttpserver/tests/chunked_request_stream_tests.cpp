#include <gtest/gtest.h>

#include "../readable_string_stream.h"
#include "../chunked_request_stream.h"
#include "../exceptions.h"

class ChunkedRequestStreamTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        ResetBuffer();
    }
    
    virtual void TearDown() {
        
    }
    
    bool SanityCheckWhatMessage(const char* msg);
    
    void ResetBuffer() { std::fill_n(buffer_, sizeof(buffer_), resetValue_); }
    
    rs::httpserver::Stream::byte buffer_[1024];
    const rs::httpserver::Stream::byte resetValue_ = 0xff;
};

bool ChunkedRequestStreamTests::SanityCheckWhatMessage(const char* msg) {
    while (*msg != '\0') {
        if (*msg < 0x0d || *msg > 0x7e) {
            return false;
        }
        msg++;
    }
    return true;
}

TEST_F(ChunkedRequestStreamTests, testMethod) {
    rs::httpserver::ReadableStringStream requestStream("0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
}

TEST_F(ChunkedRequestStreamTests, testMethod2) {
    rs::httpserver::ReadableStringStream requestStream("0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_), true), 0);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
}

TEST_F(ChunkedRequestStreamTests, testMethod3) {
    rs::httpserver::ReadableStringStream requestStream("1\r\na\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_), true), 1);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 1);
    ASSERT_EQ(stream.getPosition(), 1);
    ASSERT_EQ(stream.getLength(), 1);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 1);
    ASSERT_EQ(stream.getLength(), 1);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], resetValue_);
}

TEST_F(ChunkedRequestStreamTests, testMethod4) {
    rs::httpserver::ReadableStringStream requestStream("3\r\nabc\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
        
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_), true), 3);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], 'b');
    ASSERT_EQ(buffer_[2], 'c');
    ASSERT_EQ(buffer_[3], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 3);
    ASSERT_EQ(stream.getPosition(), 3);
    ASSERT_EQ(stream.getLength(), 3);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], 'b');
    ASSERT_EQ(buffer_[2], 'c');
    ASSERT_EQ(buffer_[3], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 3);
    ASSERT_EQ(stream.getLength(), 3);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], 'b');
    ASSERT_EQ(buffer_[2], 'c');
    ASSERT_EQ(buffer_[3], resetValue_);
}

TEST_F(ChunkedRequestStreamTests, testMethod5) {
    rs::httpserver::ReadableStringStream requestStream("3\r\nabc\r\n3\r\npqr\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
        
    ASSERT_EQ(stream.Read(buffer_, 0, 3, true), 3);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], 'b');
    ASSERT_EQ(buffer_[2], 'c');
    ASSERT_EQ(buffer_[3], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, 3), 3);
    ASSERT_EQ(stream.getPosition(), 3);
    ASSERT_EQ(stream.getLength(), 3);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], 'b');
    ASSERT_EQ(buffer_[2], 'c');
    ASSERT_EQ(buffer_[3], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 3, sizeof(buffer_)), 3);
    ASSERT_EQ(stream.getPosition(), 6);
    ASSERT_EQ(stream.getLength(), 6);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], 'b');
    ASSERT_EQ(buffer_[2], 'c');
    ASSERT_EQ(buffer_[3], 'p');
    ASSERT_EQ(buffer_[4], 'q');
    ASSERT_EQ(buffer_[5], 'r');
    ASSERT_EQ(buffer_[6], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 6);
    ASSERT_EQ(stream.getLength(), 6);
    ASSERT_EQ(buffer_[0], 'a');
    ASSERT_EQ(buffer_[1], 'b');
    ASSERT_EQ(buffer_[2], 'c');
    ASSERT_EQ(buffer_[3], 'p');
    ASSERT_EQ(buffer_[4], 'q');
    ASSERT_EQ(buffer_[5], 'r');
    ASSERT_EQ(buffer_[6], resetValue_);
}

TEST_F(ChunkedRequestStreamTests, testMethod6) {
    rs::httpserver::ReadableStringStream requestStream("a\r\n0123456789\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_), true), 10);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 10);
    ASSERT_EQ(stream.getPosition(), 10);
    ASSERT_EQ(stream.getLength(), 10);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], resetValue_);    
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 10);
    ASSERT_EQ(stream.getLength(), 10);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], resetValue_);    
}

TEST_F(ChunkedRequestStreamTests, testMethod7) {
    rs::httpserver::ReadableStringStream requestStream("f\r\n012345678901234\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_), true), 15);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], '0');
    ASSERT_EQ(buffer_[11], '1');
    ASSERT_EQ(buffer_[12], '2');
    ASSERT_EQ(buffer_[13], '3');
    ASSERT_EQ(buffer_[14], '4');
    ASSERT_EQ(buffer_[15], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 15);
    ASSERT_EQ(stream.getPosition(), 15);
    ASSERT_EQ(stream.getLength(), 15);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], '0');
    ASSERT_EQ(buffer_[11], '1');
    ASSERT_EQ(buffer_[12], '2');
    ASSERT_EQ(buffer_[13], '3');
    ASSERT_EQ(buffer_[14], '4');
    ASSERT_EQ(buffer_[15], resetValue_); 
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 15);
    ASSERT_EQ(stream.getLength(), 15);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], '0');
    ASSERT_EQ(buffer_[11], '1');
    ASSERT_EQ(buffer_[12], '2');
    ASSERT_EQ(buffer_[13], '3');
    ASSERT_EQ(buffer_[14], '4');
    ASSERT_EQ(buffer_[15], resetValue_);   
}

TEST_F(ChunkedRequestStreamTests, testMethod8) {
    rs::httpserver::ReadableStringStream requestStream("C\r\n012345678901\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_), true), 12);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], '0');
    ASSERT_EQ(buffer_[11], '1');
    ASSERT_EQ(buffer_[12], resetValue_);
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 12);
    ASSERT_EQ(stream.getPosition(), 12);
    ASSERT_EQ(stream.getLength(), 12);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], '0');
    ASSERT_EQ(buffer_[11], '1');
    ASSERT_EQ(buffer_[12], resetValue_); 
    
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 12);
    ASSERT_EQ(stream.getLength(), 12);
    ASSERT_EQ(buffer_[0], '0');
    ASSERT_EQ(buffer_[1], '1');
    ASSERT_EQ(buffer_[2], '2');
    ASSERT_EQ(buffer_[3], '3');
    ASSERT_EQ(buffer_[4], '4');
    ASSERT_EQ(buffer_[5], '5');
    ASSERT_EQ(buffer_[6], '6');
    ASSERT_EQ(buffer_[7], '7');
    ASSERT_EQ(buffer_[8], '8');
    ASSERT_EQ(buffer_[9], '9');
    ASSERT_EQ(buffer_[10], '0');
    ASSERT_EQ(buffer_[11], '1');
    ASSERT_EQ(buffer_[12], resetValue_);   
}

TEST_F(ChunkedRequestStreamTests, testMethod9) {    
    rs::httpserver::ReadableStringStream requestStream("1;Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc auctor erat in porta aliquam. Aliquam at semper augue, quis mattis ipsum.\r\na\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    bool thrown = false;
    try {
        stream.Read(buffer_, 0, sizeof(buffer_));
    } catch (const rs::httpserver::ChunkedRequestHeaderException& ex) {
        ASSERT_TRUE(SanityCheckWhatMessage(ex.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(ChunkedRequestStreamTests, testMethod10) {
    rs::httpserver::ReadableStringStream requestStream("1;Lorem ipsum dolor sit amet, consectetur adipiscing elit. ");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 0);
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    
    requestStream.AppendData("Nunc auctor erat in porta aliquam. Aliquam at semper augue, quis mattis ipsum.\r\na\r\n0\r\n\r\n");
    ASSERT_EQ(stream.getPosition(), 0);
    ASSERT_EQ(stream.getLength(), 0);
    
    ASSERT_THROW({                
        stream.Read(buffer_, 0, sizeof(buffer_));                
    }, rs::httpserver::ChunkedRequestHeaderException);
}

TEST_F(ChunkedRequestStreamTests, testMethod11) {
    rs::httpserver::ReadableStringStream requestStream("\11\r\nthis is a placebo\r\n0\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);    
    
    bool thrown = false;
    try {                
        stream.Write(buffer_, 0, sizeof(buffer_));                
    } catch (const rs::httpserver::InvalidStreamOperationException& ex) {
        ASSERT_TRUE(SanityCheckWhatMessage(ex.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(ChunkedRequestStreamTests, testMethod12) {    
    rs::httpserver::ReadableStringStream requestStream("87\r\nLorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc auctor erat in porta aliquam. Aliquam at semper augue, quis mattis ipsum.\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    ASSERT_EQ(stream.Read(buffer_, 0, sizeof(buffer_)), 135);
    ASSERT_EQ(stream.getPosition(), 135);
    ASSERT_EQ(stream.getLength(), 135);
}

TEST_F(ChunkedRequestStreamTests, testMethod13) {
    rs::httpserver::ReadableStringStream requestStream("");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    stream.Flush();
    ASSERT_TRUE(true);
}