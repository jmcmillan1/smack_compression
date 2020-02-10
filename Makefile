

SMACK_FLAGS := --unroll=67
SMACK_FLAGS += --time-limit=86400
SMACK_FLAGS += --bit-precise
SMACK_FLAGS += --clang-options="-Ialgorithms -Iinclude"

SMACK        := time -f %e smack ${SMACK_FLAGS}
BOOGIE_SMACK := ${SMACK} --verifier=boogie
CVC4_SMACK   := ${SMACK} --verifier-options=/bopt:proverOpt:SOLVER=cvc4
YICES2_SMACK   := ${SMACK} --solver=yices2 --bit-precise-pointers

smoke_source     := $(wildcard src/*_smoke.c)
fail_source      := $(wildcard src/*_fail.c)
pass_source      := $(wildcard src/*_pass.c)

smoke_txt     := $(patsubst %.c,%_log.txt,${smoke_source})
fail_txt      := $(patsubst %.c,%_log.txt,${fail_source})
pass_txt      := $(patsubst %.c,%_log.txt,${pass_source})

smoke_log_files     := $(patsubst src/%,smoke_logs/%,${smoke_txt})
fail_log_files      := $(patsubst src/%,fail_logs/%,${fail_txt})
pass_log_files      := $(patsubst src/%,pass_logs/%,${pass_txt})

smoke_cvc4_log_files     := $(patsubst src/%,smoke_cvc4_logs/%,${smoke_txt})
fail_cvc4_log_files      := $(patsubst src/%,fail_cvc4_logs/%,${fail_txt})
pass_cvc4_log_files      := $(patsubst src/%,pass_cvc4_logs/%,${pass_txt})

smoke_yices2_log_files     := $(patsubst src/%,smoke_yices2_logs/%,${smoke_txt})
fail_yices2_log_files      := $(patsubst src/%,fail_yices2_logs/%,${fail_txt})
pass_yices2_log_files      := $(patsubst src/%,pass_yices2_logs/%,${pass_txt})

smoke_boogie_log_files     := $(patsubst src/%,smoke_boogie_logs/%,${smoke_txt})
fail_boogie_log_files      := $(patsubst src/%,fail_boogie_logs/%,${fail_txt})
pass_boogie_log_files      := $(patsubst src/%,pass_boogie_logs/%,${pass_txt})




.PHONY: all
all: smoke fail pass

.PHONY: cvc4
cvc4: smoke_cvc4 fail_cvc4 pass_cvc4

.PHONY: yices2
yices2: smoke_yices2 fail_yices2 pass_yices2

.PHONY: boogie
boogie: smoke_boogie fail_boogie pass_boogie




.PHONY: smoke
smoke: ${smoke_log_files}

.PHONY: fail
fail: ${fail_log_files}

.PHONY: pass
pass: ${pass_log_files}


.PHONY: smoke_cvc4
smoke_cvc4: ${smoke_cvc4_log_files}

.PHONY: fail_cvc4
fail_cvc4: ${fail_cvc4_log_files}

.PHONY: pass_cvc4
pass_cvc4: ${pass_cvc4_log_files}


.PHONY: smoke_yices2
smoke_yices2: ${smoke_yices2_log_files}

.PHONY: fail_yices2
fail_yices2: ${fail_yices2_log_files}

.PHONY: pass_yices2
pass_yices2: ${pass_yices2_log_files}


.PHONY: smoke_boogie
smoke_boogie: ${smoke_boogie_log_files}

.PHONY: fail_boogie
fail_boogie: ${fail_boogie_log_files}

.PHONY: pass_boogie
pass_boogie: ${pass_boogie_log_files}




smoke_logs/%_log.txt: src/%.c | smoke_logs
	! $(SMACK) $^ > $@ 2>&1

fail_logs/%_log.txt: src/%.c | fail_logs
	! $(SMACK) $^ > $@ 2>&1

pass_logs/%_log.txt: src/%.c | pass_logs
	$(SMACK) $^ > $@ 2>&1


smoke_cvc4_logs/%_log.txt: src/%.c | smoke_cvc4_logs
	! $(CVC4_SMACK) $^ > $@ 2>&1

fail_cvc4_logs/%_log.txt: src/%.c | fail_cvc4_logs
	! $(CVC4_SMACK) $^ > $@ 2>&1

pass_cvc4_logs/%_log.txt: src/%.c | pass_cvc4_logs
	$(CVC4_SMACK) $^ > $@ 2>&1


smoke_yices2_logs/%_log.txt: src/%.c | smoke_yices2_logs
	! $(YICES2_SMACK) $^ > $@ 2>&1

fail_yices2_logs/%_log.txt: src/%.c | fail_yices2_logs
	! $(YICES2_SMACK) $^ > $@ 2>&1

pass_yices2_logs/%_log.txt: src/%.c | pass_yices2_logs
	$(YICES2_SMACK) $^ > $@ 2>&1


smoke_boogie_logs/%_log.txt: src/%.c | smoke_boogie_logs
	! $(BOOGIE_SMACK) $^ > $@ 2>&1

fail_boogie_logs/%_log.txt: src/%.c | fail_boogie_logs
	! $(BOOGIE_SMACK) $^ > $@ 2>&1

pass_boogie_logs/%_log.txt: src/%.c | pass_boogie_logs
	$(BOOGIE_SMACK) $^ > $@ 2>&1




smoke_logs:
	mkdir -p smoke_logs

fail_logs:
	mkdir -p fail_logs

pass_logs:
	mkdir -p pass_logs


smoke_cvc4_logs:
	mkdir -p smoke_cvc4_logs

fail_cvc4_logs:
	mkdir -p fail_cvc4_logs

pass_cvc4_logs:
	mkdir -p pass_cvc4_logs


smoke_yices2_logs:
	mkdir -p smoke_yices2_logs

fail_yices2_logs:
	mkdir -p fail_yices2_logs

pass_yices2_logs:
	mkdir -p pass_yices2_logs


smoke_boogie_logs:
	mkdir -p smoke_boogie_logs

fail_boogie_logs:
	mkdir -p fail_boogie_logs

pass_boogie_logs:
	mkdir -p pass_boogie_logs




.PHONY: clean
clean:
	$(RM) *~
	$(RM) */*~
	$(RM) -r smoke_logs
	$(RM) -r fail_logs
	$(RM) -r pass_logs
	$(RM) -r smoke_cvc4_logs
	$(RM) -r fail_cvc4_logs
	$(RM) -r pass_cvc4_logs
	$(RM) -r smoke_yices2_logs
	$(RM) -r fail_yices2_logs
	$(RM) -r pass_yices2_logs
	$(RM) -r smoke_boogie_logs
	$(RM) -r fail_boogie_logs
	$(RM) -r pass_boogie_logs
