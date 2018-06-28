########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 3.0.0 ) 

project( Gemini )

#########################################################

# Qt5 packages minimum version 5.4
find_package(Qt5 5.4 COMPONENTS Core Network Svg WebKit WebKitWidgets Widgets Xml XmlPatterns Concurrent PrintSupport LinguistTools)
set(CMAKE_AUTOMOC ON)

set( MAIN_FILES
	gemini_constants.h
	main.cpp
)

set( MAINUI_FILES 
	mainUI/MainWindow.h
	mainUI/MainWindow.cpp
	mainUI/CalcManager.h
	mainUI/CalcManager.cpp
)

set( CALC_CP_FILES 
	calcCP/CalcCPDlg.h
	calcCP/CalcCPDlg.cpp
	calcCP/CSVKyobo.h
	calcCP/CSVKyobo.cpp
	calcCP/CSVNaver.h
	calcCP/CSVNaver.cpp
	calcCP/CSVRidi.h
	calcCP/CSVRidi.cpp
	calcCP/CSVMunpia.h
	calcCP/CSVMunpia.cpp
	calcCP/CSVMrblue.h
	calcCP/CSVMrblue.cpp
	calcCP/CSVBarobook.h
	calcCP/CSVBarobook.cpp
	calcCP/CSVBookcube.h
	calcCP/CSVBookcube.cpp
	calcCP/CSVEpyrus.h
	calcCP/CSVEpyrus.cpp
	calcCP/CSVOebook.h
	calcCP/CSVOebook.cpp
	calcCP/CSVOnestore.h
	calcCP/CSVOnestore.cpp
	calcCP/CSVKakao.h
	calcCP/CSVKakao.cpp
	calcCP/CSVComico.h
	calcCP/CSVComico.cpp
	calcCP/CSVTocsoda.h
	calcCP/CSVTocsoda.cpp
	calcCP/CSVKepub.h
	calcCP/CSVKepub.cpp
)

set( CALC_TOTAL_FILES 
	calcTotal/CSVTotalCP.h
	calcTotal/CSVTotalCP.cpp
	calcTotal/CSVTotalBook.h
	calcTotal/CSVTotalBook.cpp
	calcTotal/CSVTotalSeries.h
	calcTotal/CSVTotalSeries.cpp
	calcTotal/CalcTotalDlg.h
	calcTotal/CalcTotalDlg.cpp
)

set( MISC_FILES 
	misc/LimitDate.h
	misc/LimitDate.cpp
    misc/SettingData.h
    misc/SettingData.cpp
	misc/TinyAES.h
	misc/TinyAES.cpp
)

set( QTCSV_FILES
	qtcsv/abstractdata.h
	qtcsv/contentiterator.cpp
	qtcsv/contentiterator.h
	qtcsv/filechecker.h
	qtcsv/qtcsv_global.h
	qtcsv/reader.cpp
	qtcsv/reader.h
	qtcsv/stringdata.cpp
	qtcsv/stringdata.h
	qtcsv/symbols.h
	qtcsv/variantdata.cpp
	qtcsv/variantdata.h
	qtcsv/writer.cpp
	qtcsv/writer.h
)

set( UI_FILES
	formFiles/MainWindow.ui
	formFiles/CalcCPDlg.ui
	formFiles/CalcTotalDlg.ui
)

set( QRC_FILES
	resFiles/resources.qrc
)

set( RAW_SOURCES ${MAIN_FILES} ${MAINUI_FILES} ${CALC_CP_FILES} ${CALC_TOTAL_FILES} ${MISC_FILES} ${QTCSV_FILES})

#########################################################

# Runs UIC on specified files
qt5_wrap_ui( UI_FILES_H ${UI_FILES} )
# Runs RCC on specified files
qt5_add_resources( QRC_FILES_CPP ${QRC_FILES} )
# Runs lrelease on the specified files
qt5_add_translation( QM_FILES ${TS_FILES} )

# Define the Gemini version string for use in source files
# set_source_files_properties( Misc/Utility.cpp PROPERTIES COMPILE_DEFINITIONS GEMINI_FULL_VERSION="${GEMINI_FULL_VERSION}" )
# set_source_files_properties( Dialogs/About.cpp PROPERTIES COMPILE_DEFINITIONS GEMINI_FULL_VERSION="${GEMINI_FULL_VERSION}" )
# set_property( SOURCE Dialogs/About.cpp APPEND PROPERTY COMPILE_DEFINITIONS GEMINI_FULL_VERSION="${GEMINI_FULL_VERSION}" GEMINI_CODE_NAME="${GEMINI_CODE_NAME}" )

#########################################################

# Adds folders for Visual Studio solution explorer (and for Xcode explorer)
source_group( "Form Files"        FILES ${UI_FILES} )
source_group( "Resource Files"    FILES ${QRC_FILES} )
source_group( "Calc CP"           FILES ${CALC_CP_FILES} )
source_group( "Calc Total"        FILES ${CALC_TOTAL_FILES} )
source_group( "Misc"              FILES ${MISC_FILES} )
source_group( "QtCSV"             FILES ${QTCSV_FILES} )
source_group( "Main UI"           FILES ${MAINUI_FILES} )
source_group( "Main Files"        FILES ${MAIN_FILES} )

#########################################################

set( ALL_SOURCES ${RAW_SOURCES} ${UI_FILES_H} ${QRC_FILES_CPP} ${QM_FILES} )

#########################################################

# We need to pick up the ui*.h files,
# and the headers for the linked-to libraries.
# The directories are in reverse order because we're using before to
# put our include dirs before any system ones.
include_directories( BEFORE
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR} )

#########################################################

add_executable( ${PROJECT_NAME} WIN32 ${ALL_SOURCES} )

if (MSVC)
    set(QT_MAIN Qt5::WinMain)
endif()

target_link_libraries( ${PROJECT_NAME} ${QT_MAIN}  )
qt5_use_modules(${PROJECT_NAME} Widgets Xml XmlPatterns PrintSupport Svg WebKit WebKitWidgets Network Concurrent Multimedia)

#########################################################

# Speed up stirng building
add_definitions( -DQT_USE_FAST_CONCATENATION )
add_definitions( -DQT_USE_FAST_OPERATOR_PLUS )

#########################################################

# "Link time code generation" flags for MSVC
if( MSVC )
    add_definitions( /DUNICODE /D_UNICODE /DHAVE_ROUND )
    # The /Zc:wchar_t- flag can't go into add_definitions
    # because the RC compiler picks it up too and it provokes a name clash
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t- /MP")
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
    set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )

# "Print all warnings" flag for GCC
elseif( CMAKE_COMPILER_IS_GNUCXX )
    add_definitions( -Wall )
endif()

#########################################################
