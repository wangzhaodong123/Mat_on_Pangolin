# OPENCV
INCLUDE_OPENCV = $(shell pkg-config --cflags opencv)
LIBDIR_OPENCV = $(shell pkg-config --libs opencv)

# PANGOLIN
INCLUDE_PANGOLIN = -I /usr/local/include/pangolin
LIBDIR_PANGOLIN =  /usr/local/lib/libpangolin.so \
		/usr/lib/x86_64-linux-gnu/libGL.so
# eigen3
INCLUDE_EIGEN = -I /usr/include/eigen3

# OTHER
LIBDIR_OTHER = -L /usr/lib/x86_64-linux-gnu/libGLU.so \
		/usr/lib/x86_64-linux-gnu/libGL.so \
		/usr/lib/x86_64-linux-gnu/libGLEW.so \
		/usr/lib/x86_64-linux-gnu/libSM.so \
		/usr/lib/x86_64-linux-gnu/libICE.so \
		/usr/lib/x86_64-linux-gnu/libX11.so \
		/usr/lib/x86_64-linux-gnu/libXext.so \
		/usr/lib/x86_64-linux-gnu/libdc1394.so \
		/usr/lib/x86_64-linux-gnu/libavcodec.so \
		/usr/lib/x86_64-linux-gnu/libavformat.so \
		/usr/lib/x86_64-linux-gnu/libavutil.so \
		/usr/lib/x86_64-linux-gnu/libswscale.so \
		/opt/ros/indigo/lib/librealsense.so \
		/usr/lib/libOpenNI.so \
		/usr/lib/libOpenNI2.so \
		/usr/lib/x86_64-linux-gnu/libpng.so \
		/usr/lib/x86_64-linux-gnu/libz.so \
		/usr/lib/x86_64-linux-gnu/libjpeg.so \
		/usr/lib/x86_64-linux-gnu/libtiff.so \
		/usr/lib/x86_64-linux-gnu/libIlmImf.so

all:mat_on_pangolin
	mv *.o lib/
	mv mat_on_pangolin bin/
mat_on_pangolin:mat_on_pangolin.o
	g++ -std=c++11 -O3 -Wno-deprecated -o mat_on_pangolin mat_on_pangolin.o $(LIBDIR_PANGOLIN) $(LIBDIR_OPENCV)

mat_on_pangolin.o: src/mat_on_pangolin.cpp
	g++ -std=c++11 -O3 -Wno-deprecated -c src/mat_on_pangolin.cpp $(INCLUDE_PANGOLIN) $(INCLUDE_EIGEN) $(INCLUDE_OPENCV)
clean:
	rm -f lib/*.o bin/*
