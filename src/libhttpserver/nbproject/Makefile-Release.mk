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
CND_CONF=Release
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
	${OBJECTDIR}/gzip_response_stream.o \
	${OBJECTDIR}/header_buffer.o \
	${OBJECTDIR}/headers.o \
	${OBJECTDIR}/httpserver.o \
	${OBJECTDIR}/mime_types.o \
	${OBJECTDIR}/query_string.o \
	${OBJECTDIR}/request.o \
	${OBJECTDIR}/request_headers.o \
	${OBJECTDIR}/request_stream.o \
	${OBJECTDIR}/response.o \
	${OBJECTDIR}/response_stream.o \
	${OBJECTDIR}/socket.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f2

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

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
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chunked_request_stream.o chunked_request_stream.cpp

${OBJECTDIR}/chunked_response_stream.o: chunked_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chunked_response_stream.o chunked_response_stream.cpp

${OBJECTDIR}/config.o: config.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config.o config.cpp

${OBJECTDIR}/gzip_response_stream.o: gzip_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gzip_response_stream.o gzip_response_stream.cpp

${OBJECTDIR}/header_buffer.o: header_buffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/header_buffer.o header_buffer.cpp

${OBJECTDIR}/headers.o: headers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/headers.o headers.cpp

${OBJECTDIR}/httpserver.o: httpserver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/httpserver.o httpserver.cpp

${OBJECTDIR}/mime_types.o: mime_types.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mime_types.o mime_types.cpp

${OBJECTDIR}/query_string.o: query_string.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/query_string.o query_string.cpp

${OBJECTDIR}/request.o: request.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request.o request.cpp

${OBJECTDIR}/request_headers.o: request_headers.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_headers.o request_headers.cpp

${OBJECTDIR}/request_stream.o: request_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_stream.o request_stream.cpp

${OBJECTDIR}/response.o: response.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response.o response.cpp

${OBJECTDIR}/response_stream.o: response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response_stream.o response_stream.cpp

${OBJECTDIR}/socket.o: socket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/socket.o socket.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/ChunkedRequestStreamTests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} externals/gtest-1.7.0/lib/.libs/libgtest_main.a externals/gtest-1.7.0/lib/.libs/libgtest.a  -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_system `pkg-config --libs zlib`   

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/mime_type_tests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} externals/gtest-1.7.0/lib/.libs/libgtest_main.a externals/gtest-1.7.0/lib/.libs/libgtest.a  -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_system `pkg-config --libs zlib`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/StringStreamTests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} externals/gtest-1.7.0/lib/.libs/libgtest_main.a externals/gtest-1.7.0/lib/.libs/libgtest.a  -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lboost_thread -lboost_system `pkg-config --libs zlib`   


${TESTDIR}/tests/ChunkedRequestStreamTests.o: tests/ChunkedRequestStreamTests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iexternals/gtest-1.7.0/include -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ChunkedRequestStreamTests.o tests/ChunkedRequestStreamTests.cpp


${TESTDIR}/tests/mime_type_tests.o: tests/mime_type_tests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iexternals/gtest-1.7.0/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/mime_type_tests.o tests/mime_type_tests.cpp


${TESTDIR}/tests/StringStreamTests.o: tests/StringStreamTests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iexternals/gtest-1.7.0/include -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/StringStreamTests.o tests/StringStreamTests.cpp


${OBJECTDIR}/chunked_request_stream_nomain.o: ${OBJECTDIR}/chunked_request_stream.o chunked_request_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/chunked_request_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chunked_request_stream_nomain.o chunked_request_stream.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/chunked_response_stream_nomain.o chunked_response_stream.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config_nomain.o config.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/config.o ${OBJECTDIR}/config_nomain.o;\
	fi

${OBJECTDIR}/gzip_response_stream_nomain.o: ${OBJECTDIR}/gzip_response_stream.o gzip_response_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gzip_response_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gzip_response_stream_nomain.o gzip_response_stream.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/header_buffer_nomain.o header_buffer.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/headers_nomain.o headers.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/httpserver_nomain.o httpserver.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mime_types_nomain.o mime_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/mime_types.o ${OBJECTDIR}/mime_types_nomain.o;\
	fi

${OBJECTDIR}/query_string_nomain.o: ${OBJECTDIR}/query_string.o query_string.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/query_string.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/query_string_nomain.o query_string.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_nomain.o request.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_headers_nomain.o request_headers.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/request_headers.o ${OBJECTDIR}/request_headers_nomain.o;\
	fi

${OBJECTDIR}/request_stream_nomain.o: ${OBJECTDIR}/request_stream.o request_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/request_stream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/request_stream_nomain.o request_stream.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response_nomain.o response.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response_stream_nomain.o response_stream.cpp;\
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
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/socket_nomain.o socket.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/socket.o ${OBJECTDIR}/socket_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
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
