

SMACK_FLAGS := --unroll=100
SMACK_FLAGS += --time-limit=86400
SMACK_FLAGS += --integer-encoding=bit-vector


TIME := time -f %e
SMACK := ${TIME} smack ${SMACK_FLAGS}
CORRAL_SMACK := ${SMACK}
BOOGIE_SMACK := ${SMACK} --verifier=boogie
CVC4_SMACK   := ${SMACK} --verifier-options=/bopt:proverOpt:SOLVER=cvc4
YICES2_SMACK := ${SMACK} --solver=yices2 --pointer-encoding=bit-vector

CFLAGS := -Iinclude -I. -Isrc
SMOKE := --clang-options="${CFLAGS} -DSMOKE -DSMACK"
FAIL  := --clang-options="${CFLAGS} -DFAIL -DSMACK"
HARD  := --clang-options="${CFLAGS} -DHARD -DSMACK"
PASS  := --clang-options="${CFLAGS} -DPASS -DSMACK"

mains := $(wildcard src/main*.c)

txt_extension := $(patsubst src/main-%.c,src/%-log.txt,${mains})

smoke_corral_log_files := $(patsubst src/%,smoke-corral-logs/%,${txt_extension})
fail_corral_log_files  := $(patsubst src/%,fail-corral-logs/%,${txt_extension})
hard_corral_log_files  := $(patsubst src/%,hard-corral-logs/%,${txt_extension})
pass_corral_log_files  := $(patsubst src/%,pass-corral-logs/%,${txt_extension})

smoke_boogie_log_files := $(patsubst src/%,smoke-boogie-logs/%,${txt_extension})
fail_boogie_log_files  := $(patsubst src/%,fail-boogie-logs/%,${txt_extension})
hard_boogie_log_files  := $(patsubst src/%,hard-boogie-logs/%,${txt_extension})
pass_boogie_log_files  := $(patsubst src/%,pass-boogie-logs/%,${txt_extension})

smoke_cvc4_log_files   := $(patsubst src/%,smoke-cvc4-logs/%,${txt_extension})
fail_cvc4_log_files    := $(patsubst src/%,fail-cvc4-logs/%,${txt_extension})
hard_cvc4_log_files    := $(patsubst src/%,hard-cvc4-logs/%,${txt_extension})
pass_cvc4_log_files    := $(patsubst src/%,pass-cvc4-logs/%,${txt_extension})

smoke_yices2_log_files := $(patsubst src/%,smoke-yices2-logs/%,${txt_extension})
fail_yices2_log_files  := $(patsubst src/%,fail-yices2-logs/%,${txt_extension})
hard_yices2_log_files  := $(patsubst src/%,hard-yices2-logs/%,${txt_extension})
pass_yices2_log_files  := $(patsubst src/%,pass-yices2-logs/%,${txt_extension})


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
	@echo "    <type>-<solver>"


.PHONY: corral
corral: smoke-corral fail-corral hard-corral pass-corral

.PHONY: boogie
boogie: smoke-boogie fail-boogie hard-boogie pass-boogie

.PHONY: cvc4
cvc4: smoke-cvc4 fail-cvc4 hard-cvc4 pass-cvc4

.PHONY: yices2
yices2: smoke-yices2 fail-yices2 hard-yices2 pass-yices2

.PHONY: smoke
smoke: smoke-corral smoke-boogie smoke-cvc4 smoke-yices2

.PHONY: fail
fail: fail-corral fail-boogie fail-cvc4 fail-yices2

.PHONY: hard
hard: hard-corral hard-boogie hard-cvc4 hard-yices2

.PHONY: pass
pass: pass-corral pass-boogie pass-cvc4 pass-yices2




.PHONY: smoke-corral
smoke-corral: ${smoke_corral_log_files}

.PHONY: fail-corral
fail-corral: ${fail_corral_log_files}

.PHONY: hard-corral
hard-corral: ${hard_corral_log_files}

.PHONY: pass-corral
pass-corral: ${pass_corral_log_files}


.PHONY: smoke-boogie
smoke-boogie: ${smoke_boogie_log_files}

.PHONY: fail-boogie
fail-boogie: ${fail_boogie_log_files}

.PHONY: hard-boogie
hard-boogie: ${hard_boogie_log_files}

.PHONY: pass-boogie
pass-boogie: ${pass_boogie_log_files}


.PHONY: smoke-cvc4
smoke-cvc4: ${smoke_cvc4_log_files}

.PHONY: fail-cvc4
fail-cvc4: ${fail_cvc4_log_files}

.PHONY: hard-cvc4
hard-cvc4: ${hard_cvc4_log_files}

.PHONY: pass-cvc4
pass-cvc4: ${pass_cvc4_log_files}


.PHONY: smoke-yices2
smoke-yices2: ${smoke_yices2_log_files}

.PHONY: fail-yices2
fail-yices2: ${fail_yices2_log_files}

.PHONY: hard-yices2
hard-yices2: ${hard_yices2_log_files}

.PHONY: pass-yices2
pass-yices2: ${pass_yices2_log_files}





smoke-corral-logs/%-log.txt: src/main-%.c | smoke-corral-logs
	! $(CORRAL_SMACK) ${SMOKE} $^ > $@ 2>&1

fail-corral-logs/%-log.txt: src/main-%.c | fail-corral-logs
	! $(CORRAL_SMACK) ${FAIL} $^ > $@ 2>&1

hard-corral-logs/%-log.txt: src/main-%.c | hard-corral-logs
	! $(CORRAL_SMACK) ${HARD} $^ > $@ 2>&1

pass-corral-logs/%-log.txt: src/main-%.c | pass-corral-logs
	$(CORRAL_SMACK) ${PASS} $^ > $@ 2>&1


smoke-boogie-logs/%-log.txt: src/main-%.c | smoke-boogie-logs
	! $(BOOGIE_SMACK) ${SMOKE} $^ > $@ 2>&1

fail-boogie-logs/%-log.txt: src/main-%.c | fail-boogie-logs
	! $(BOOGIE_SMACK) ${FAIL} $^ > $@ 2>&1

hard-boogie-logs/%-log.txt: src/main-%.c | hard-boogie-logs
	! $(BOOGIE_SMACK) ${HARD} $^ > $@ 2>&1

pass-boogie-logs/%-log.txt: src/main-%.c | pass-boogie-logs
	$(BOOGIE_SMACK) ${PASS} $^ > $@ 2>&1


smoke-cvc4-logs/%-log.txt: src/main-%.c | smoke-cvc4-logs
	! $(CVC4_SMACK) ${SMOKE} $^ > $@ 2>&1

fail-cvc4-logs/%-log.txt: src/main-%.c | fail-cvc4-logs
	! $(CVC4_SMACK) ${FAIL} $^ > $@ 2>&1

hard-cvc4-logs/%-log.txt: src/main-%.c | hard-cvc4-logs
	! $(CVC4_SMACK) ${HARD} $^ > $@ 2>&1

pass-cvc4-logs/%-log.txt: src/main-%.c | pass-cvc4-logs
	$(CVC4_SMACK) ${PASS} $^ > $@ 2>&1


smoke-yices2-logs/%-log.txt: src/main-%.c | smoke-yices2-logs
	! $(YICES2_SMACK) ${SMOKE} $^ > $@ 2>&1

fail-yices2-logs/%-log.txt: src/main-%.c | fail-yices2-logs
	! $(YICES2_SMACK) ${FAIL} $^ > $@ 2>&1

hard-yices2-logs/%-log.txt: src/main-%.c | hard-yices2-logs
	! $(YICES2_SMACK) ${HARD} $^ > $@ 2>&1

pass-yices2-logs/%-log.txt: src/main-%.c | pass-yices2-logs
	$(YICES2_SMACK) ${PASS} $^ > $@ 2>&1






smoke-corral-logs:
	mkdir -p smoke-corral-logs

fail-corral-logs:
	mkdir -p fail-corral-logs

hard-corral-logs:
	mkdir -p hard-corral-logs

pass-corral-logs:
	mkdir -p pass-corral-logs


smoke-boogie-logs:
	mkdir -p smoke-boogie-logs

fail-boogie-logs:
	mkdir -p fail-boogie-logs

hard-boogie-logs:
	mkdir -p hard-boogie-logs

pass-boogie-logs:
	mkdir -p pass-boogie-logs


smoke-cvc4-logs:
	mkdir -p smoke-cvc4-logs

fail-cvc4-logs:
	mkdir -p fail-cvc4-logs

hard-cvc4-logs:
	mkdir -p hard-cvc4-logs

pass-cvc4-logs:
	mkdir -p pass-cvc4-logs


smoke-yices2-logs:
	mkdir -p smoke-yices2-logs

fail-yices2-logs:
	mkdir -p fail-yices2-logs

hard-yices2-logs:
	mkdir -p hard-yices2-logs

pass-yices2-logs:
	mkdir -p pass-yices2-logs





.PHONY: clean
clean:
	$(RM) *~
	$(RM) */*~
	$(RM) -r smoke-corral-logs
	$(RM) -r fail-corral-logs
	$(RM) -r hard-corral-logs
	$(RM) -r pass-corral-logs
	$(RM) -r smoke-cvc4-logs
	$(RM) -r fail-cvc4-logs
	$(RM) -r hard-cvc4-logs
	$(RM) -r pass-cvc4-logs
	$(RM) -r smoke-yices2-logs
	$(RM) -r fail-yices2-logs
	$(RM) -r hard-yices2-logs
	$(RM) -r pass-yices2-logs
	$(RM) -r smoke-boogie-logs
	$(RM) -r fail-boogie-logs
	$(RM) -r hard-boogie-logs
	$(RM) -r pass-boogie-logs
