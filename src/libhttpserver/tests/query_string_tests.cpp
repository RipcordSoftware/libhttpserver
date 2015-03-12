#include <algorithm>

#include <gtest/gtest.h>

#include "../query_string.h"

class QueryStringTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }    
};

TEST_F(QueryStringTests, testMethod1) {
    rs::httpserver::QueryString q("abc=1");
    
    ASSERT_EQ(q.IsKey("abc"), true);
    
    auto keys = q.getKeys();
    ASSERT_EQ(keys.size(), 1);
    ASSERT_STRCASEEQ(keys[0].c_str(), "abc");
    ASSERT_STRCASEEQ(q.getValue("abc").c_str(), "1");
}

TEST_F(QueryStringTests, testMethod2) {
    rs::httpserver::QueryString q("abc=1&pqr=xyz");
    
    ASSERT_EQ(q.IsKey("abc"), true);
    ASSERT_EQ(q.IsKey("pqr"), true);
    
    auto keys = q.getKeys();
    ASSERT_EQ(keys.size(), 2);
    ASSERT_STRCASEEQ(keys[0].c_str(), "abc");
    ASSERT_STRCASEEQ(keys[1].c_str(), "pqr");
    ASSERT_STRCASEEQ(q.getValue("abc").c_str(), "1");
    ASSERT_STRCASEEQ(q.getValue("pqr").c_str(), "xyz");
}

TEST_F(QueryStringTests, testMethod3) {
    rs::httpserver::QueryString q("abc=1&pqr=xyz&test=");
    
    ASSERT_EQ(q.IsKey("abc"), true);
    ASSERT_EQ(q.IsKey("pqr"), true);
    ASSERT_EQ(q.IsKey("test"), true);
    
    auto keys = q.getKeys();
    ASSERT_EQ(keys.size(), 3);
    ASSERT_STRCASEEQ(keys[0].c_str(), "abc");
    ASSERT_STRCASEEQ(keys[1].c_str(), "pqr");
    ASSERT_STRCASEEQ(keys[2].c_str(), "test");
    ASSERT_STRCASEEQ(q.getValue("abc").c_str(), "1");
    ASSERT_STRCASEEQ(q.getValue("pqr").c_str(), "xyz");
    ASSERT_STRCASEEQ(q.getValue("test").c_str(), "");
}

TEST_F(QueryStringTests, testMethod4) {
    rs::httpserver::QueryString q("");
    
    ASSERT_EQ(q.IsKey("abc"), false);
    ASSERT_EQ(q.IsKey("pqr"), false);
    ASSERT_EQ(q.IsKey("test"), false);
    
    auto keys = q.getKeys();
    ASSERT_EQ(keys.size(), 0);
    ASSERT_STRCASENE(q.getValue("abc").c_str(), "1");
    ASSERT_STRCASENE(q.getValue("pqr").c_str(), "xyz");
    ASSERT_STRCASEEQ(q.getValue("test").c_str(), "");
}

TEST_F(QueryStringTests, testMethod5) {
    rs::httpserver::QueryString q("nothing_here");
    
    ASSERT_EQ(q.IsKey("abc"), false);
    ASSERT_EQ(q.IsKey("pqr"), false);
    ASSERT_EQ(q.IsKey("test"), false);
    
    auto keys = q.getKeys();
    ASSERT_EQ(keys.size(), 1);
    ASSERT_STRCASEEQ(keys[0].c_str(), "nothing_here");
    ASSERT_STRCASEEQ(q.getValue("nothing_here").c_str(), "");
}