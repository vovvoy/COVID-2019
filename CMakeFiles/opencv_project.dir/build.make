# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/936/bin/cmake

# The command to remove a file.
RM = /snap/cmake/936/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ljerrica/Desktop/opencv_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ljerrica/Desktop/opencv_project

# Include any dependencies generated for this target.
include CMakeFiles/opencv_project.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/opencv_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opencv_project.dir/flags.make

CMakeFiles/opencv_project.dir/main.cpp.o: CMakeFiles/opencv_project.dir/flags.make
CMakeFiles/opencv_project.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljerrica/Desktop/opencv_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opencv_project.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv_project.dir/main.cpp.o -c /home/ljerrica/Desktop/opencv_project/main.cpp

CMakeFiles/opencv_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_project.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljerrica/Desktop/opencv_project/main.cpp > CMakeFiles/opencv_project.dir/main.cpp.i

CMakeFiles/opencv_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_project.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljerrica/Desktop/opencv_project/main.cpp -o CMakeFiles/opencv_project.dir/main.cpp.s

CMakeFiles/opencv_project.dir/Weapon.cpp.o: CMakeFiles/opencv_project.dir/flags.make
CMakeFiles/opencv_project.dir/Weapon.cpp.o: Weapon.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljerrica/Desktop/opencv_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/opencv_project.dir/Weapon.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv_project.dir/Weapon.cpp.o -c /home/ljerrica/Desktop/opencv_project/Weapon.cpp

CMakeFiles/opencv_project.dir/Weapon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_project.dir/Weapon.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljerrica/Desktop/opencv_project/Weapon.cpp > CMakeFiles/opencv_project.dir/Weapon.cpp.i

CMakeFiles/opencv_project.dir/Weapon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_project.dir/Weapon.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljerrica/Desktop/opencv_project/Weapon.cpp -o CMakeFiles/opencv_project.dir/Weapon.cpp.s

CMakeFiles/opencv_project.dir/Enemy.cpp.o: CMakeFiles/opencv_project.dir/flags.make
CMakeFiles/opencv_project.dir/Enemy.cpp.o: Enemy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljerrica/Desktop/opencv_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/opencv_project.dir/Enemy.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv_project.dir/Enemy.cpp.o -c /home/ljerrica/Desktop/opencv_project/Enemy.cpp

CMakeFiles/opencv_project.dir/Enemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_project.dir/Enemy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljerrica/Desktop/opencv_project/Enemy.cpp > CMakeFiles/opencv_project.dir/Enemy.cpp.i

CMakeFiles/opencv_project.dir/Enemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_project.dir/Enemy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljerrica/Desktop/opencv_project/Enemy.cpp -o CMakeFiles/opencv_project.dir/Enemy.cpp.s

CMakeFiles/opencv_project.dir/Game.cpp.o: CMakeFiles/opencv_project.dir/flags.make
CMakeFiles/opencv_project.dir/Game.cpp.o: Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ljerrica/Desktop/opencv_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/opencv_project.dir/Game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv_project.dir/Game.cpp.o -c /home/ljerrica/Desktop/opencv_project/Game.cpp

CMakeFiles/opencv_project.dir/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_project.dir/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ljerrica/Desktop/opencv_project/Game.cpp > CMakeFiles/opencv_project.dir/Game.cpp.i

CMakeFiles/opencv_project.dir/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_project.dir/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ljerrica/Desktop/opencv_project/Game.cpp -o CMakeFiles/opencv_project.dir/Game.cpp.s

# Object files for target opencv_project
opencv_project_OBJECTS = \
"CMakeFiles/opencv_project.dir/main.cpp.o" \
"CMakeFiles/opencv_project.dir/Weapon.cpp.o" \
"CMakeFiles/opencv_project.dir/Enemy.cpp.o" \
"CMakeFiles/opencv_project.dir/Game.cpp.o"

# External object files for target opencv_project
opencv_project_EXTERNAL_OBJECTS =

opencv_project: CMakeFiles/opencv_project.dir/main.cpp.o
opencv_project: CMakeFiles/opencv_project.dir/Weapon.cpp.o
opencv_project: CMakeFiles/opencv_project.dir/Enemy.cpp.o
opencv_project: CMakeFiles/opencv_project.dir/Game.cpp.o
opencv_project: CMakeFiles/opencv_project.dir/build.make
opencv_project: /usr/local/lib/libopencv_gapi.so.4.5.3
opencv_project: /usr/local/lib/libopencv_stitching.so.4.5.3
opencv_project: /usr/local/lib/libopencv_aruco.so.4.5.3
opencv_project: /usr/local/lib/libopencv_barcode.so.4.5.3
opencv_project: /usr/local/lib/libopencv_bgsegm.so.4.5.3
opencv_project: /usr/local/lib/libopencv_bioinspired.so.4.5.3
opencv_project: /usr/local/lib/libopencv_ccalib.so.4.5.3
opencv_project: /usr/local/lib/libopencv_dnn_objdetect.so.4.5.3
opencv_project: /usr/local/lib/libopencv_dnn_superres.so.4.5.3
opencv_project: /usr/local/lib/libopencv_dpm.so.4.5.3
opencv_project: /usr/local/lib/libopencv_face.so.4.5.3
opencv_project: /usr/local/lib/libopencv_freetype.so.4.5.3
opencv_project: /usr/local/lib/libopencv_fuzzy.so.4.5.3
opencv_project: /usr/local/lib/libopencv_hfs.so.4.5.3
opencv_project: /usr/local/lib/libopencv_img_hash.so.4.5.3
opencv_project: /usr/local/lib/libopencv_intensity_transform.so.4.5.3
opencv_project: /usr/local/lib/libopencv_line_descriptor.so.4.5.3
opencv_project: /usr/local/lib/libopencv_mcc.so.4.5.3
opencv_project: /usr/local/lib/libopencv_quality.so.4.5.3
opencv_project: /usr/local/lib/libopencv_rapid.so.4.5.3
opencv_project: /usr/local/lib/libopencv_reg.so.4.5.3
opencv_project: /usr/local/lib/libopencv_rgbd.so.4.5.3
opencv_project: /usr/local/lib/libopencv_saliency.so.4.5.3
opencv_project: /usr/local/lib/libopencv_stereo.so.4.5.3
opencv_project: /usr/local/lib/libopencv_structured_light.so.4.5.3
opencv_project: /usr/local/lib/libopencv_superres.so.4.5.3
opencv_project: /usr/local/lib/libopencv_surface_matching.so.4.5.3
opencv_project: /usr/local/lib/libopencv_tracking.so.4.5.3
opencv_project: /usr/local/lib/libopencv_videostab.so.4.5.3
opencv_project: /usr/local/lib/libopencv_wechat_qrcode.so.4.5.3
opencv_project: /usr/local/lib/libopencv_xfeatures2d.so.4.5.3
opencv_project: /usr/local/lib/libopencv_xobjdetect.so.4.5.3
opencv_project: /usr/local/lib/libopencv_xphoto.so.4.5.3
opencv_project: /usr/local/lib/libopencv_shape.so.4.5.3
opencv_project: /usr/local/lib/libopencv_highgui.so.4.5.3
opencv_project: /usr/local/lib/libopencv_datasets.so.4.5.3
opencv_project: /usr/local/lib/libopencv_plot.so.4.5.3
opencv_project: /usr/local/lib/libopencv_text.so.4.5.3
opencv_project: /usr/local/lib/libopencv_ml.so.4.5.3
opencv_project: /usr/local/lib/libopencv_phase_unwrapping.so.4.5.3
opencv_project: /usr/local/lib/libopencv_optflow.so.4.5.3
opencv_project: /usr/local/lib/libopencv_ximgproc.so.4.5.3
opencv_project: /usr/local/lib/libopencv_video.so.4.5.3
opencv_project: /usr/local/lib/libopencv_videoio.so.4.5.3
opencv_project: /usr/local/lib/libopencv_dnn.so.4.5.3
opencv_project: /usr/local/lib/libopencv_imgcodecs.so.4.5.3
opencv_project: /usr/local/lib/libopencv_objdetect.so.4.5.3
opencv_project: /usr/local/lib/libopencv_calib3d.so.4.5.3
opencv_project: /usr/local/lib/libopencv_features2d.so.4.5.3
opencv_project: /usr/local/lib/libopencv_flann.so.4.5.3
opencv_project: /usr/local/lib/libopencv_photo.so.4.5.3
opencv_project: /usr/local/lib/libopencv_imgproc.so.4.5.3
opencv_project: /usr/local/lib/libopencv_core.so.4.5.3
opencv_project: CMakeFiles/opencv_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ljerrica/Desktop/opencv_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable opencv_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opencv_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opencv_project.dir/build: opencv_project
.PHONY : CMakeFiles/opencv_project.dir/build

CMakeFiles/opencv_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opencv_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opencv_project.dir/clean

CMakeFiles/opencv_project.dir/depend:
	cd /home/ljerrica/Desktop/opencv_project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ljerrica/Desktop/opencv_project /home/ljerrica/Desktop/opencv_project /home/ljerrica/Desktop/opencv_project /home/ljerrica/Desktop/opencv_project /home/ljerrica/Desktop/opencv_project/CMakeFiles/opencv_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opencv_project.dir/depend
