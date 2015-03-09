#ifndef CHUNKEDREQUESTSTREAM_H
#define	CHUNKEDREQUESTSTREAM_H

#include <cppunit/extensions/HelperMacros.h>

#include "../stream.h"

class ChunkedRequestStreamTests : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ChunkedRequestStreamTests);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testMethod2);
    CPPUNIT_TEST(testMethod3);
    CPPUNIT_TEST(testMethod4);
    CPPUNIT_TEST(testMethod5);
    CPPUNIT_TEST(testMethod6);
    CPPUNIT_TEST(testMethod7);
    CPPUNIT_TEST(testMethod8);
    CPPUNIT_TEST(testMethod9);
    CPPUNIT_TEST(testMethod10);

    CPPUNIT_TEST_SUITE_END();

public:
    ChunkedRequestStreamTests();
    virtual ~ChunkedRequestStreamTests();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testMethod2();
    void testMethod3();
    void testMethod4();
    void testMethod5();
    void testMethod6();
    void testMethod7();
    void testMethod8();
    void testMethod9();
    void testMethod10();
    
    void ResetBuffer() { std::fill_n(buffer_, sizeof(buffer_), resetValue_); }
    
    rs::httpserver::Stream::byte buffer_[1024];
    const rs::httpserver::Stream::byte resetValue_ = 0xff;
};

#endif	/* CHUNKEDREQUESTSTREAM_H */

