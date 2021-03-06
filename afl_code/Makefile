SOURCES = afl_introIspc.cpp base64.cpp Bound.cpp Edge.cpp intro.cpp main_.cpp Node.cpp PngImage.cpp Point.cpp Renderer.cpp RoadSegment.cpp Segment.cpp Tile.cpp
TARGET  = libaflintro.so

CXX      = g++
CXXFLAGS = -fPIC -Wall -g -O0 -Wno-strict-aliasing
INCLUDES = -I$(HANA_SDK_PATH)/include
LDFLAGS  = -shared -lhdbaflsdk -Wl,-no-undefined -L$(HANA_SDK_PATH)/libs -lpng -lagg
RM       = rm -f

OBJS = $(patsubst %.cpp,%.o,$(SOURCES))
DEPS = $(patsubst %.cpp,%.o.dep,$(SOURCES))

ifndef HANA_SDK_PATH
$(error Environment is not set up: HANA_SDK_PATH is not defined)
endif

.PHONY: all clean installer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)
	@echo "Run \"make installer\" to build an installation package for your AFL!"

afl_introIspc.cpp: afl_intro.afx
	@echo -n "Validating AFX... "
	$(HANA_SDK_PATH)/tools/afxcheck afl_intro.afx $(HANA_SDK_PATH)/tools/afx_schema.xsd
	@echo -n "Generating supporting files... "
	$(HANA_SDK_PATH)/tools/aflgen -m -f76 -afl -sdk afl_intro.afx
	@echo "Don't forget to add new functions to the *.lst file!"
	@echo

.cpp.o: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	@$(CXX) $(CXXFLAGS) -MG -MP -MT $@ -MF $@.dep -MM $<

-include $(DEPS)

clean:
	$(RM) $(TARGET) *.o *.o.dep afl_intro.h afl_introWrapper.h afl_introFactory.h afl_introIspc.cpp

installer: $(TARGET)
	@echo -n "Creating installation package... "
	$(HANA_SDK_PATH)/tools/aflinstaller

