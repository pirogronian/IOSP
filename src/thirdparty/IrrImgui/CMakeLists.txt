#
# The MIT License (MIT)
#
# Copyright (c) 2015 André Netzeband
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

#cmake_minimum_required(VERSION 2.6)
#cmake_policy(VERSION 2.6)
	
#PROJECT(IrrIMGUI)

add_library(IrrImgui STATIC)

SET (IMGUI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependency/IMGUI/")

SET (IMGUI_PUBLIC_HEADER_FILES
	${IMGUI_SOURCE_DIR}/imgui.h
	${IMGUI_SOURCE_DIR}/imconfig.h	
)

SET (IMGUI_PRIVATE_HEADER_FILES
	${IMGUI_SOURCE_DIR}/imgui_internal.h
	${IMGUI_SOURCE_DIR}/imstb_rectpack.h	
	${IMGUI_SOURCE_DIR}/imstb_textedit.h	
	${IMGUI_SOURCE_DIR}/imstb_truetype.h	
)

SET (IMGUI_SOURCE_FILES
	${IMGUI_SOURCE_DIR}/imgui.cpp
	${IMGUI_SOURCE_DIR}/imgui_draw.cpp
	${IMGUI_SOURCE_DIR}/imgui_demo.cpp
	${IMGUI_SOURCE_DIR}/imgui_tables.cpp
	${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
)

SET (IRRIMGUI_PUBLIC_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/Inject/IrrIMGUIInject.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/Tools/CBasicMemoryLeakDetection.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/UnitTest/IIMGUIHandleMock.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/UnitTest/IncludeCppUTest.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/UnitTest/MockHelper.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/UnitTest/UnitTest.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/CCharFifo.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/CIMGUIEventReceiver.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/CIMGUIEventStorage.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IGUITexture.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IIMGUIHandle.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IMGUIHelper.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IncludeIMGUI.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IncludeIrrlicht.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IReferenceCounter.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IrrIMGUI.h	
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IrrIMGUIConfig.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IrrIMGUIConstants.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/IrrIMGUIDebug.h
	${CMAKE_CURRENT_SOURCE_DIR}/includes/IrrIMGUI/SIMGUISettings.h
)

SET (IRRIMGUI_PRIVATE_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/source/private/CGUITexture.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/private/IrrIMGUIDebug_priv.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/private/IrrIMGUIInject_priv.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/CIMGUIHandle.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/CIrrlichtIMGUIDriver.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/COpenGLIMGUIDriver.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/IIMGUIDriver.h
)

SET (IRRIMGUI_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/source/CBasicMemoryLeakDetection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/CChannelBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/CCharFifo.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/CGUITexture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/CIMGUIEventReceiver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/CIMGUIHandle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/CIrrlichtIMGUIDriver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/COpenGLIMGUIDriver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/IIMGUIDriver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/IMGUIHelper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/IReferenceCounter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/IrrIMGUIInject.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/UnitTest.cpp
)


# Collect all source files
SET(ALL_HEADER_FILES
	${IRRIMGUI_PRIVATE_HEADER_FILES}
	${IRRIMGUI_PUBLIC_HEADER_FILES}
	${IMGUI_PUBLIC_HEADER_FILES}
	${IMGUI_PRIVATE_HEADER_FILES}
)

SET(ALL_SOURCE_FILES
	${IRRIMGUI_SOURCE_FILES}
	${IMGUI_SOURCE_FILES}
)

# Target settings
SET_SOURCE_FILES_PROPERTIES(ALL_HEADER_FILES
                            PROPERTIES HEADER_FILE_ONLY TRUE)
							
LIST(APPEND ALL_SOURCE_FILES ${ALL_HEADER_FILES})

target_include_directories(IrrImgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes/)
target_include_directories(IrrImgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependency/)
target_include_directories(IrrImgui PRIVATE ${IRRLICHT_INCLUDE_DIR})

target_sources(IrrImgui PRIVATE ${ALL_SOURCE_FILES})
