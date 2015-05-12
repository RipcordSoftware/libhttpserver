#include <gtest/gtest.h>

#include "../mime_types.h"

class MimeTypeTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }                
};

TEST_F(MimeTypeTests, lookupTest1) {
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(".gif").get().getType(), "image/gif");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(".gif").get().getCompressible(), false);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(".png").get().getType(), "image/png");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(".txt").get().getType(), "text/plain");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(".html").get().getType(), "text/html");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(".html").get().getCompressible(), true);
}

TEST_F(MimeTypeTests, lookupTest2) {
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetType(".xif"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetType("xif"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetType(".xyz"), false);
}

TEST_F(MimeTypeTests, lookupTest3) {
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("example.gif").get().getType(), "image/gif");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("/images/svg/example.svg").get().getType(), "image/svg+xml");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("/images/../example.woff").get().getType(), "application/font-woff");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("/images.vectors/example.svg").get().getType(), "image/svg+xml");
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetType("/images.vectors/example"), false);
}

TEST_F(MimeTypeTests, lookupTest4) {
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example", true), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("example.example").get().getType(), "text/example");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("example.example").get().getCompressible(), true);
    rs::httpserver::MimeTypes::RemoveType(".example");
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetType("example.example"), false);
    
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example2", false), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("example.example").get().getType(), "text/example2");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("example.example").get().getCompressible(), false);
    
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example3", true), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("example.example").get().getType(), "text/example3");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType("example.example").get().getCompressible(), true);
}

TEST_F(MimeTypeTests, lookupTest5) {
    boost::filesystem::path path("/image.png");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(path).get().getType(), "image/png");
    
    path = "image.jpg";
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(path).get().getType(), "image/jpeg");
    
    path = "image.xyz";
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetType(path), false);
    
    path = "image";
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetType(path), false);
    
    path = "images.png/image";
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetType(path), false);
    
    path = "images.png/image.png";
    ASSERT_EQ(rs::httpserver::MimeTypes::GetType(path).get().getType(), "image/png");
}