CXXFLAGS = -D _DEBUG  -ggdb -g3 -D_FORTIFY_SOURCES=3 -std=c++17 -Og -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=81920 -Wstack-usage=81920 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: list

list: main_list.o list.o logging.o print_error.o
	@g++ $(CXXFLAGS) build/*.o -o list

logging.o: My_lib/Logger/logging.cpp
	@g++ $(CXXFLAGS) -c My_lib/Logger/logging.cpp -o build/logging.o

print_error.o: My_lib/Assert/print_error.cpp
	@g++ $(CXXFLAGS) -c My_lib/Assert/print_error.cpp -o build/print_error.o

main_list.o: main_list.cpp
	@g++ $(CXXFLAGS) -c main_list.cpp -o build/main_list.o

list.o: list_construction.o list_push.o list_pop.o list_index.o list_error_handler.o
	@

list_construction.o: source/list_construction.cpp
	@g++ $(CXXFLAGS) -c source/list_construction.cpp -o build/list_construction.o

list_push.o: source/list_push.cpp
	@g++ $(CXXFLAGS) -c source/list_push.cpp -o build/list_push.o

list_pop.o: source/list_pop.cpp
	@g++ $(CXXFLAGS) -c source/list_pop.cpp -o build/list_pop.o

list_index.o: source/list_index.cpp
	@g++ $(CXXFLAGS) -c source/list_index.cpp -o build/list_index.o

list_error_handler.o: source/list_error_handler.cpp
	@g++ $(CXXFLAGS) -c source/list_error_handler.cpp -o build/list_error_handler.o

clean:
	rm -rf build/*.o list
