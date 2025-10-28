SRC_DIR := src
INC_DIR := include
TARGET_DIR := target
GNUPLOT_DIR := plots/gnuplot-files
REPORT_DIR := report

RPRT := $(REPORT_DIR)/report.pdf
EXE := $(TARGET_DIR)/main
INC := $(wildcard $(INC_DIR)/*.h)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(SRC))
GNP := $(wildcard $(GNUPLOT_DIR)/*.p)

CPPC := g++
CPPFLAGS := -fopenmp -lpthread -Wall
GNPLT := gnuplot
PDFLTX := pdflatex

OUTPUT := --output-directory

.PHONY: all

all: clean run-src compile-gnp run-report clean-aux clean-target

run-src: $(EXE)
	@echo "Running.."
	@./$<
 
$(EXE): $(OBJ) | $(TARGET_DIR)
	@echo "Building binaries."
	@$(CPPC) $^ -o $@

$(TARGET_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC) | $(TARGET_DIR)
	@echo "Building objects.."
	@$(CPPC) $(CPPFLAGS) -c $< -o $@ -I $(INC_DIR) 

$(TARGET_DIR):
	@echo "Create target dir.."
	@mkdir -p $@

compile-gnp: $(GNP)
	@echo "Compile gnuplot files.."
	@$(foreach file_name, $(GNP), $(GNPLT) $(file_name);)

run-report: $(RPRT)
	@echo "Running a report.."
	@zathura $<

$(RPRT): $(REPORT_DIR)/*.tex
	@echo "Building pdf.."
	$(PDFLTX) $(OUTPUT)=$(REPORT_DIR) $<
	$(PDFLTX) $(OUTPUT)=$(REPORT_DIR) $<

clean-aux:
	@echo "Cleaning up auxiliary files.."
	@find $(REPORT_DIR) -type f ! -name '*.pdf' ! -name '*.tex' -delete

clean-target:
	@echo "Cleaning the target dir.."
	@$(RM) -rv $(TARGET_DIR) 

clean:
	@echo "Cleaning up.."
	@$(RM) $(RPRT)
