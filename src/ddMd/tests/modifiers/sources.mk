ddMd_tests_modifiers_=ddMd/tests/modifiers/Test.cpp

ddMd_tests_modifiers_SRCS=\
     $(addprefix $(SRC_DIR)/, $(ddMd_tests_modifiers_))
ddMd_tests_modifiers_OBJS=\
     $(addprefix $(OBJ_DIR)/, $(ddMd_tests_modifiers_:.cpp=.o))

