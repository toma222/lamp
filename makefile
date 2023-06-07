
CXX = g++
RULES = -Wall -O2 -std=c++17
LIB = -Llib -lopengl32 -lglfw3dll -ldl -lpthread -llibsoundio
INCLUDE = -Iinclude -Iinclude/imgui -Iinclude/imgui/backends 

OBJECTS = obj/Window.o obj/Timeline.o obj/Viewer.o obj/audio.o obj/wav.o obj/registry.o obj/table.o obj/UUID.o obj/Toolbar.o

IMGUI_DIR = include/imgui
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
IMGUI_OBJ = obj/implot.o obj/implot_items.o obj/implot_demo.o
IMGUI_OBJ += obj/imgui.o obj/imgui_widgets.o obj/imgui_tables.o obj/imgui_draw.o obj/imgui_demo.o obj/imgui_impl_glfw.o obj/imgui_impl_opengl3.o

FFT_OBJ = obj/fft.o obj/complex.o

obj/%.o:include/FFT/%.cpp
	$(CXX) $(RULES) $(INCLUDE) -c -o $@ $<

obj/%.o:include/imgui/%.cpp
	$(CXX) $(RULES) $(INCLUDE) -c -o $@ $<

obj/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(RULES) $(INCLUDE) -c -o $@ $<

obj/%.o : src/%.cpp
	$(CXX) $(RULES) -c -o $@ $< $(LIB) $(INCLUDE)

obj/%.o : src/gui/%.cpp
	$(CXX) $(RULES) -c -o $@ $< $(LIB) $(INCLUDE)

obj/%.o : src/panels/%.cpp
	$(CXX) $(RULES) -c -o $@ $< $(LIB) $(INCLUDE)

obj/%.o : src/file/%.cpp
	$(CXX) $(RULES) -c -o $@ $< $(LIB) $(INCLUDE)

obj/%.o : src/core/%.cpp src/core/%.hpp
	$(CXX) $(RULES) -c -o $@ $< $(LIB) $(INCLUDE)

obj/%.o : src/algorithms/%.cpp src/algorithms/%.hpp
	$(CXX) $(RULES) -c -o $@ $< $(LIB) $(INCLUDE)

makeApp : $(OBJECTS) $(IMGUI_OBJ) $(FFT_OBJ)
	$(CXX) $(RULES) main.cpp -o bin/game $(OBJECTS) $(IMGUI_OBJ) $(FFT_OBJ) $(LIB) $(INCLUDE)
	make run
	
run:
	bin/game
