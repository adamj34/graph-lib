FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG devel
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(catch2)


add_executable(gralphTests
    WeightedGraphTest.cpp
    primTest.cpp
    dijkstraTest.cpp
)

target_link_libraries(gralphTests
    PRIVATE
        Catch2::Catch2WithMain
        gralph
)
