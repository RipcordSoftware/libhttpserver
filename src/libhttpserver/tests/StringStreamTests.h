#ifndef STRINGSTREAMTESTS_H
#define	STRINGSTREAMTESTS_H

#include <cppunit/extensions/HelperMacros.h>

#include <algorithm>

#include "../string_stream.h"

class StringStreamTests : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(StringStreamTests);

    CPPUNIT_TEST(TestEmptyStream);
    CPPUNIT_TEST(TestShortStream1);
    CPPUNIT_TEST(TestShortStream2); 
    CPPUNIT_TEST(TestShortStream3); 
    CPPUNIT_TEST(TestShortStream4); 
    CPPUNIT_TEST(TestShortStream5); 

    CPPUNIT_TEST_SUITE_END();

public:
    StringStreamTests();
    virtual ~StringStreamTests();
    void setUp();
    void tearDown();

private:
    void TestEmptyStream();
    void TestShortStream1();
    void TestShortStream2();
    void TestShortStream3();
    void TestShortStream4();
    void TestShortStream5();
    
    void ResetBuffer() { std::fill_n(buffer_, sizeof(buffer_), resetValue_); }
    
    const rs::httpserver::Stream::byte resetValue_ = 0xff;
    rs::httpserver::Stream::byte buffer_[1024];
};

#endif	/* STRINGSTREAMTESTS_H */

