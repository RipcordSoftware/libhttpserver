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
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(".gif").get().getType(), "image/gif");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(".gif").get().getCompressible(), false);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(".png").get().getType(), "image/png");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(".txt").get().getType(), "text/plain");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(".html").get().getType(), "text/html");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(".html").get().getCompressible(), true);
}

TEST_F(MimeTypeTests, lookupTest2) {
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType(".xif"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType("xif"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType(".xyz"), false);
}

TEST_F(MimeTypeTests, lookupTest3) {
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.gif").get().getType(), "image/gif");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("/images/svg/example.svg").get().getType(), "image/svg+xml");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("/images/../example.woff").get().getType(), "application/font-woff");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("/images.vectors/example.svg").get().getType(), "image/svg+xml");
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType("/images.vectors/example"), false);
}

TEST_F(MimeTypeTests, lookupTest4) {
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example", true), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getType(), "text/example");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getCompressible(), true);
    rs::httpserver::MimeTypes::RemoveExtensionType(".example");
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType("example.example"), false);    
    
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example2", false), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getType(), "text/example2");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getCompressible(), false);
    rs::httpserver::MimeTypes::RemoveExtensionType(".example");
    
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example3", true), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getType(), "text/example3");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getCompressible(), true);
    rs::httpserver::MimeTypes::RemoveExtensionType(".example");
}

TEST_F(MimeTypeTests, lookupTest5) {
    boost::filesystem::path path("/image.png");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(path).get().getType(), "image/png");
    
    path = "image.jpg";
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(path).get().getType(), "image/jpg");
    
    path = "image.xyz";
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType(path), false);
    
    path = "image";
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType(path), false);
    
    path = "images.png/image";
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType(path), false);
    
    path = "images.png/image.png";
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType(path).get().getType(), "image/png");
}

TEST_F(MimeTypeTests, lookupTest6) {
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("image/gif").get().getType(), "image/gif");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("image/gif").get().getCompressible(), false);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("image/png").get().getType(), "image/png");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("text/plain").get().getType(), "text/plain");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("text/html").get().getType(), "text/html");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("text/html").get().getCompressible(), true);
}

TEST_F(MimeTypeTests, lookupTest7) {
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetContentType("image/abc"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetContentType("text/abc"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetContentType("video/zzz"), false);
}

TEST_F(MimeTypeTests, lookupTest8) {
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example", true), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getType(), "text/example");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getCompressible(), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("text/example").get().getType(), "text/example");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("text/example").get().getCompressible(), true);    
    rs::httpserver::MimeTypes::RemoveExtensionType(".example");
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType("example.example"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetContentType("example.example"), false);
    
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType("example.example"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetContentType("text/example2"), false);
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example2", false), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getType(), "text/example2");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getCompressible(), false);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("text/example2").get().getType(), "text/example2");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetContentType("text/example2").get().getCompressible(), false);
    rs::httpserver::MimeTypes::RemoveExtensionType(".example");
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType("example.example"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetContentType("text/example2"), false);
    
    ASSERT_EQ(rs::httpserver::MimeTypes::AddType(".example", "text/example3", true), true);
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getType(), "text/example3");
    ASSERT_EQ(rs::httpserver::MimeTypes::GetExtensionType("example.example").get().getCompressible(), true);
    rs::httpserver::MimeTypes::RemoveExtensionType(".example");
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetExtensionType("example.example"), false);
    ASSERT_EQ(!!rs::httpserver::MimeTypes::GetContentType("text/example3"), false);
}