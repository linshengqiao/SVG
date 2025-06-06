cmake_minimum_required(VERSION 3.12)
project(KSvgEditor LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找 Qt 库（Widgets 和其他模块）
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Charts)

# 自动处理 Qt MOC、RCC 和 UIC
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOUIC ON)

# 主源文件
set(MAIN_SRC src/main.cpp)

# UI 组件
set(UI_SOURCES 
    src/ui/kmainwindow.cpp
    src/ui/kmainwindow.h
    src/ui/kmainwindow.ui
    )

source_group("src\\ui" FILES 
    ${UI_SOURCES}
)

# KToolbar
set(KTOOLBAR_SOURCES  
    src/ui/KToolbar/ktoolbarwidget.cpp
    src/ui/KToolbar/ktoolbarwidget.h
    )

source_group("src\\ui\\KToolbar" FILES 
    ${KTOOLBAR_SOURCES}
)

#KCanvas
set(KCANVAS_SOURCES 
    src/ui/KCanvas/kcanvaswidget.cpp
    src/ui/KCanvas/kcanvaswidget.h
    src/ui/KCanvas/kcanvascontroller.cpp
    src/ui/KCanvas/kcanvascontroller.h
    src/ui/KCanvas/kshapefactory.cpp
    src/ui/KCanvas/kshapefactory.h
    )

source_group("src\\ui\\KCanvas" FILES
    ${KCANVAS_SOURCES}
)

#KParameterSetting
set(KPARAMETERSETTING_SOURCES 
    src/ui/KParameterSetting/kparametersettingwidget.cpp
    src/ui/KParameterSetting/kparametersettingwidget.h
    )

source_group("src\\ui\\KParameterSetting" FILES
    ${KPARAMETERSETTING_SOURCES}
)

#KRender
set(KRENDER_SOURCES 
    src/ui/KRender/kirender.cpp
    src/ui/KRender/kirender.h
    )

source_group("src\\ui\\KRender" FILES
    ${KRENDER_SOURCES}
)

#KRenderShapes
set(KRENDER_KRENDERSHAPES_SOURCES
    src/ui/KRender/KRenderShapes/kirendershape.cpp
    src/ui/KRender/KRenderShapes/kirendershape.h
    src/ui/KRender/KRenderShapes/krenderfreehandshape.cpp
    src/ui/KRender/KRenderShapes/krenderfreehandshape.h
    src/ui/KRender/KRenderShapes/krenderlineshape.cpp
    src/ui/KRender/KRenderShapes/krenderlineshape.h
    src/ui/KRender/KRenderShapes/krenderellipseshape.cpp
    src/ui/KRender/KRenderShapes/krenderellipseshape.h
    src/ui/KRender/KRenderShapes/krenderrectshape.cpp
    src/ui/KRender/KRenderShapes/krenderrectshape.h
    src/ui/KRender/KRenderShapes/krenderpentagonshape.cpp
    src/ui/KRender/KRenderShapes/krenderpentagonshape.h
    src/ui/KRender/KRenderShapes/krenderhexagonshape.cpp
    src/ui/KRender/KRenderShapes/krenderhexagonshape.h
    src/ui/KRender/KRenderShapes/krenderstarshape.cpp
    src/ui/KRender/KRenderShapes/krenderstarshape.h
    src/ui/KRender/KRenderShapes/krendertextshape.cpp
    src/ui/KRender/KRenderShapes/krendertextshape.h
)

source_group("src\\ui\\KRender\\KRenderShapes" FILES
    ${KRENDER_KRENDERSHAPES_SOURCES}
)


set(KRENDER_KSHAPES_SOURCES
    src/ui/KRender/KShapes/kishape.cpp
    src/ui/KRender/KShapes/kishape.h
)

source_group("src\\ui\\KRender\\KShapes" FILES
    ${KRENDER_KSHAPES_SOURCES}
)

# 汇总所有源文件
set(SOURCES
    ${MAIN_SRC}
    ${UI_SOURCES}
    ${KTOOLBAR_SOURCES}
    ${KCANVAS_SOURCES}
    ${KCANVAS_KTOOLSTRATEGY_SOURCES}
    ${KPARAMETERSETTING_SOURCES}
    ${KRENDER_SOURCES}
    ${KRENDER_KRENDERSHAPES_SOURCES}
    ${KRENDER_KSHAPES_SOURCES}
)

# # 使用 uic 生成 UI 头文件
# qt5_wrap_ui(UI_HEADERS ${UI_MAIN_SOURCES})

# 将 UI 头文件添加到项目中
list(APPEND HEADERS ${UI_HEADERS})

# res设置资源文件路径
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(ICONS_DIR ${RESOURCES_DIR}/icons)

# 创建Qt资源文件
file(GLOB ICON_FILES 
    "${ICONS_DIR}/*.svg"
    "${ICONS_DIR}/*.png"
)

# 创建资源文件
set(RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/res/Resource.qrc
)

# 自动处理资源文件
qt5_add_resources(RESOURCE_RCC ${RESOURCE_FILES})

# 创建可执行文件
add_executable(KSvgEditor ${SOURCES} ${HEADERS} ${RESOURCE_RCC})

# 链接 Qt 库
target_link_libraries(KSvgEditor Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Charts)

# 设置包含目录
target_include_directories(KSvgEditor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/KToolbar
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/KCanvas
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/KParameterSetting
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/KRender
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/KRender/KRenderShapes
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/KRender/KShapes
)

# qt ui文件编译
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# 文件分组
source_group("src" FILES ${MAIN_SRC})
source_group("src\\ui" FILES ${UI_MAIN_SOURCES} ${UI_SOURCES})
source_group("res" FILES ${RESOURCE_FILES})
source_group("res\\icons" FILES ${ICONS_FILES})