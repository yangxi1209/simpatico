# ---------------------------------------------------------------------
# File: src/simp/patterns.mk
#
# This makefile contains the pattern rule used to compile all source
# files in the src/simp directory tree. This file is included by all 
# makefile files in the src/simp directory tree. 
#
# This file should be included in other makefiles after inclusion of 
# the main config.mk in the build directory, and the util/config.mk 
# and simp/config.mk namespace level config files. 
#-----------------------------------------------------------------------

# All libraries needed in for files in src/simp
LIBS= $(simp_LIB) $(util_LIB)

# C preprocessor macro definitions needed in src/simp
DEFINES=$(UTIL_DEFS) $(SIMP_DEFS)

# Dependencies on build configuration files
MAKE_DEPS= -A$(BLD_DIR)/config.mk
MAKE_DEPS+= -A$(BLD_DIR)/util/config.mk
MAKE_DEPS+= -A$(BLD_DIR)/simp/config.mk

# Pattern rule to compile all *.cpp class source files in src/simp
$(BLD_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(CXX) $(INCLUDES) $(DEFINES) $(CXXFLAGS) -c -o $@ $<
ifdef MAKEDEP
	$(MAKEDEP) $(INCLUDES) $(DEFINES) $(CXX_FLAGS) $(MAKE_DEPS) -S$(SRC_DIR) -B$(BLD_DIR) $<
endif

# Pattern rule to compile all *.cc test programs in src/simp/tests
$(BLD_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(INCLUDES) $(DEFINES) $(TESTFLAGS) -c -o $@ $<
ifdef MAKEDEP
	$(MAKEDEP) $(INCLUDES) $(DEFINES) $(CXX_FLAGS) $(MAKE_DEPS) -S$(SRC_DIR) -B$(BLD_DIR) $<
endif

# Pattern rule to link all *.cc test programs in src/simp/tests
$(BLD_DIR)/%: $(BLD_DIR)/%.o $(LIBS)
	$(CXX) $(INCLUDES) $(DEFINES) $(TESTFLAGS) -o $@ $@.o $(LIBS) $(LDFLAGS)
