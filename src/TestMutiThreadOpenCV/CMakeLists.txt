ADD_EXECUTABLE(test ./mainthread.cpp ./JsonMap.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
target_link_libraries(test boost_system boost_thread libjsoncpp.a Match pthread opencv_core opencv_imgproc opencv_highgui opencv_ml opencv_video opencv_features2d opencv_calib3d
    opencv_objdetect opencv_contrib opencv_legacy opencv_flann)
