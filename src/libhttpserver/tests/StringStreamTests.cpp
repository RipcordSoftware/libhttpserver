#include "StringStreamTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(StringStreamTests);

StringStreamTests::StringStreamTests() {
}

StringStreamTests::~StringStreamTests() {
}

void StringStreamTests::setUp() {
    ResetBuffer();
}

void StringStreamTests::tearDown() {
}

void StringStreamTests::TestEmptyStream() {
    rs::httpserver::StringStream stream("");
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    int bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_), true);
    CPPUNIT_ASSERT(bytesRead == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
}


void StringStreamTests::TestShortStream1() {
    CPPUNIT_ASSERT(buffer_[0] == resetValue_);
    
    std::string testData = "1234";
    rs::httpserver::StringStream stream("1234");
    CPPUNIT_ASSERT(stream.getLength() == 4);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    // read all the available data
    int bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 4);    
    CPPUNIT_ASSERT(stream.getLength() == 4);
    CPPUNIT_ASSERT(stream.getPosition() == 4);
    CPPUNIT_ASSERT(buffer_[0] == testData[0]);
    CPPUNIT_ASSERT(buffer_[1] == testData[1]);
    CPPUNIT_ASSERT(buffer_[2] == testData[2]);
    CPPUNIT_ASSERT(buffer_[3] == testData[3]);
    CPPUNIT_ASSERT(buffer_[4] == resetValue_);
    
    // read over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 0);
    CPPUNIT_ASSERT(stream.getLength() == 4);
    CPPUNIT_ASSERT(stream.getPosition() == 4);
    CPPUNIT_ASSERT(buffer_[0] == testData[0]);
    CPPUNIT_ASSERT(buffer_[1] == testData[1]);
    CPPUNIT_ASSERT(buffer_[2] == testData[2]);
    CPPUNIT_ASSERT(buffer_[3] == testData[3]);
    CPPUNIT_ASSERT(buffer_[4] == resetValue_);
    
    // peek over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_), true);
    CPPUNIT_ASSERT(bytesRead == 0);
    CPPUNIT_ASSERT(stream.getLength() == 4);
    CPPUNIT_ASSERT(stream.getPosition() == 4);
    CPPUNIT_ASSERT(buffer_[0] == testData[0]);
    CPPUNIT_ASSERT(buffer_[1] == testData[1]);
    CPPUNIT_ASSERT(buffer_[2] == testData[2]);
    CPPUNIT_ASSERT(buffer_[3] == testData[3]);
    CPPUNIT_ASSERT(buffer_[4] == resetValue_);
}

void StringStreamTests::TestShortStream2() {
    CPPUNIT_ASSERT(buffer_[0] == resetValue_);
    
    std::string testData = "12345678";
    rs::httpserver::StringStream stream(testData);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    // read the first N bytes of the available data
    int bytesRead = stream.Read(buffer_, 0, 4);
    CPPUNIT_ASSERT(bytesRead == 4);    
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 4);
    CPPUNIT_ASSERT(buffer_[0] == testData[0]);
    CPPUNIT_ASSERT(buffer_[1] == testData[1]);
    CPPUNIT_ASSERT(buffer_[2] == testData[2]);
    CPPUNIT_ASSERT(buffer_[3] == testData[3]);
    CPPUNIT_ASSERT(buffer_[4] == resetValue_);
    
    // read the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 4);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 8);
    CPPUNIT_ASSERT(buffer_[0] == testData[4]);
    CPPUNIT_ASSERT(buffer_[1] == testData[5]);
    CPPUNIT_ASSERT(buffer_[2] == testData[6]);
    CPPUNIT_ASSERT(buffer_[3] == testData[7]);
    CPPUNIT_ASSERT(buffer_[4] == resetValue_);
    
    // read over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 0);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 8);
    CPPUNIT_ASSERT(buffer_[0] == testData[4]);
    CPPUNIT_ASSERT(buffer_[1] == testData[5]);
    CPPUNIT_ASSERT(buffer_[2] == testData[6]);
    CPPUNIT_ASSERT(buffer_[3] == testData[7]);
    CPPUNIT_ASSERT(buffer_[4] == resetValue_);
    
    // peek over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_), true);
    CPPUNIT_ASSERT(bytesRead == 0);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 8);
    CPPUNIT_ASSERT(buffer_[0] == testData[4]);
    CPPUNIT_ASSERT(buffer_[1] == testData[5]);
    CPPUNIT_ASSERT(buffer_[2] == testData[6]);
    CPPUNIT_ASSERT(buffer_[3] == testData[7]);
    CPPUNIT_ASSERT(buffer_[4] == resetValue_);
}

void StringStreamTests::TestShortStream3() {
    CPPUNIT_ASSERT(buffer_[0] == resetValue_);
    
    std::string testData = "12345678";
    rs::httpserver::StringStream stream(testData);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    // peek the first N bytes of the available data
    int bytesRead = stream.Read(buffer_, 0, 4, true);
    CPPUNIT_ASSERT(bytesRead == 4);    
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(buffer_[0] == testData[0]);
    CPPUNIT_ASSERT(buffer_[1] == testData[1]);
    CPPUNIT_ASSERT(buffer_[2] == testData[2]);
    CPPUNIT_ASSERT(buffer_[3] == testData[3]);
    CPPUNIT_ASSERT(buffer_[4] == resetValue_);
    
    // peek all remaining bytes of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_), true);
    CPPUNIT_ASSERT(bytesRead == 8);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(buffer_[0] == testData[0]);
    CPPUNIT_ASSERT(buffer_[1] == testData[1]);
    CPPUNIT_ASSERT(buffer_[2] == testData[2]);
    CPPUNIT_ASSERT(buffer_[3] == testData[3]);
    CPPUNIT_ASSERT(buffer_[4] == testData[4]);
    CPPUNIT_ASSERT(buffer_[5] == testData[5]);
    CPPUNIT_ASSERT(buffer_[6] == testData[6]);
    CPPUNIT_ASSERT(buffer_[7] == testData[7]);
    CPPUNIT_ASSERT(buffer_[8] == resetValue_);
    
    // read all bytes of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 8);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 8);
    CPPUNIT_ASSERT(buffer_[0] == testData[0]);
    CPPUNIT_ASSERT(buffer_[1] == testData[1]);
    CPPUNIT_ASSERT(buffer_[2] == testData[2]);
    CPPUNIT_ASSERT(buffer_[3] == testData[3]);
    CPPUNIT_ASSERT(buffer_[4] == testData[4]);
    CPPUNIT_ASSERT(buffer_[5] == testData[5]);
    CPPUNIT_ASSERT(buffer_[6] == testData[6]);
    CPPUNIT_ASSERT(buffer_[7] == testData[7]);
    CPPUNIT_ASSERT(buffer_[8] == resetValue_);
}

void StringStreamTests::TestShortStream4() {
    CPPUNIT_ASSERT(buffer_[0] == resetValue_);
    
    std::string testData = "12345678";
    rs::httpserver::StringStream stream(testData);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    // read the first N bytes of the available data at offset M
    int bytesRead = stream.Read(buffer_, 4, 4);
    CPPUNIT_ASSERT(bytesRead == 4);    
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 4);
    CPPUNIT_ASSERT(buffer_[0] == resetValue_);
    CPPUNIT_ASSERT(buffer_[1] == resetValue_);
    CPPUNIT_ASSERT(buffer_[2] == resetValue_);
    CPPUNIT_ASSERT(buffer_[3] == resetValue_);
    CPPUNIT_ASSERT(buffer_[4] == testData[0]);
    CPPUNIT_ASSERT(buffer_[5] == testData[1]);
    CPPUNIT_ASSERT(buffer_[6] == testData[2]);
    CPPUNIT_ASSERT(buffer_[7] == testData[3]);
    CPPUNIT_ASSERT(buffer_[8] == resetValue_);
    
    // read the next N bytes of the available data at offset 0
    bytesRead = stream.Read(buffer_, 0, 4);
    CPPUNIT_ASSERT(bytesRead == 4);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 8);
    CPPUNIT_ASSERT(buffer_[0] == testData[4]);
    CPPUNIT_ASSERT(buffer_[1] == testData[5]);
    CPPUNIT_ASSERT(buffer_[2] == testData[6]);
    CPPUNIT_ASSERT(buffer_[3] == testData[7]);
    CPPUNIT_ASSERT(buffer_[4] == testData[0]);
    CPPUNIT_ASSERT(buffer_[5] == testData[1]);
    CPPUNIT_ASSERT(buffer_[6] == testData[2]);
    CPPUNIT_ASSERT(buffer_[7] == testData[3]);
    CPPUNIT_ASSERT(buffer_[8] == resetValue_);
 
    // read over the end of the available data
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 0);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 8);
    CPPUNIT_ASSERT(buffer_[0] == testData[4]);
    CPPUNIT_ASSERT(buffer_[1] == testData[5]);
    CPPUNIT_ASSERT(buffer_[2] == testData[6]);
    CPPUNIT_ASSERT(buffer_[3] == testData[7]);
    CPPUNIT_ASSERT(buffer_[4] == testData[0]);
    CPPUNIT_ASSERT(buffer_[5] == testData[1]);
    CPPUNIT_ASSERT(buffer_[6] == testData[2]);
    CPPUNIT_ASSERT(buffer_[7] == testData[3]);
    CPPUNIT_ASSERT(buffer_[8] == resetValue_);
}

void StringStreamTests::TestShortStream5() {
    CPPUNIT_ASSERT(buffer_[0] == resetValue_);
    
    std::string testData = "12345678";
    rs::httpserver::StringStream stream(testData);
    CPPUNIT_ASSERT(stream.getLength() == 8);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    stream.AppendData("90123456");
    CPPUNIT_ASSERT(stream.getLength() == 16);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    
    // read the first N bytes of the available data at offset M
    int bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 16);    
    CPPUNIT_ASSERT(stream.getLength() == 16);
    CPPUNIT_ASSERT(stream.getPosition() == 16);
    
    stream.AppendData("78901234");
    CPPUNIT_ASSERT(stream.getLength() == 24);
    CPPUNIT_ASSERT(stream.getPosition() == 16);
    
    bytesRead = stream.Read(buffer_, 0, sizeof(buffer_));
    CPPUNIT_ASSERT(bytesRead == 8);    
    CPPUNIT_ASSERT(stream.getLength() == 24);
    CPPUNIT_ASSERT(stream.getPosition() == 24);
}