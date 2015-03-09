#include "ChunkedRequestStreamTests.h"

#include "../string_stream.h"
#include "../chunked_request_stream.h"
#include "../exceptions.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ChunkedRequestStreamTests);

ChunkedRequestStreamTests::ChunkedRequestStreamTests() {
}

ChunkedRequestStreamTests::~ChunkedRequestStreamTests() {
}

void ChunkedRequestStreamTests::setUp() {
    ResetBuffer();
}

void ChunkedRequestStreamTests::tearDown() {
}

void ChunkedRequestStreamTests::testMethod() {
    rs::httpserver::StringStream requestStream("0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
}

void ChunkedRequestStreamTests::testMethod2() {
    rs::httpserver::StringStream requestStream("0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_), true) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
}

void ChunkedRequestStreamTests::testMethod3() {
    rs::httpserver::StringStream requestStream("1\r\na\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_), true) == 1);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 1);
    CPPUNIT_ASSERT(stream.getPosition() == 1);
    CPPUNIT_ASSERT(stream.getLength() == 1);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 1);
    CPPUNIT_ASSERT(stream.getLength() == 1);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == resetValue_);
}

void ChunkedRequestStreamTests::testMethod4() {
    rs::httpserver::StringStream requestStream("3\r\nabc\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
        
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_), true) == 3);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == 'b');
    CPPUNIT_ASSERT(buffer_[2] == 'c');
    CPPUNIT_ASSERT(buffer_[3] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 3);
    CPPUNIT_ASSERT(stream.getPosition() == 3);
    CPPUNIT_ASSERT(stream.getLength() == 3);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == 'b');
    CPPUNIT_ASSERT(buffer_[2] == 'c');
    CPPUNIT_ASSERT(buffer_[3] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 3);
    CPPUNIT_ASSERT(stream.getLength() == 3);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == 'b');
    CPPUNIT_ASSERT(buffer_[2] == 'c');
    CPPUNIT_ASSERT(buffer_[3] == resetValue_);
}

void ChunkedRequestStreamTests::testMethod5() {
    rs::httpserver::StringStream requestStream("3\r\nabc\r\n3\r\npqr\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
        
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, 3, true) == 3);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == 'b');
    CPPUNIT_ASSERT(buffer_[2] == 'c');
    CPPUNIT_ASSERT(buffer_[3] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, 3) == 3);
    CPPUNIT_ASSERT(stream.getPosition() == 3);
    CPPUNIT_ASSERT(stream.getLength() == 3);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == 'b');
    CPPUNIT_ASSERT(buffer_[2] == 'c');
    CPPUNIT_ASSERT(buffer_[3] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 3, sizeof(buffer_)) == 3);
    CPPUNIT_ASSERT(stream.getPosition() == 6);
    CPPUNIT_ASSERT(stream.getLength() == 6);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == 'b');
    CPPUNIT_ASSERT(buffer_[2] == 'c');
    CPPUNIT_ASSERT(buffer_[3] == 'p');
    CPPUNIT_ASSERT(buffer_[4] == 'q');
    CPPUNIT_ASSERT(buffer_[5] == 'r');
    CPPUNIT_ASSERT(buffer_[6] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 6);
    CPPUNIT_ASSERT(stream.getLength() == 6);
    CPPUNIT_ASSERT(buffer_[0] == 'a');
    CPPUNIT_ASSERT(buffer_[1] == 'b');
    CPPUNIT_ASSERT(buffer_[2] == 'c');
    CPPUNIT_ASSERT(buffer_[3] == 'p');
    CPPUNIT_ASSERT(buffer_[4] == 'q');
    CPPUNIT_ASSERT(buffer_[5] == 'r');
    CPPUNIT_ASSERT(buffer_[6] == resetValue_);
}

void ChunkedRequestStreamTests::testMethod6() {
    rs::httpserver::StringStream requestStream("a\r\n0123456789\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_), true) == 10);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 10);
    CPPUNIT_ASSERT(stream.getPosition() == 10);
    CPPUNIT_ASSERT(stream.getLength() == 10);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == resetValue_);    
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 10);
    CPPUNIT_ASSERT(stream.getLength() == 10);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == resetValue_);    
}

void ChunkedRequestStreamTests::testMethod7() {
    rs::httpserver::StringStream requestStream("f\r\n012345678901234\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_), true) == 15);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == '0');
    CPPUNIT_ASSERT(buffer_[11] == '1');
    CPPUNIT_ASSERT(buffer_[12] == '2');
    CPPUNIT_ASSERT(buffer_[13] == '3');
    CPPUNIT_ASSERT(buffer_[14] == '4');
    CPPUNIT_ASSERT(buffer_[15] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 15);
    CPPUNIT_ASSERT(stream.getPosition() == 15);
    CPPUNIT_ASSERT(stream.getLength() == 15);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == '0');
    CPPUNIT_ASSERT(buffer_[11] == '1');
    CPPUNIT_ASSERT(buffer_[12] == '2');
    CPPUNIT_ASSERT(buffer_[13] == '3');
    CPPUNIT_ASSERT(buffer_[14] == '4');
    CPPUNIT_ASSERT(buffer_[15] == resetValue_); 
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 15);
    CPPUNIT_ASSERT(stream.getLength() == 15);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == '0');
    CPPUNIT_ASSERT(buffer_[11] == '1');
    CPPUNIT_ASSERT(buffer_[12] == '2');
    CPPUNIT_ASSERT(buffer_[13] == '3');
    CPPUNIT_ASSERT(buffer_[14] == '4');
    CPPUNIT_ASSERT(buffer_[15] == resetValue_);   
}

void ChunkedRequestStreamTests::testMethod8() {
    rs::httpserver::StringStream requestStream("C\r\n012345678901\r\n0\r\n\r\n");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_), true) == 12);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == '0');
    CPPUNIT_ASSERT(buffer_[11] == '1');
    CPPUNIT_ASSERT(buffer_[12] == resetValue_);
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 12);
    CPPUNIT_ASSERT(stream.getPosition() == 12);
    CPPUNIT_ASSERT(stream.getLength() == 12);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == '0');
    CPPUNIT_ASSERT(buffer_[11] == '1');
    CPPUNIT_ASSERT(buffer_[12] == resetValue_); 
    
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 12);
    CPPUNIT_ASSERT(stream.getLength() == 12);
    CPPUNIT_ASSERT(buffer_[0] == '0');
    CPPUNIT_ASSERT(buffer_[1] == '1');
    CPPUNIT_ASSERT(buffer_[2] == '2');
    CPPUNIT_ASSERT(buffer_[3] == '3');
    CPPUNIT_ASSERT(buffer_[4] == '4');
    CPPUNIT_ASSERT(buffer_[5] == '5');
    CPPUNIT_ASSERT(buffer_[6] == '6');
    CPPUNIT_ASSERT(buffer_[7] == '7');
    CPPUNIT_ASSERT(buffer_[8] == '8');
    CPPUNIT_ASSERT(buffer_[9] == '9');
    CPPUNIT_ASSERT(buffer_[10] == '0');
    CPPUNIT_ASSERT(buffer_[11] == '1');
    CPPUNIT_ASSERT(buffer_[12] == resetValue_);   
}

void ChunkedRequestStreamTests::testMethod9() {
    bool gotException = false;
    
    try {
        rs::httpserver::StringStream requestStream("1;Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc auctor erat in porta aliquam. Aliquam at semper augue, quis mattis ipsum.\r\na\r\n0\r\n\r\n");
        rs::httpserver::ChunkedRequestStream stream(requestStream);

        stream.Read(buffer_, 0, sizeof(buffer_));
    } catch (const rs::httpserver::ChunkedRequestHeaderException& ex) {
        gotException = true;
    } 
    
    CPPUNIT_ASSERT(gotException == true);
}

void ChunkedRequestStreamTests::testMethod10() {
    bool gotException = false;
    
    rs::httpserver::StringStream requestStream("1;Lorem ipsum dolor sit amet, consectetur adipiscing elit. ");
    rs::httpserver::ChunkedRequestStream stream(requestStream);
    CPPUNIT_ASSERT(stream.Read(buffer_, 0, sizeof(buffer_)) == 0);
    CPPUNIT_ASSERT(stream.getPosition() == 0);
    CPPUNIT_ASSERT(stream.getLength() == 0);
    
    try {        
        requestStream.AppendData("Nunc auctor erat in porta aliquam. Aliquam at semper augue, quis mattis ipsum.\r\na\r\n0\r\n\r\n");
        stream.Read(buffer_, 0, sizeof(buffer_));                
    } catch (const rs::httpserver::ChunkedRequestHeaderException& ex) {
        gotException = true;
    } 
    
    CPPUNIT_ASSERT(gotException == true);
}