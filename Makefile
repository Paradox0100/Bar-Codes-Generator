build:
	g++ src/*.cpp -o program -I /usr/include/opencv4 -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui
clean:
	rm -f program
