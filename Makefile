TARGET		:=	armas
CXXFLAGS	:=	-std=c++17

all: $(TARGET)

$(TARGET):
	@$(CXX) $(CXXFLAGS) main.cpp -o $@

clean:
	@$(RM) $(TARGET)

re: clean all
