cmake_minimum_required(VERSION 3.30)
project(RatRacingEngine)

set(CMAKE_CXX_STANDARD 20)

set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)
set(LIBS_DIR ${CMAKE_SOURCE_DIR}/lib)
set(IMGUI_DIR ${VENDOR_DIR}/imgui)

add_library(GLAD ${VENDOR_DIR}/glad/glad.c)
add_library(STB_IMAGE ${VENDOR_DIR}/stb/stb_image.cpp)
add_library(IMGUI
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(LIBS GLAD STB_IMAGE glfw3 assimp IMGUI)

include_directories(${VENDOR_DIR})
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/backends)

link_directories(${LIBS_DIR})

add_executable(RatRacingEngine src/main.cpp
        src/Engine/Engine.cpp
        src/Engine/Engine.h
        src/Engine/Scene/Scene.cpp
        src/Engine/Scene/Scene.h
        src/Engine/UserInterface/UserInterface.cpp
        src/Engine/UserInterface/UserInterface.h
        src/Core/Core.cpp
        src/Core/Core.h
        src/Input/Input.cpp
        src/Input/Input.h
        src/DeltaTime/Time.cpp
        src/DeltaTime/Time.h
        src/Utils/Utils.cpp
        src/Utils/Utils.h
        src/Engine/Scene/GameObject/Model/Material/TextureMaterial/Texture/Texture.cpp
        src/Engine/Scene/GameObject/Model/Material/TextureMaterial/Texture/Texture.h
        src/Error/Error.cpp
        src/Error/Error.h
        src/Engine/Scene/GameObject/GameObject.cpp
        src/Engine/Scene/GameObject/GameObject.h
        src/Engine/Scene/GameObject/Camera/Camera.cpp
        src/Engine/Scene/GameObject/Camera/Camera.h
        src/Engine/Scene/GameObject/Model/Material/Material.cpp
        src/Engine/Scene/GameObject/Model/Material/Material.h
        src/Engine/Scene/GameObject/Model/Material/DefaultMaterial/DefaultMaterial.cpp
        src/Engine/Scene/GameObject/Model/Material/DefaultMaterial/DefaultMaterial.h
        src/Engine/Scene/GameObject/Model/Material/TextureMaterial/TextureMaterial.cpp
        src/Engine/Scene/GameObject/Model/Material/TextureMaterial/TextureMaterial.h
        src/Engine/Scene/GameObject/Model/Mesh/Mesh.cpp
        src/Engine/Scene/GameObject/Model/Mesh/Mesh.h
        src/Engine/Scene/GameObject/Model/Mesh/Vertex/Vertex.cpp
        src/Engine/Scene/GameObject/Model/Mesh/Vertex/Vertex.h
        src/Engine/Scene/GameObject/Model/Model.cpp
        src/Engine/Scene/GameObject/Model/Model.h
        src/Engine/Shader/Shader.cpp
        src/Engine/Shader/Shader.h
        src/Engine/Scene/GameObject/Light/Light.cpp
        src/Engine/Scene/GameObject/Light/Light.h
        src/Engine/Scene/GameObject/Light/DirectionalLight/DirectionalLight.cpp
        src/Engine/Scene/GameObject/Light/DirectionalLight/DirectionalLight.h
        src/Engine/Scene/GameObject/Light/PointLight/PointLight.cpp
        src/Engine/Scene/GameObject/Light/PointLight/PointLight.h
        src/Engine/Scene/GameObject/Light/SpotLight/SpotLight.cpp
        src/Engine/Scene/GameObject/Light/SpotLight/SpotLight.h)

target_link_libraries(RatRacingEngine ${LIBS})
