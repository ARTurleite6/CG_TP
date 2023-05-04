set(IMGUI_PATH imgui)

include_directories(${IMGUI_PATH} ${IMGUI_PATH}/backends)
file(GLOB imgui_sources ${IMGUI_PATH}/*.cpp ${IMGUI_PATH}/backend/)
