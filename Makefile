

SMACK_FLAGS := --unroll=100
SMACK_FLAGS += --time-limit=86400
SMACK_FLAGS += --bit-precise

SMACK := time -f %e smack ${SMACK_FLAGS}
CORRAL_SMACK := ${SMACK}
BOOGIE_SMACK := ${SMACK} --verifier=boogie
CVC4_SMACK   := ${SMACK} --verifier-options=/bopt:proverOpt:SOLVER=cvc4
YICES2_SMACK := ${SMACK} --solver=yices2 --bit-precise-pointers

CFLAGS := -Iinclude -I. -DLEN=1
SMOKE := --clang-options="${CFLAGS} -DSMOKE"
FAIL  := --clang-options="${CFLAGS} -DFAIL"
HARD  := --clang-options="${CFLAGS} -DHARD"
PASS  := --clang-options="${CFLAGS} -DPASS"

source := $(wildcard src/*.c)

txt_extension := $(patsubst %.c,%_log.txt,${source})

smoke_corral_log_files := $(patsubst src/%,smoke_corral_logs/%,${txt_extension})
fail_corral_log_files  := $(patsubst src/%,fail_corral_logs/%,${txt_extension})
hard_corral_log_files  := $(patsubst src/%,hard_corral_logs/%,${txt_extension})
pass_corral_log_files  := $(patsubst src/%,pass_corral_logs/%,${txt_extension})

smoke_boogie_log_files := $(patsubst src/%,smoke_boogie_logs/%,${txt_extension})
fail_boogie_log_files  := $(patsubst src/%,fail_boogie_logs/%,${txt_extension})
hard_boogie_log_files  := $(patsubst src/%,hard_boogie_logs/%,${txt_extension})
pass_boogie_log_files  := $(patsubst src/%,pass_boogie_logs/%,${txt_extension})

smoke_cvc4_log_files   := $(patsubst src/%,smoke_cvc4_logs/%,${txt_extension})
fail_cvc4_log_files    := $(patsubst src/%,fail_cvc4_logs/%,${txt_extension})
hard_cvc4_log_files    := $(patsubst src/%,hard_cvc4_logs/%,${txt_extension})
pass_cvc4_log_files    := $(patsubst src/%,pass_cvc4_logs/%,${txt_extension})

smoke_yices2_log_files := $(patsubst src/%,smoke_yices2_logs/%,${txt_extension})
fail_yices2_log_files  := $(patsubst src/%,fail_yices2_logs/%,${txt_extension})
hard_yices2_log_files  := $(patsubst src/%,hard_yices2_logs/%,${txt_extension})
pass_yices2_log_files  := $(patsubst src/%,pass_yices2_logs/%,${txt_extension})


.PHONY: help
help:
	@echo "Possible targets are:"
	@echo "  all types for a solver:"
	@echo "    corral"
	@echo "    boogie"
	@echo "    cvc4"
	@echo "    yices2"
	@echo "  all solvers for a target:"
	@echo "    smoke"
	@echo "    fail"
	@echo "    hard"
	@echo "    pass"
	@echo "  specific type for specific solver"
	@echo "    <type>_<solver>"


.PHONY: corral
all: smoke_corral fail_corral hard_corral pass_corral

.PHONY: boogie
boogie: smoke_boogie fail_boogie hard_boogie pass_boogie

.PHONY: cvc4
cvc4: smoke_cvc4 fail_cvc4 hard_cvc4 pass_cvc4

.PHONY: yices2
yices2: smoke_yices2 fail_yices2 hard_yices2 pass_yices2

.PHONY: smoke
smoke: smoke-corral smoke-boogie smoke-cvc4 smoke-yices

.PHONY: fail
fail: fail-corral fail-boogie fail-cvc4 fail-yices

.PHONY: hard
hard: hard-corral hard-boogie hard-cvc4 hard-yices

.PHONY: pass
pass: pass-corral pass-boogie pass-cvc4 pass-yices




.PHONY: smoke_corral
smoke_corral: ${smoke_corral_log_files}

.PHONY: fail_corral
fail_corral: ${fail_corral_log_files}

.PHONY: hard_corral
hard_corral: ${hard_corral_log_files}

.PHONY: pass_corral
pass_corral: ${pass_corral_log_files}


.PHONY: smoke_boogie
smoke_boogie: ${smoke_boogie_log_files}

.PHONY: fail_boogie
fail_boogie: ${fail_boogie_log_files}

.PHONY: hard_boogie
hard_boogie: ${hard_boogie_log_files}

.PHONY: pass_boogie
pass_boogie: ${pass_boogie_log_files}


.PHONY: smoke_cvc4
smoke_cvc4: ${smoke_cvc4_log_files}

.PHONY: fail_cvc4
fail_cvc4: ${fail_cvc4_log_files}

.PHONY: hard_cvc4
hard_cvc4: ${hard_cvc4_log_files}

.PHONY: pass_cvc4
pass_cvc4: ${pass_cvc4_log_files}


.PHONY: smoke_yices2
smoke_yices2: ${smoke_yices2_log_files}

.PHONY: fail_yices2
fail_yices2: ${fail_yices2_log_files}

.PHONY: hard_yices2
hard_yices2: ${hard_yices2_log_files}

.PHONY: pass_yices2
pass_yices2: ${pass_yices2_log_files}





smoke_corral_logs/%_log.txt: src/%.c | smoke_corral_logs
	! $(CORRAL_SMACK) ${SMOKE} $^ > $@ 2>&1

fail_corral_logs/%_log.txt: src/%.c | fail_corral_logs
	! $(CORRAL_SMACK) ${FAIL} $^ > $@ 2>&1

hard_corral_logs/%_log.txt: src/%.c | hard_corral_logs
	! $(CORRAL_SMACK) ${HARD} $^ > $@ 2>&1

pass_corral_logs/%_log.txt: src/%.c | pass_corral_logs
	$(CORRAL_SMACK) ${PASS} $^ > $@ 2>&1


smoke_boogie_logs/%_log.txt: src/%.c | smoke_boogie_logs
	! $(BOOGIE_SMACK) ${SMOKE} $^ > $@ 2>&1

fail_boogie_logs/%_log.txt: src/%.c | fail_boogie_logs
	! $(BOOGIE_SMACK) ${FAIL} $^ > $@ 2>&1

hard_boogie_logs/%_log.txt: src/%.c | hard_boogie_logs
	! $(BOOGIE_SMACK) ${HARD} $^ > $@ 2>&1

pass_boogie_logs/%_log.txt: src/%.c | pass_boogie_logs
	$(BOOGIE_SMACK) ${PASS} $^ > $@ 2>&1


smoke_cvc4_logs/%_log.txt: src/%.c | smoke_cvc4_logs
	! $(CVC4_SMACK) ${SMOKE} $^ > $@ 2>&1

fail_cvc4_logs/%_log.txt: src/%.c | fail_cvc4_logs
	! $(CVC4_SMACK) ${FAIL} $^ > $@ 2>&1

hard_cvc4_logs/%_log.txt: src/%.c | hard_cvc4_logs
	! $(CVC4_SMACK) ${HARD} $^ > $@ 2>&1

pass_cvc4_logs/%_log.txt: src/%.c | pass_cvc4_logs
	$(CVC4_SMACK) ${PASS} $^ > $@ 2>&1


smoke_yices2_logs/%_log.txt: src/%.c | smoke_yices2_logs
	! $(YICES2_SMACK) ${SMOKE} $^ > $@ 2>&1

fail_yices2_logs/%_log.txt: src/%.c | fail_yices2_logs
	! $(YICES2_SMACK) ${FAIL} $^ > $@ 2>&1

hard_yices2_logs/%_log.txt: src/%.c | hard_yices2_logs
	! $(YICES2_SMACK) ${HARD} $^ > $@ 2>&1

pass_yices2_logs/%_log.txt: src/%.c | pass_yices2_logs
	$(YICES2_SMACK) ${PASS} $^ > $@ 2>&1






smoke_corral_logs:
	mkdir -p smoke_corral_logs

fail_corral_logs:
	mkdir -p fail_corral_logs

hard_corral_logs:
	mkdir -p hard_corral_logs

pass_corral_logs:
	mkdir -p pass_corral_logs


smoke_boogie_logs:
	mkdir -p smoke_boogie_logs

fail_boogie_logs:
	mkdir -p fail_boogie_logs

hard_boogie_logs:
	mkdir -p hard_boogie_logs

pass_boogie_logs:
	mkdir -p pass_boogie_logs


smoke_cvc4_logs:
	mkdir -p smoke_cvc4_logs

fail_cvc4_logs:
	mkdir -p fail_cvc4_logs

hard_cvc4_logs:
	mkdir -p hard_cvc4_logs

pass_cvc4_logs:
	mkdir -p pass_cvc4_logs


smoke_yices2_logs:
	mkdir -p smoke_yices2_logs

fail_yices2_logs:
	mkdir -p fail_yices2_logs

hard_yices2_logs:
	mkdir -p hard_yices2_logs

pass_yices2_logs:
	mkdir -p pass_yices2_logs





.PHONY: clean
clean:
	$(RM) *~
	$(RM) */*~
	$(RM) -r smoke_corral_logs
	$(RM) -r fail_corral_logs
	$(RM) -r hard_corral_logs
	$(RM) -r pass_corral_logs
	$(RM) -r smoke_cvc4_logs
	$(RM) -r fail_cvc4_logs
	$(RM) -r hard_cvc4_logs
	$(RM) -r pass_cvc4_logs
	$(RM) -r smoke_yices2_logs
	$(RM) -r fail_yices2_logs
	$(RM) -r hard_yices2_logs
	$(RM) -r pass_yices2_logs
	$(RM) -r smoke_boogie_logs
	$(RM) -r fail_boogie_logs
	$(RM) -r hard_boogie_logs
	$(RM) -r pass_boogie_logs
