FILE(GLOB sources Main.cpp)
LINK_LIBRARIES(lsys)
ADD_EXECUTABLE(psgen ${sources})
