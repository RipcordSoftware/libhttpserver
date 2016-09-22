#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/chunked_request_stream.o \
	${OBJECTDIR}/chunked_response_stream.o \
	${OBJECTDIR}/config.o \
	${OBJECTDIR}/file_stream.o \
	${OBJECTDIR}/gzip_response_stream.o \
	${OBJECTDIR}/header_buffer.o \
	${OBJECTDIR}/headers.o \
	${OBJECTDIR}/httpserver.o \
	${OBJECTDIR}/mime_types.o \
	${OBJECTDIR}/multipart_response_stream.o \
	${OBJECTDIR}/query_string.o \
	${OBJECTDIR}/request.o \
	${OBJECTDIR}/request_headers.o \
	${OBJECTDIR}/request_router.o \
	${OBJECTDIR}/request_stream.o \
	${OBJECTDIR}/response.o \
	${OBJECTDIR}/response_stream.o \
	${OBJECTDIR}/socket.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f9 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f6

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=$(COVERAGE_FLAGS)
CXXFLAGS=$(COVERAGE_FLAGS)

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhttpserver.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhttpserver.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhttpserver.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhttpserver.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhttpserver.a

${OBJECTDIR}/chunked_request_stream.o: chunked_request_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chunked_request_stream.o chunked_request_stream.cpp

${OBJECTDIR}/chunked_response_stream.o: chunked_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chunked_response_stream.o chunked_response_stream.cpp

${OBJECTDIR}/config.o: config.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config.o config.cpp

${OBJECTDIR}/file_stream.o: file_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file_stream.o file_stream.cpp

${OBJECTDIR}/gzip_response_stream.o: gzip_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gzip_response_stream.o gzip_response_stream.cpp

${OBJECTDIR}/header_buffer.o: header_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/header_buffer.o header_buffer.cpp

${OBJECTDIR}/headers.o: headers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/headers.o headers.cpp

${OBJECTDIR}/httpserver.o: httpserver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/httpserver.o httpserver.cpp

${OBJECTDIR}/mime_types.o: mime_types.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mime_types.o mime_types.cpp

${OBJECTDIR}/multipart_response_stream.o: multipart_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/multipart_response_stream.o multipart_response_stream.cpp

${OBJECTDIR}/query_string.o: query_string.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/query_string.o query_string.cpp

${OBJECTDIR}/request.o: request.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request.o request.cpp

${OBJECTDIR}/request_headers.o: request_headers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_headers.o request_headers.cpp

${OBJECTDIR}/request_router.o: request_router.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_router.o request_router.cpp

${OBJECTDIR}/request_stream.o: request_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_stream.o request_stream.cpp

${OBJECTDIR}/response.o: response.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response.o response.cpp

${OBJECTDIR}/response_stream.o: response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response_stream.o response_stream.cpp

${OBJECTDIR}/socket.o: socket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/socket.o socket.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/chunked_request_stream_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/chunked_response_stream_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/file_stream_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/mime_type_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 

${TESTDIR}/TestFiles/f9: ${TESTDIR}/tests/null_stream_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f9 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/query_string_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/readable_string_stream_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 

${TESTDIR}/TestFiles/f8: ${TESTDIR}/tests/request_header_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/writable_string_stream_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} ../../externals/installed/lib/libgtest_main.a ../../externals/installed/lib/libgtest.a $(COVERAGE_FLAGS)  -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_filesystem -lboost_date_time -lboost_system -lboost_regex -lpthread -lz 


${TESTDIR}/tests/chunked_request_stream_tests.o: tests/chunked_request_stream_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/chunked_request_stream_tests.o tests/chunked_request_stream_tests.cpp


${TESTDIR}/tests/chunked_response_stream_tests.o: tests/chunked_response_stream_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -I. -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/chunked_response_stream_tests.o tests/chunked_response_stream_tests.cpp


${TESTDIR}/tests/file_stream_tests.o: tests/file_stream_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -I. -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/file_stream_tests.o tests/file_stream_tests.cpp


${TESTDIR}/tests/mime_type_tests.o: tests/mime_type_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -I. -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/mime_type_tests.o tests/mime_type_tests.cpp


${TESTDIR}/tests/null_stream_tests.o: tests/null_stream_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -I. -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/null_stream_tests.o tests/null_stream_tests.cpp


${TESTDIR}/tests/query_string_tests.o: tests/query_string_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -I. -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/query_string_tests.o tests/query_string_tests.cpp


${TESTDIR}/tests/readable_string_stream_tests.o: tests/readable_string_stream_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/readable_string_stream_tests.o tests/readable_string_stream_tests.cpp


${TESTDIR}/tests/request_header_tests.o: tests/request_header_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -I. -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/request_header_tests.o tests/request_header_tests.cpp


${TESTDIR}/tests/writable_string_stream_tests.o: tests/writable_string_stream_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -I../../externals/installed/include -I. -std=c++11 $(COVERAGE_FLAGS) -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/writable_string_stream_tests.o tests/writable_string_stream_tests.cpp


${OBJECTDIR}/chunked_request_stream_nomain.o: ${OBJECTDIR}/chunked_request_stream.o chunked_request_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/chunked_request_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chunked_request_stream_nomain.o chunked_request_stream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/chunked_request_stream.o ${OBJECTDIR}/chunked_request_stream_nomain.o;\
	fi

${OBJECTDIR}/chunked_response_stream_nomain.o: ${OBJECTDIR}/chunked_response_stream.o chunked_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/chunked_response_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chunked_response_stream_nomain.o chunked_response_stream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/chunked_response_stream.o ${OBJECTDIR}/chunked_response_stream_nomain.o;\
	fi

${OBJECTDIR}/config_nomain.o: ${OBJECTDIR}/config.o config.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/config.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config_nomain.o config.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/config.o ${OBJECTDIR}/config_nomain.o;\
	fi

${OBJECTDIR}/file_stream_nomain.o: ${OBJECTDIR}/file_stream.o file_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/file_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file_stream_nomain.o file_stream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/file_stream.o ${OBJECTDIR}/file_stream_nomain.o;\
	fi

${OBJECTDIR}/gzip_response_stream_nomain.o: ${OBJECTDIR}/gzip_response_stream.o gzip_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gzip_response_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gzip_response_stream_nomain.o gzip_response_stream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gzip_response_stream.o ${OBJECTDIR}/gzip_response_stream_nomain.o;\
	fi

${OBJECTDIR}/header_buffer_nomain.o: ${OBJECTDIR}/header_buffer.o header_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/header_buffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/header_buffer_nomain.o header_buffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/header_buffer.o ${OBJECTDIR}/header_buffer_nomain.o;\
	fi

${OBJECTDIR}/headers_nomain.o: ${OBJECTDIR}/headers.o headers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/headers.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/headers_nomain.o headers.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/headers.o ${OBJECTDIR}/headers_nomain.o;\
	fi

${OBJECTDIR}/httpserver_nomain.o: ${OBJECTDIR}/httpserver.o httpserver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/httpserver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/httpserver_nomain.o httpserver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/httpserver.o ${OBJECTDIR}/httpserver_nomain.o;\
	fi

${OBJECTDIR}/mime_types_nomain.o: ${OBJECTDIR}/mime_types.o mime_types.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mime_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mime_types_nomain.o mime_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/mime_types.o ${OBJECTDIR}/mime_types_nomain.o;\
	fi

${OBJECTDIR}/multipart_response_stream_nomain.o: ${OBJECTDIR}/multipart_response_stream.o multipart_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/multipart_response_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/multipart_response_stream_nomain.o multipart_response_stream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/multipart_response_stream.o ${OBJECTDIR}/multipart_response_stream_nomain.o;\
	fi

${OBJECTDIR}/query_string_nomain.o: ${OBJECTDIR}/query_string.o query_string.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/query_string.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/query_string_nomain.o query_string.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/query_string.o ${OBJECTDIR}/query_string_nomain.o;\
	fi

${OBJECTDIR}/request_nomain.o: ${OBJECTDIR}/request.o request.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/request.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_nomain.o request.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/request.o ${OBJECTDIR}/request_nomain.o;\
	fi

${OBJECTDIR}/request_headers_nomain.o: ${OBJECTDIR}/request_headers.o request_headers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/request_headers.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_headers_nomain.o request_headers.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/request_headers.o ${OBJECTDIR}/request_headers_nomain.o;\
	fi

${OBJECTDIR}/request_router_nomain.o: ${OBJECTDIR}/request_router.o request_router.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/request_router.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_router_nomain.o request_router.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/request_router.o ${OBJECTDIR}/request_router_nomain.o;\
	fi

${OBJECTDIR}/request_stream_nomain.o: ${OBJECTDIR}/request_stream.o request_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/request_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_stream_nomain.o request_stream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/request_stream.o ${OBJECTDIR}/request_stream_nomain.o;\
	fi

${OBJECTDIR}/response_nomain.o: ${OBJECTDIR}/response.o response.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/response.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response_nomain.o response.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/response.o ${OBJECTDIR}/response_nomain.o;\
	fi

${OBJECTDIR}/response_stream_nomain.o: ${OBJECTDIR}/response_stream.o response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/response_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response_stream_nomain.o response_stream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/response_stream.o ${OBJECTDIR}/response_stream_nomain.o;\
	fi

${OBJECTDIR}/socket_nomain.o: ${OBJECTDIR}/socket.o socket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/socket.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/socket_nomain.o socket.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/socket.o ${OBJECTDIR}/socket_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f9 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libhttpserver.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
