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

add_executable(RatRacingEngine
        src/main.cpp
        src/Engine/Engine.cpp
        src/Engine/Engine.h
        src/Engine/Project/Scene/Scene.cpp
        src/Engine/Project/Scene/Scene.h
        src/Engine/UserInterface/UserInterface.cpp
        src/Engine/UserInterface/UserInterface.h
        src/Resources/Resources.cpp
        src/Resources/Resources.h
        src/Core/Core.cpp
        src/Core/Core.h
        src/Core/Input/Input.cpp
        src/Core/Input/Input.h
        src/Core/Time/Time.cpp
        src/Core/Time/Time.h
        src/Utils/Utils.cpp
        src/Utils/Utils.h
        src/Error/Error.cpp
        src/Error/Error.h
        src/GameObject/GameObject.cpp
        src/GameObject/GameObject.h
        src/GameObject/Components/Camera/Camera.cpp
        src/GameObject/Components/Camera/Camera.h
        src/GameObject/Components/Light/Light.cpp
        src/GameObject/Components/Light/Light.h
        src/GameObject/Components/Light/DirectionalLight/DirectionalLight.cpp
        src/GameObject/Components/Light/DirectionalLight/DirectionalLight.h
        src/GameObject/Components/Light/PointLight/PointLight.cpp
        src/GameObject/Components/Light/PointLight/PointLight.h
        src/GameObject/Components/Light/SpotLight/SpotLight.cpp
        src/GameObject/Components/Light/SpotLight/SpotLight.h
        src/GameObject/Components/Model/Model.cpp
        src/GameObject/Components/Model/Model.h
        src/GameObject/Components/Model/Mesh/Mesh.cpp
        src/GameObject/Components/Model/Mesh/Mesh.h
        src/GameObject/Components/Model/Mesh/Vertex/Vertex.cpp
        src/GameObject/Components/Model/Mesh/Vertex/Vertex.h
        src/Material/Material.cpp
        src/Material/Material.h
        src/Material/DefaultMaterial/DefaultMaterial.cpp
        src/Material/DefaultMaterial/DefaultMaterial.h
        src/Material/TextureMaterial/TextureMaterial.cpp
        src/Material/TextureMaterial/TextureMaterial.h
        src/Material/TextureMaterial/Texture/Texture.cpp
        src/Material/TextureMaterial/Texture/Texture.h
        src/Shader/Shader.cpp
        src/Shader/Shader.h
        src/Dispose/IDisposable.h
        src/Engine/Project/Renderer/Renderer.cpp
        src/Engine/Project/Renderer/Renderer.h
        src/Engine/Project/Renderer/RenderData.h
        src/Engine/Project/Renderer/RenderTypes.h
        src/Engine/Project/Project.cpp
        src/Engine/Project/Project.h
)

target_link_libraries(RatRacingEngine ${LIBS})
